#include <library/opengl/vao.hpp>

#include <cassert>
#include <cstdint>
#include <library/log.hpp>
#include <library/opengl/opengl.hpp>
#include <array>
#include <stdexcept>

namespace library
{
GLuint VAO::lastVAO = 0;

// custom drawing
void VAO::begin(GLuint vertexSize, GLsizei vertices, const GLvoid* data, GLenum usage)
{
	// create VAO & VBO
	if (vao == 0)
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
	}
	upload(vertexSize, vertices, data, usage);
}
void VAO::upload(GLuint vertexSize, GLsizei vertices, const GLvoid* data, GLenum usage)
{
	assert(this->vao != 0);
	bind();
	glBindBuffer(GL_ARRAY_BUFFER_ARB, vbo);

	this->vertexSize = vertexSize;
	this->vertices = vertices;
	unsigned int totalBytes = vertices * vertexSize;

	// upload data
	glBufferData(GL_ARRAY_BUFFER_ARB, totalBytes, data, usage);

#ifdef DEBUG
	if (OpenGL::checkError())
	{
		logger << Log::ERR << "VAO::upload(): OpenGL error for vao = " << vao
			   << ", vbo = " << vbo << Log::ENDL;
		throw std::runtime_error("VAO::upload(): OpenGL error");
	}
#endif
}
void VAO::uploadAt(GLuint vertexSize, GLsizei offset, GLsizei vertices, const GLvoid* data)
{
	assert(this->vao != 0);
	bind();
	glBindBuffer(GL_ARRAY_BUFFER_ARB, vbo);

	this->vertexSize = vertexSize;
	this->vertices = std::max(this->vertices, GLsizei(offset + vertices));
	unsigned int totalBytes = vertices * vertexSize;

	// upload data
	glBufferSubData(GL_ARRAY_BUFFER_ARB, offset * vertexSize, totalBytes, data);

#ifdef DEBUG
	if (OpenGL::checkError())
	{
		logger << Log::ERR << "VAO::uploadAt(): OpenGL error for vao = " << vao
			   << ", vbo = " << vbo << Log::ENDL;
		throw std::runtime_error("VAO::uploadAt(): OpenGL error");
	}
#endif
}

void VAO::uploadIndices(const GLvoid* data, GLsizei dataSize, GLsizei count, GLenum usage)
{
	if (dataSize != 2 && dataSize != 4) {
		throw std::runtime_error("VAO::upload_indices(): Indices must be 16- or 32-bit in size");
	}
	this->indices = count;
	this->indexSize = dataSize;

	bind();
	if (ibo == 0) { glGenBuffers(1, &ibo); }
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER_ARB, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER_ARB, count * dataSize, data, usage);

#ifdef DEBUG
	if (OpenGL::checkError())
	{
		logger << Log::ERR << "VAO::indexes(): OpenGL error for vao = " << vao << ", ibo = " << ibo
			   << Log::ENDL;
		throw std::runtime_error("VAO::indexes(): OpenGL error");
	}
#endif
}

void VAO::attrib(GLuint index, GLsizei size, GLenum type, bool normalize, int offset)
{
	glEnableVertexAttribArray(index);
	intptr_t dataPointer = offset; // convert offset to the pointer size of build target
	glVertexAttribPointer(index, size, type, (normalize) ? GL_TRUE : GL_FALSE, vertexSize,
						  (GLvoid*) dataPointer);

#ifdef DEBUG
	if (OpenGL::checkError())
	{
		logger << Log::ERR << "VAO::attrib(): OpenGL error for vao = " << vao << ", vbo = " << vbo
			   << Log::ENDL;
		logger << Log::ERR << "VAO::attrib(): Attrib = { index = " << index << ", size = " << size
			   << ", type = " << type << ", normalize = " << normalize << ", offset = " << offset
			   << " }" << Log::ENDL;
		throw std::runtime_error("VAO::attrib(): OpenGL error");
	}
#endif
}

void VAO::createScreenspaceVAO()
{
	struct screenvertex_t
	{
		float x, y;
	};

	screenvertex_t sv_t[4] = {{1, 0}, {0, 0}, {0, 1}, {1, 1}};
	std::array<uint16_t, 6> ind{0, 1, 2, 0, 2, 3};

	begin(sizeof(screenvertex_t), 4, sv_t);
	indexes(ind.data(), ind.size());
	attrib(0, 2, GL_FLOAT, GL_FALSE, 0);
}

void VAO::renderScreenspaceNow()
{
	static VAO vao;
	if (!vao.good()) {
		vao.createScreenspaceVAO();
	}
	vao.renderIndexed(GL_TRIANGLES);
}

void VAO::bind()
{
	if (lastVAO != vao)
	{
		glBindVertexArray(vao);
		lastVAO = vao;
	}
}

void VAO::unbind()
{
	glBindVertexArray(0);
	lastVAO = 0;
}

void VAO::render(GLenum mode, GLint first, GLsizei count)
{
	bind();
	glDrawArrays(mode, first, count);

#ifdef DEBUG
	if (OpenGL::checkError())
	{
		logger << Log::ERR << "VAO::render(): OpenGL error for vao = " << vao << Log::ENDL;
		logger << Log::ERR << "VAO::render(): render = { mode = " << mode << ", first = " << first
			   << ", count = " << count << " }" << Log::ENDL;
		throw std::runtime_error("VAO::render(): OpenGL error");
	}
#endif
}

void VAO::renderIndexed(GLenum mode, GLuint first, GLint count)
{
	bind();
	glDrawElements(mode, count, indexSize == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, (GLvoid*)uintptr_t(first * indexSize));

#ifdef DEBUG
	if (OpenGL::checkError())
	{
		logger << Log::ERR << "VAO::renderIndexed(3): OpenGL error for vao = " << vao << Log::ENDL;
		throw std::runtime_error("VAO::renderIndexed(3): OpenGL error");
	}
#endif
}
void VAO::renderIndexed(GLenum mode)
{
	bind();
	glDrawElements(mode, this->indices, indexSize == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, 0);

#ifdef DEBUG
	if (OpenGL::checkError())
	{
		logger << Log::ERR << "VAO::renderIndexed(1): OpenGL error for vao = " << vao << Log::ENDL;
		throw std::runtime_error("VAO::renderIndexed(1): OpenGL error");
	}
#endif
}
} // namespace library
