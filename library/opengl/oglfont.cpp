#include <library/opengl/oglfont.hpp>

#include <library/bitmap/bitmap.hpp>
#include <library/math/matrix.hpp>
#include <library/opengl/opengl.hpp>
#include <library/opengl/texture.hpp>

namespace library
{
	SimpleFont::~SimpleFont()
	{
		delete[] vdata;
	}
	
	void SimpleFont::bind(GLenum unit)
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
		texture->bind(unit);
	}
	
	// Y-axis goes positively upwards
	static const int font_windings_up[8] = 
	{
		0, 0,   1, 0,   1, 1,   0, 1
	};
	// Y-axis goes positively downwards
	static const int font_windings_down[8] = 
	{
		0, 1,   1, 1,   1, 0,   0, 0
	};
	
	void SimpleFont::print(const vec3& location, const vec2& size, std::string text, bool YaxisUp)
	{
		// vertex count
		int current_vertices = text.length();
		if (current_vertices == 0) return;
		current_vertices *= 4;
		
		/// create vertex array ///
		resizeVertexArray(current_vertices);
		
		font_vertex_t* vertex = this->vdata;
		const int* windings = (YaxisUp) ? font_windings_up : font_windings_down;
		
		/// emit vertex data
		emitTextBlock(vertex, location, size, text, windings);
		
		// upload to GPU and render
		upload(current_vertices);
		render();
	}
	void SimpleFont::serialUpload(std::vector<SimpleFont::print_data_t>& data, bool YaxisUp)
	{
		// vertex count
		int current_vertices = 0;
		for (size_t i = 0; i < data.size(); i++)
			current_vertices += data[i].text.length();
		
		if (current_vertices == 0) return;
		current_vertices *= 4;
		
		/// create vertex array ///
		resizeVertexArray(current_vertices);
		
		font_vertex_t* vertex = this->vdata;
		const int* windings = (YaxisUp) ? font_windings_up : font_windings_down;
		
		/// emit vertex data for each data structure
		for (size_t i = 0; i < data.size(); i++)
		{
			emitTextBlock(vertex, data[i].location, data[i].size, data[i].text, windings);
		}
		
		// upload to GPU and render
		upload(current_vertices);
	}
	
	void SimpleFont::resizeVertexArray(int verts)
	{
		// vertex data
		if (this->max_vertices < verts)
		{
			// delete any old data
			delete[] this->vdata;
			// resize when too small
			this->max_vertices = verts;
			this->vdata = new font_vertex_t[this->max_vertices];
		}
	}
	
	void SimpleFont::emitTextBlock(font_vertex_t*& vertex, const vec3& location, const vec2& size, std::string& text, const int* wind)
	{
		for (size_t i = 0; i < text.length(); i++)
		{
			// convert text to font array index positions
			text[i] -= 32;
			
			// emit characters as quads
			vertex->x = location.x + (wind[0] + i) * size.x;
			vertex->y = location.y + 0.0;
			vertex->z = location.z;
			vertex->s = wind[0];
			vertex->t = wind[1];
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (wind[2] + i) * size.x;
			vertex->y = location.y + 0.0;
			vertex->z = location.z;
			vertex->s = wind[2];
			vertex->t = wind[3];
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (wind[4] + i) * size.x;
			vertex->y = location.y + size.y;
			vertex->z = location.z;
			vertex->s = wind[4];
			vertex->t = wind[5];
			vertex->p = text[i];
			vertex++;
			
			vertex->x = location.x + (wind[6] + i) * size.x;
			vertex->y = location.y + size.y;
			vertex->z = location.z;
			vertex->s = wind[6];
			vertex->t = wind[7];
			vertex->p = text[i];
			vertex++;
		}
	}
	
	void SimpleFont::upload(int verts)
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
	}
	
	// a simple render call
	void SimpleFont::render()
	{
		vao.render(GL_QUADS);
	}
	
	Texture* SimpleFont::createTexture(const std::string& filename, int tilesize)
	{
		if (tilesize <= 1)
			throw std::string("SimpleFont::createTexture: Invalid tile size");
		
		// FIXME: assuming PNG format
		Bitmap fontImage(filename, Bitmap::PNG);
		if (fontImage.isValid() == false)
			throw std::string("SimpleFont::createTexture: Bitmap ended up invalid");
		
		fontImage.parse2D(tilesize, tilesize);
		
		// create texture, upload image data
		texture = new Texture(GL_TEXTURE_2D_ARRAY);
		texture->create(fontImage, true, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
		
		return texture;
	}
	
}
