#include <library/opengl/oglfont.hpp>

#include <library/bitmap/bitmap.hpp>
#include <library/math/matrix.hpp>
#include <library/opengl/opengl.hpp>

namespace library
{
	OglFont::OglFont(const std::string& filename, int size) : OglFont()
	{
		if (size <= 1)
			throw std::string("OglFont::OglFont: Invalid font size");
		if (load(filename, size) == false)
			throw std::string("OglFont::OglFont: Could not load font image");
	}
	
	bool OglFont::load(const std::string& filename, int size)
	{
		if (size <= 1) return false;
		this->tilesize = size;
		
		Bitmap fontImage(filename, Bitmap::PNG);
		if (fontImage.data() == nullptr) return false;
		
		fontImage.parse2D(tilesize, tilesize);
		
		// create texture, upload image data
		font = Texture(GL_TEXTURE_2D_ARRAY);
		font.create(fontImage, true, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		
		return true;
	}
	
	void OglFont::bind(GLenum unit)
	{
		// bind font shader
		shader->bind();
		if (this->lastUnit != unit)
		{
			this->lastUnit = unit;
			// resend texture slot to shader
			shader->sendInteger("fontimage", unit);
		}
		// bind texture
		font.bind(unit);
	}
	
	void OglFont::print(const vec3& location, const vec2& size, std::string text)
	{
		if (text.length() == 0) return;
		
		/// create vertex data ///
		// vertex count
		int current_vertices = text.length() * 4;
		// vertex data
		if (this->vertices < current_vertices)
		{
			// delete any old data
			delete[] this->vdata;
			// resize when too small
			this->vertices = current_vertices;
			this->vdata = new font_vertex_t[this->vertices];
		}
		font_vertex_t* vertex = vdata;
		
		for (size_t i = 0; i < text.length(); i++)
		{
			// convert text to font array index positions
			text[i] -= 32;
			
			// emit characters as quads
			vertex->x = location.x + (0 + i) * size.x;
			vertex->y = location.y + 0.0;
			vertex->z = location.z;
			vertex->s = 0;
			vertex->t = 0;
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (1 + i) * size.x;
			vertex->y = location.y + 0.0;
			vertex->z = location.z;
			vertex->s = 1;
			vertex->t = 0;
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (1 + i) * size.x;
			vertex->y = location.y + size.y;
			vertex->z = location.z;
			vertex->s = 1;
			vertex->t = 1;
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (0 + i) * size.x;
			vertex->y = location.y + size.y;
			vertex->z = location.z;
			vertex->s = 0;
			vertex->t = 1;
			vertex->p = text[i];
			vertex++;
		}
		uploadAndRender(current_vertices);
	}
	void OglFont::print2d(const vec3& location, const vec2& size, std::string text)
	{
		if (text.length() == 0) return;
		
		/// create vertex data ///
		// vertex count
		int current_vertices = text.length() * 4;
		// vertex data
		if (this->vertices < current_vertices)
		{
			// delete any old data
			delete[] this->vdata;
			// resize when too small
			this->vertices = current_vertices;
			this->vdata = new font_vertex_t[this->vertices];
		}
		font_vertex_t* vertex = this->vdata;
		
		for (size_t i = 0; i < text.length(); i++)
		{
			// convert text to font array index positions
			text[i] -= 32;
			
			// emit characters as quads
			vertex->x = location.x + (0 + i) * size.x;
			vertex->y = location.y + 0.0;
			vertex->z = location.z;
			vertex->s = 0;
			vertex->t = 1;
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (1 + i) * size.x;
			vertex->y = location.y + 0.0;
			vertex->z = location.z;
			vertex->s = 1;
			vertex->t = 1;
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (1 + i) * size.x;
			vertex->y = location.y + size.y;
			vertex->z = location.z;
			vertex->s = 1;
			vertex->t = 0;
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (0 + i) * size.x;
			vertex->y = location.y + size.y;
			vertex->z = location.z;
			vertex->s = 0;
			vertex->t = 0;
			vertex->p = text[i];
			vertex++;
		}
		uploadAndRender(current_vertices);
	}
	
	void OglFont::uploadAndRender(int verts)
	{
		// upload data to vao
		if (vao.isGood() == false)
		{
			vao.begin(sizeof(font_vertex_t), verts, this->vdata, GL_STREAM_DRAW);
			vao.attrib(0, 3, GL_FLOAT, GL_FALSE, offsetof(font_vertex_t, x));
			vao.attrib(1, 4, GL_SHORT, GL_FALSE, offsetof(font_vertex_t, s));
			vao.end();
		}
		else
		{
			vao.upload(sizeof(font_vertex_t), verts, this->vdata, GL_STREAM_DRAW);
		}
		// render
		glDrawArrays(GL_QUADS, 0, verts);
	}
	
	vec2 OglFont::measure(std::string text) const
	{
		return vec2(this->tilesize * text.length(), this->tilesize);
	}
	
}
