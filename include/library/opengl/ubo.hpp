/**
 * 
 * Uniform Buffer Object
 * 
**/
#pragma once

typedef unsigned int GLenum;
typedef unsigned int GLuint;
typedef void GLvoid;

#ifndef GL_STATIC_DRAW_ARB
#define GL_STATIC_DRAW_ARB 0x88E4
#endif

namespace library
{
class UBO
{
public:
    UBO() = default;

    inline bool good() const { return m_ubo != 0; }

    // Upload data
    void upload(GLuint bytes, const GLvoid* data,
                GLenum usage = GL_STATIC_DRAW_ARB);

    // Upload data at given offset
    void upload_at(GLuint offset, GLuint bytes, const GLvoid* data);

    // bind / unbind mesh
    void bind();
    static void unbind();

	void bindGlobalIndex(GLuint index, GLuint offset, GLuint bytes);

private:
    GLuint m_ubo = 0;
};

} // library
