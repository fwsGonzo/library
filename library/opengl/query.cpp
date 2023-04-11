#include <library/opengl/query.hpp>

#include <library/opengl/opengl.hpp>
#include <cstdio>

namespace library
{
void QueryObject::init()
{
    glGenQueries(1, &this->m_id);
}

bool QueryObject::available()
{
	if (m_target == 0)
		return false;

	GLint result = 0;
	glGetQueryObjectiv(this->m_id, GL_QUERY_RESULT_AVAILABLE, &result);
	return result == GL_TRUE;
}

void QueryObject::begin(GLenum target)
{
	glBeginQuery(target, this->m_id);
	this->m_target = target;
}
void QueryObject::end()
{
	glEndQuery(this->m_target);
}

GLint QueryObject::getI32(bool wait)
{
	GLint result = 0;
	glGetQueryObjectiv(this->m_id, wait ? GL_QUERY_RESULT : GL_QUERY_RESULT_NO_WAIT, &result);
	return result;
}

GLuint QueryObject::getU32(bool wait)
{
	GLuint result = 0;
	glGetQueryObjectuiv(this->m_id, wait ? GL_QUERY_RESULT : GL_QUERY_RESULT_NO_WAIT, &result);
	return result;
}

} // namespace library
