#pragma once
#include <cstddef>
#include <cstdint>

// aliases to avoid including GL header
typedef unsigned int GLenum;
typedef int GLint;
typedef unsigned int GLuint;

namespace library
{
class QueryObject
{
public:
    QueryObject() {}

	void init();
    void begin(GLenum target);
	void end();

	bool available();

	GLint    getI32(bool wait = false);
	GLuint   getU32(bool wait = false);

private:
    GLuint m_id;
	GLenum m_target = 0;
	bool m_query_active = false;
};
} // namespace library
