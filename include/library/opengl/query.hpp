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

class OcclusionQuery
{
public:
	OcclusionQuery() = default;
	~OcclusionQuery();

	OcclusionQuery(const OcclusionQuery&) = delete;
	OcclusionQuery& operator=(const OcclusionQuery&) = delete;
	OcclusionQuery(OcclusionQuery&& other) noexcept;
	OcclusionQuery& operator=(OcclusionQuery&& other) noexcept;

	void begin();
	void end();
	bool isResultAvailable() const;
	bool isPassed() const;

private:
	void initialize();
	GLuint m_id = 0;
};

} // namespace library
