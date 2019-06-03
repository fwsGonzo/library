#include <library/opengl/oglfont.hpp>

#include <string>
#include <vector>

namespace library
{
Shader* SimpleFont::createShader()
{
    const std::string font_vertex_shader =
        R"(
			#version 130
			uniform mat4 mvp;
			
			in vec3 in_vertex;
			in vec2 in_texture;
			
			out vec2 texCoord;
			
			void main(void)
			{
				texCoord = in_texture;
				
				gl_Position = mvp * vec4(in_vertex.xyz, 1.0);
			}
		)";
    const std::string font_fragment_shader =
        R"(
			#version 130
			uniform sampler2D fontimage;
			uniform vec4 bgcolor;
			uniform vec4 fcolor;
			
			in vec2 texCoord;
      out vec4 color;
			
			void main(void)
			{
				color = fcolor * texture(fontimage, texCoord);
				color = mix(bgcolor, color, length(color.rgb));
			}
		)";

    std::vector<std::string> attr;
    attr.emplace_back("in_vertex");
    attr.emplace_back("in_texture");

    shader = new Shader(font_vertex_shader, font_fragment_shader, "Internal font shader", attr);
    shader->sendVec4("bgcolor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)); // black
    shader->sendVec4("fcolor", glm::vec4(1.0f));                    // white

    return shader;
}
} // namespace library
