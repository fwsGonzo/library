#include <library/opengl/oglfont.hpp>

#include <library/bitmap/bitmap.hpp>
#include <library/math/matrix.hpp>
#include <library/opengl/opengl.hpp>
#include <library/opengl/texture.hpp>

namespace library
{
	SimpleFont::SimpleFont()
		: tilesize(0), lastUnit(-1)
	{
		setClip(glm::vec2(0.0));
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

	void SimpleFont::setClip(const glm::vec2& clip)
	{
		this->clip = clip;
		// Y-axis goes positively upwards
		font_windings_up =
		{
			clip.x, clip.y,   1-clip.x, clip.y,   1-clip.x, 1-clip.y,   clip.x, 1-clip.y
		};
		// Y-axis goes positively downwards
		font_windings_down =
		{
			clip.x, 1-clip.y,   1-clip.x, 1-clip.y,   1-clip.x, clip.y,   clip.x, clip.y
		};
	}

	void SimpleFont::print(const glm::vec3& location, const glm::vec2& size, std::string text, bool YaxisUp)
	{
		vdata.clear();
    idata.clear();
		std::vector<float>& windings = (YaxisUp) ? font_windings_up : font_windings_down;

		/// emit vertex data
		emitTextBlock(location, size, text, windings);

		// upload to GPU and render
		this->upload();
		this->render();
	}
	void SimpleFont::serialPrint(std::vector<SimpleFont::print_data_t>& data, bool YaxisUp)
	{
    vdata.clear();
    idata.clear();
		std::vector<float>& windings = (YaxisUp) ? font_windings_up : font_windings_down;

		/// emit vertex data for each data structure
		for (size_t i = 0; i < data.size(); i++)
		{
			emitTextBlock(data[i].location, data[i].size, data[i].text, windings);
		}

    // upload to GPU and render
		this->upload();
		this->render();
	}

	void SimpleFont::emitTextBlock(const glm::vec3& location, const glm::vec2& size, std::string& text, const std::vector<float>& wind)
	{
		for (size_t i = 0; i < text.length(); i++)
		{
			// convert text to font array index positions
			text[i] -= 32;

			#define clipInt(x) ((x > 0.5) ? 1 : 0)

      const size_t idx = vdata.size();
			// emit characters as quads
      vdata.push_back(font_vertex_t {
			     .x = location.x + (clipInt(wind[0]) + i) * size.x,
			     .y = location.y + 0.0,
			     .z = location.z,
			     .s = wind[0],
			     .t = wind[1],
			     .p = text[i]
      });

      vdata.push_back(font_vertex_t {
			     .x = location.x + (clipInt(wind[2]) + i) * size.x,
			     .y = location.y + 0.0,
			     .z = location.z,
			     .s = wind[2],
			     .t = wind[3],
			     .p = text[i]
      });

      vdata.push_back(font_vertex_t {
				   .x = location.x + (clipInt(wind[4]) + i) * size.x,
				   .y = location.y + size.y,
				   .z = location.z,
				   .s = wind[4],
				   .t = wind[5],
				   .p = text[i]
      });

      vdata.push_back(font_vertex_t {
  			   .x = location.x + (clipInt(wind[6]) + i) * size.x,
				   .y = location.y + size.y,
				   .z = location.z,
				   .s = wind[6],
				   .t = wind[7],
				   .p = text[i]
      });
      
      idata.push_back(idx + 0);
      idata.push_back(idx + 1);
      idata.push_back(idx + 2);
      idata.push_back(idx + 2);
      idata.push_back(idx + 3);
      idata.push_back(idx + 0);
		}
	}

	void SimpleFont::upload()
	{
		// upload data to vao
		if (vao.good() == false)
		{
			vao.begin(sizeof(font_vertex_t), vdata.size(), vdata.data(), GL_STREAM_DRAW);
			vao.attrib(0, 3, GL_FLOAT, GL_FALSE, offsetof(font_vertex_t, x));
			vao.attrib(1, 3, GL_FLOAT, GL_FALSE, offsetof(font_vertex_t, s));
			vao.end();
		}
		else
		{
			vao.upload(sizeof(font_vertex_t), vdata.size(), vdata.data(), GL_STREAM_DRAW);
		}
    vao.indexes(idata.data(), idata.size());
	}

	// a simple render call
	void SimpleFont::render()
	{
		vao.renderIndexed(GL_TRIANGLES);
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
