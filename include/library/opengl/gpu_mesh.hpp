#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

typedef unsigned int GLenum;
typedef unsigned int GLuint;

namespace library
{
	struct VertexAttrib {
		uint32_t index;
		uint32_t count;
		GLenum   type;
		bool     normalize;
		uint32_t offset;
	};

	struct VertexLayout {
		uint32_t stride;
		std::vector<VertexAttrib> attribs;
	};

	enum class IndexType : GLenum {
		Uint16 = 0x1403, // GL_UNSIGNED_SHORT
		Uint32 = 0x1405, // GL_UNSIGNED_INT
	};

	class GpuMesh {
	public:
		GpuMesh() = default;
		~GpuMesh();

		GpuMesh(GpuMesh&& other) noexcept;
		GpuMesh& operator=(GpuMesh&& other) noexcept;
		GpuMesh(const GpuMesh&) = delete;
		GpuMesh& operator=(const GpuMesh&) = delete;

		void create(const VertexLayout& layout);

		void upload(const void* vertices, size_t vertex_bytes,
					const void* indices, size_t index_bytes,
					GLenum usage = 0x88E4 /* GL_STATIC_DRAW */);

		void uploadSubData(const void* vertices, size_t vertex_bytes,
						   const void* indices, size_t index_bytes);

		void freeBufferData();

		void bind() const;

		void draw(GLenum mode, uint32_t index_count, IndexType idx_type,
				  const void* index_offset, int32_t base_vertex) const;

		void drawArrays(GLenum mode, int32_t first, uint32_t count) const;

		bool hasData() const noexcept { return m_has_data; }
		GLuint vao() const noexcept { return m_vao; }

		size_t allocatedVertexBytes() const noexcept { return m_alloc_vb; }
		size_t allocatedIndexBytes() const noexcept { return m_alloc_ib; }

		void scheduleDelete();

	private:
		void destroy();
		void applyLayout(const VertexLayout& layout);

		GLuint m_vao = 0;
		GLuint m_vbo = 0;
		GLuint m_ibo = 0;
		size_t m_alloc_vb = 0;
		size_t m_alloc_ib = 0;
		bool m_has_data = false;
		bool m_created = false;
	};

} // namespace library
