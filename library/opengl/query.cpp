#include <library/opengl/query.hpp>

#include <library/opengl/opengl.hpp>
#include <cstdio>

namespace library
{
void QueryObject::initialize()
{
	if (this->m_id[0] == ~0u)
		glGenQueries(2, this->m_id);
}

bool QueryObject::available()
{
	this->initialize();

	if (this->m_target == 0 || m_query_active)
		return false;

	GLuint result = 0;
	glGetQueryObjectuiv(this->m_id[1], GL_QUERY_RESULT_AVAILABLE, &result);
	return result == GL_TRUE;
}

void QueryObject::beginTimer()
{
	if (this->m_target != 0 || this->m_query_active)
		return;

	this->initialize();

	glQueryCounter(this->m_id[0], GL_TIMESTAMP);
	this->m_target = GL_TIMESTAMP;
	this->m_query_active = true;
}
void QueryObject::endTimer()
{
	if (this->m_query_active) {
		glQueryCounter(this->m_id[1], GL_TIMESTAMP);
		m_query_active = false;
	}
}

GLuint64 QueryObject::getU64(bool wait)
{
	GLuint64 result[2] = {0, 0};
	glGetQueryObjectui64v(this->m_id[0], wait ? GL_QUERY_RESULT : GL_QUERY_RESULT_NO_WAIT, &result[0]);
	glGetQueryObjectui64v(this->m_id[1], wait ? GL_QUERY_RESULT : GL_QUERY_RESULT_NO_WAIT, &result[1]);
	this->m_target = 0;
	return result[1] - result[0];
}

} // namespace library
