#include <library/opengl/gpu_mesh.hpp>
#include <library/opengl/opengl.hpp>
#include <cassert>
#include <utility>

namespace library
{
	GpuMesh::~GpuMesh()
	{
		destroy();
	}

	GpuMesh::GpuMesh(GpuMesh&& other) noexcept
		: m_vao(other.m_vao), m_vbo(other.m_vbo), m_ibo(other.m_ibo)
		, m_alloc_vb(other.m_alloc_vb), m_alloc_ib(other.m_alloc_ib)
		, m_has_data(other.m_has_data), m_created(other.m_created)
	{
		other.m_vao = 0;
		other.m_vbo = 0;
		other.m_ibo = 0;
		other.m_alloc_vb = 0;
		other.m_alloc_ib = 0;
		other.m_has_data = false;
		other.m_created = false;
	}

	GpuMesh& GpuMesh::operator=(GpuMesh&& other) noexcept
	{
		if (this != &other) {
			destroy();
			m_vao = other.m_vao;
			m_vbo = other.m_vbo;
			m_ibo = other.m_ibo;
			m_alloc_vb = other.m_alloc_vb;
			m_alloc_ib = other.m_alloc_ib;
			m_has_data = other.m_has_data;
			m_created = other.m_created;
			other.m_vao = 0;
			other.m_vbo = 0;
			other.m_ibo = 0;
			other.m_alloc_vb = 0;
			other.m_alloc_ib = 0;
			other.m_has_data = false;
			other.m_created = false;
		}
		return *this;
	}

	void GpuMesh::create(const VertexLayout& layout)
	{
		assert(!m_created);
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ibo);
		m_created = true;
		applyLayout(layout);
	}

	void GpuMesh::applyLayout(const VertexLayout& layout)
	{
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		for (const auto& a : layout.attribs) {
			glVertexAttribPointer(a.index, a.count, a.type,
				a.normalize ? GL_TRUE : GL_FALSE,
				layout.stride, (GLvoid*)(uintptr_t)a.offset);
			glEnableVertexAttribArray(a.index);
		}
	}

	void GpuMesh::upload(const void* vertices, size_t vertex_bytes,
						 const void* indices, size_t index_bytes, GLenum usage)
	{
		assert(m_created);
		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, vertex_bytes, vertices, usage);
		m_alloc_vb = vertex_bytes;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_bytes, indices, usage);
		m_alloc_ib = index_bytes;

		m_has_data = true;
	}

	void GpuMesh::uploadSubData(const void* vertices, size_t vertex_bytes,
								const void* indices, size_t index_bytes)
	{
		assert(m_created && m_has_data);
		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertex_bytes, vertices);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, index_bytes, indices);
	}

	void GpuMesh::freeBufferData()
	{
		if (!m_has_data)
			return;
		m_has_data = false;
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, GL_STATIC_DRAW);
		m_alloc_vb = 0;
		m_alloc_ib = 0;
	}

	void GpuMesh::bind() const
	{
		glBindVertexArray(m_vao);
	}

	void GpuMesh::draw(GLenum mode, uint32_t index_count, IndexType idx_type,
					   const void* index_offset, int32_t base_vertex) const
	{
		glDrawElementsBaseVertex(mode, index_count,
			static_cast<GLenum>(idx_type), index_offset, base_vertex);
	}

	void GpuMesh::drawArrays(GLenum mode, int32_t first, uint32_t count) const
	{
		glDrawArrays(mode, first, count);
	}

	void GpuMesh::scheduleDelete()
	{
		m_has_data = false;
		m_alloc_vb = 0;
		m_alloc_ib = 0;
	}

	void GpuMesh::destroy()
	{
		if (m_vao != 0) {
			glDeleteVertexArrays(1, &m_vao);
			glDeleteBuffers(1, &m_vbo);
			glDeleteBuffers(1, &m_ibo);
			m_vao = 0;
			m_vbo = 0;
			m_ibo = 0;
		}
		m_alloc_vb = 0;
		m_alloc_ib = 0;
		m_has_data = false;
		m_created = false;
	}

} // namespace library
