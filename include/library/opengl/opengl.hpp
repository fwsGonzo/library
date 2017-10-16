/**
 * OpenGL state & resource manager
**/

#ifndef OPENGL_HPP
#define OPENGL_HPP

#define GLEW_STATIC
#include <GL/glew.h>

namespace library
{
	class OpenGL {
	public:
		bool supportsVBO;
		bool supportsVAO;

		bool supportsFramebuffers;
		bool supportsShaders;
		bool supportsAttribs;

		bool supportsGenMipmap;
		bool supportsTextureArrays;

		OpenGL(bool core_context);
		static bool checkError();
	};
}
#endif
