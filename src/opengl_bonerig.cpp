// opengl window
#include <opengl/window.hpp>
// matrix and vector
#include <math/vector.hpp>
#include <math/matrix.hpp>
// bones
#include <math/kine/bone.hpp>
// stuff
#include <log.hpp>
#include <sleep.hpp>

#include <GL/glfw3.h>
#include <iostream>
#include <cmath>

using namespace library;

Bone motherBone;
const double PI = 4 * atan(1);

void renderTail(vec3 pos, float rad)
{
	glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(pos.x - rad, pos.y - rad, pos.z);
		
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(pos.x + rad, pos.y - rad, pos.z);
		
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(pos.x + rad, pos.y + rad, pos.z);
		
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(pos.x - rad, pos.y + rad, pos.z);
	glEnd();
}

void renderBone(Bone& bone)
{
	// render this bone
	vec3 pos = bone.getPosition();
	
	renderTail(pos, 0.5);
	
	// render children
	for (int i = 0; i < bone.childCount(); i++)
	{
		logger << Log::INFO << "Rendering child " << i << " at " << bone[i].getPosition() << Log::ENDL;
		renderBone(bone[i]);
	}
}

bool boneRenderer(WindowClass& wnd, double dtime, double timeElapsed)
{
	// depth testing
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	
	glClearColor(0.2, 0.4, 0.8, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	
	// set up perspective projection matrix
	mat4 matproj = perspectiveMatrix(61.0, wnd.SA, 0.1, 16.0);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(matproj.data());
	
	mat4 matview = rotationMatrix(sin(timeElapsed * 4.0) * PI / 8, -0.2, 0.0);
	matview.translate(0.0, 0.0, -2.0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(matview.data());
	
	renderBone(motherBone);
	
	// swap frontbuffer with backbuffer (frame change)
	glfwSwapBuffers(wnd.window());
	// close window after N seconds
	return (timeElapsed < 2);
}

void test_opengl_bonerig()
{
	std::cout << "Opening OpenGL window" << std::endl;
	
	WindowConfig wndconf;
	wndconf.fullscreen = false;
	wndconf.SW = 800;
	wndconf.SH = 600;
	wndconf.multisample = 2;
	
	// open up OpenGL window
	WindowClass renderer;
	// throws error if something bad happens...
	renderer.open(wndconf);
	
	// create bone rig
	motherBone = Bone(vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0).normalize());
	motherBone.addChild(Bone(vec3(0.0, 0.0, 2.0), vec3(0.5, 0.5, 0.0).normalize()));
	
	//////////////////////////////////////////////////////////////////
	std::cout << "Starting rendering loop: Bone rig" << std::endl;
	std::cout << "Window closes after 5 seconds" << std::endl;
	
	// what we want delta-time to be measured in:
	// 1ms granularity, meaning 1.0 dtime is 1ms, 100.0 is 100ms etc.
	// Examples: 1/1000 = 1ms/frame, 1/60 = 16.7ms/frame (60fps) etc.
	// And finally, 1.0 means dtime is measured in (whole) seconds
	const double timing_granularity = 1.0;
	
	renderer.startRenderingLoop(boneRenderer, timing_granularity);
	renderer.waitClose();
}
