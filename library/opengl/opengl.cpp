#include <library/opengl/opengl.hpp>

#include <library/log.hpp>
#include <library/opengl/fbo.hpp>
#include <library/opengl/window.hpp>

#include <string>

namespace library
{
	OpenGL ogl;
	
	OpenGL::OpenGL()
	{
		// standard 32-bits formats
		imageformat   = GL_RGBA8;
		storageformat = GL_UNSIGNED_BYTE;
	}
	
	// set opengl defaults, read function entry points
	void OpenGL::init()
	{
		//-== openGL extensions ==-//
		if (glewInit() != GLEW_OK)
		{
			logger << Log::ERR << "OpenGL::init(): Failed to initialize GLEW" << Log::ENDL;
			throw std::string("OpenGL::init(): GLEW initialization error");
		}		
		
		// test for some basic driver support
		this->supportsVBO = glGenBuffers != nullptr;
		this->supportsVAO = glGenVertexArrays != nullptr;
		
		this->supportsFramebuffers = glGenFramebuffers != nullptr;
		this->supportsShaders = glCreateProgram != nullptr;
		this->supportsAttribs = glVertexAttribPointer != nullptr;
		
		this->supportsGenMipmap = glGenerateMipmap != nullptr;
		
		// slightly more complicated texture arrays test
		GLuint test;
		glGenTextures(1, &test);
		glBindTexture(GL_TEXTURE_2D_ARRAY, test);
		glDeleteTextures(1, &test);
		
		this->supportsTextureArrays = (glGetError() == 0);
		
		// default states
		// GL_COMPRESSED_RGBA setting
		glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);
		// GL_GENERATE_MIPMAP setting
		glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
		// perspective-correct interpolation setting
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		
		// cleared colorbuffer value
		glClearColor(0.0, 0.0, 0.0, 0.0);
		// cleared depth values
		glClearDepth(1.0);
		// full depth range
		glDepthRange(0.0, 1.0);
		
		// default backface culling & fulfilled shading
		glCullFace(GL_BACK);
		glPolygonMode(GL_FRONT, GL_FILL);
		
		// default blend function
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		if (checkError())
		{
			throw std::string("OpenGL::init(): Initialization error");
		}
	}
	
	bool OpenGL::checkError()
	{
		GLenum error = glGetError();
		if (error)
		{
			std::string errorString;
			switch (error)
			{
			case GL_INVALID_ENUM:
				errorString = "Invalid enumeration parameter (GL_INVALID_ENUM)";
				break;
			case GL_INVALID_VALUE:
				errorString = "Invalid value for parameter (GL_INVALID_VALUE)";
				break;
			case GL_INVALID_OPERATION:
				errorString = "Invalid operation for current state (GL_INVALID_OPERATION)";
				break;
				
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				errorString = "Invalid operation on incomplete framebuffer (GL_INVALID_FRAMEBUFFER_OPERATION)";
				errorString += "\nFramebuffer error: " + FBO::errorString();
				break;
				
			default:
				errorString = "Unknown error";
			}
			
			logger << Log::ERR << "OpenGL error(" << error << "): " << errorString << Log::ENDL;
			return true;
		}
		return false;
	}
	
}
