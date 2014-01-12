#include <library/opengl/window.hpp>

#include <library/log.hpp>
#include <library/sleep.hpp>
#include <GL/glfw3.h>
#include <library/opengl/opengl.hpp>

namespace library
{
	bool WindowClass::init = false;
	
	WindowConfig::WindowConfig()
	{
		// set default window settings
		this->title = "Untitled window";
		this->SW = 640;
		this->SH = 480;
		this->fullscreen = false;
		this->refreshrate = 60;
		this->vsync = true;
		this->multisample = 0;
	}
	WindowConfig::WindowConfig(std::string title, int width, int height)
	{
		// set default window settings
		this->title = title;
		this->SW = width;
		this->SH = height;
		this->fullscreen = false;
		this->refreshrate = 60;
		this->vsync = true;
		this->multisample = 0;
	}
	
	void WindowClass::open(const WindowConfig& wndconf)
	{
		if (this->init == false)
		{
			glfwInit();
		}
		this->closing = false;
		
		// fullscreen enables setting refresh rate
		this->fullscreen = wndconf.fullscreen;
		
		GLFWmonitor* monitor = nullptr;
		// set primary monitor if we are to run in fullscreen
		if (fullscreen) monitor = glfwGetPrimaryMonitor();
		
		glfwWindowHint(GLFW_REFRESH_RATE, wndconf.refreshrate);
		glfwWindowHint(GLFW_RESIZABLE, 0);
		
		// clamp multisample to at least 0
		int multisample = wndconf.multisample;
		if (multisample < 0) multisample = 0;
		// set multisampling level for main framebuffer
		glfwWindowHint(GLFW_SAMPLES, multisample);
		// common alpha, stencil & depth settings
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_DEPTH_BITS,  24);
		glfwWindowHint(GLFW_STENCIL_BITS, 8);
		
		// create new glfw3 window
		this->wndHandle = glfwCreateWindow(wndconf.SW, wndconf.SH, wndconf.title.c_str(), monitor, nullptr);
		
		if (this->wndHandle == nullptr)
		{
			logger << Log::ERR << "Could not open 32bit / 24d8s window of size: " << SW << ", " << SH << Log::ENDL;
			glfwTerminate();
			throw "Window::init(): Could not open OpenGL context window, check your drivers!";
		}
		
		// get actual size, since it may not be supported
		glfwGetWindowSize(this->wndHandle, &this->SW, &this->SH);
		// screen aspect
		this->SA = (float)this->SW / (float)this->SH;
		
		// make this window the current OpenGL context
		setCurrent();
		
		// vertical sync
		glfwSwapInterval((wndconf.vsync) ? 1 : 0);
		
		// set default viewport
		glViewport(0, 0, this->SW, this->SH);
		
		// initialize OpenGL automatically
		if (this->init == false)
		{
			this->init = true;
			// init OpenGL entries & defaults
			ogl.init();
		}
	}
	
	void WindowClass::close()
	{
		if (wndHandle)
		{
			setCurrent();
			glfwDestroyWindow(wndHandle);
			wndHandle = nullptr;
		}
	}
	
	void WindowClass::waitClose()
	{
		while (this->closing == false)
			relinquishCPU();
		close();
	}
	
	GLFWwindow* WindowClass::window()
	{
		return this->wndHandle;
	}
	
	void WindowClass::setTitle(std::string title)
	{
		glfwSetWindowTitle(wndHandle, title.c_str());
	}
	
	void WindowClass::setPosition(int x, int y)
	{
		glfwSetWindowPos(wndHandle, x, y);
	}
	
	// makes this window the current opengl context
	void WindowClass::setCurrent()
	{
		glfwMakeContextCurrent(this->wndHandle);
	}
	
	void WindowClass::startRenderingLoop(renderFunc renderfunc, double granularity)
	{
		setCurrent();
		double t0 = glfwGetTime();
		double t1 = t0;
		
		glfwSetWindowShouldClose(wndHandle, 0);
		while (!glfwWindowShouldClose(wndHandle))
		{
			setCurrent();
			
			double t2 = t1;
			t1 = glfwGetTime();
			// variable delta-frame timing
			double dtime = (t2 - t1) / granularity;
			
			// render function returns false if we should stop rendering
			if (renderfunc(*this, dtime, t1 - t0) == false) break;
			
			// check for new events that might eg. set window to be flagged as closing
			glfwPollEvents();
		}
		
		this->closing = true;
	}
	
}
