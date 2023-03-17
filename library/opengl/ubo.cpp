#include <library/opengl/ubo.hpp>

#include <cassert>
#include <cstdint>
#include <library/log.hpp>
#include <library/opengl/opengl.hpp>
#include <stdexcept>

namespace library {

void UBO::upload(GLuint bytes, const GLvoid* data, GLenum usage)
{
	// Lazily create UBO on-demand
    if (this->m_ubo == 0)
    {
        glGenBuffers(1, &this->m_ubo);
    }

    // upload data
    this->bind();
    glBufferData(GL_UNIFORM_BUFFER, bytes, data, usage);

    if (OpenGL::checkError())
    {
        logger << Log::ERR << "UBO::upload(): OpenGL error for ubo = " << m_ubo
               << ", bytes = " << bytes << Log::ENDL;
        throw std::runtime_error("UBO::upload(): OpenGL error");
    }
}

void UBO::upload_at(GLuint offset, GLuint bytes, const GLvoid* data)
{
	// Lazily create UBO on-demand
    if (this->m_ubo == 0)
    {
        glGenBuffers(1, &this->m_ubo);
    }

    // upload data
    this->bind();
    glBufferSubData(GL_UNIFORM_BUFFER, offset, bytes, data);

    if (OpenGL::checkError())
    {
        logger << Log::ERR << "UBO::upload(): OpenGL error for ubo = " << m_ubo
               << ", bytes = " << bytes << Log::ENDL;
        throw std::runtime_error("UBO::upload(): OpenGL error");
    }
}

void UBO::bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->m_ubo);
}

void UBO::unbind()
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::bindGlobalIndex(GLuint index, GLuint offset, GLuint bytes)
{
	glBindBufferRange(GL_UNIFORM_BUFFER, index, this->m_ubo, offset, bytes);
}

} // library
