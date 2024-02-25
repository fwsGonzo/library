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
	if (this->m_target == 0)
		return false;

	GLint result = 0;
	glGetQueryObjectiv(this->m_id, GL_QUERY_RESULT_AVAILABLE, &result);
	return result == GL_TRUE;
}

void QueryObject::begin(GLenum target)
{
	if (this->m_target != 0 || this->m_query_active)
		return;

	glBeginQuery(target, this->m_id);
	this->m_target = target;
	this->m_query_active = true;
}
void QueryObject::end()
{
	if (this->m_target != 0 && this->m_query_active) {
		glEndQuery(this->m_target);
		m_query_active = false;
	}
}

GLint QueryObject::getI32(bool wait)
{
	GLint result = 0;
	glGetQueryObjectiv(this->m_id, wait ? GL_QUERY_RESULT : GL_QUERY_RESULT_NO_WAIT, &result);
	this->m_target = 0;
	return result;
}

GLuint QueryObject::getU32(bool wait)
{
	GLuint result = 0;
	glGetQueryObjectuiv(this->m_id, wait ? GL_QUERY_RESULT : GL_QUERY_RESULT_NO_WAIT, &result);
	this->m_target = 0;
	return result;
}

} // namespace library
