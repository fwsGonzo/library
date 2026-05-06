#pragma once
#include <library/opengl/ubo.hpp>

namespace library
{

template<typename T>
class UniformBuffer
{
public:
	void upload(const T& data, GLenum usage = 0x88E8 /* GL_DYNAMIC_DRAW */)
	{
		m_ubo.upload(sizeof(T), &data, usage);
	}

	void bind(GLuint binding_point)
	{
		m_ubo.bindGlobalIndex(binding_point, 0, sizeof(T));
	}

	void upload_and_bind(const T& data, GLuint binding_point,
						 GLenum usage = 0x88E8 /* GL_DYNAMIC_DRAW */)
	{
		upload(data, usage);
		bind(binding_point);
	}

	bool good() const { return m_ubo.good(); }

private:
	UBO m_ubo;
};

} // namespace library
