#pragma once
#include <cstddef>
#include <cstdint>

// aliases to avoid including GL header
typedef unsigned int GLenum;
typedef int GLint;
typedef uint32_t GLuint;
typedef uint64_t GLuint64;

namespace library
{
class QueryObject
{
public:
    QueryObject() {}

    void beginTimer();
	void endTimer();

	bool available();

	GLuint64 getU64(bool wait = false);

private:
	void initialize();
    GLuint m_id[2] = {~0u, ~0u};
	GLenum m_target = 0;
	bool m_query_active = false;
};
} // namespace library
