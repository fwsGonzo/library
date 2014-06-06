#include <library/opengl/input.hpp>

#include <library/log.hpp>
#include <library/math/toolbox.hpp>
#include <library/opengl/window.hpp>
#include <GL/glfw3.h>
#include <cmath>

#include <iostream>

namespace library
{
	std::vector<Input*> Input::workingSet;
	
	void keyboard(GLFWwindow* window, int key, int action, int a, int b);
	void keyboardType(GLFWwindow* window, unsigned int character);
	void mouseMove(GLFWwindow* window, double x, double y);
	void mouseButton(GLFWwindow* window, int button, int action, int mods);
	void mouseWheel(GLFWwindow* window, double x, double y);
	
	void Input::init(WindowClass& gamescr, bool kbd, bool mouse)
	{
		workingSet.push_back(this);
		// set owning window
		this->gamescr = &gamescr;
		this->speed   = 0.12;
		this->sensitivity = 8;
		// default rotation
		this->rotation  = vec2(0.0);
		this->mousegrab = false;
		
		if (kbd)
		{
			// hook keyboard events
			glfwSetKeyCallback (gamescr.window(), &keyboard);
			glfwSetCharCallback(gamescr.window(), &keyboardType);
			// disable sticky keys
			glfwSetInputMode(gamescr.window(), GLFW_STICKY_KEYS, GL_TRUE);
		}
		if (mouse)
		{
			// hook mouse events
			glfwSetCursorPosCallback(gamescr.window(), &mouseMove);
			// mouse button event
			glfwSetMouseButtonCallback(gamescr.window(), &mouseButton);
			// mouse wheel event
			glfwSetScrollCallback(gamescr.window(), &mouseWheel);
		}
	}
	Input::~Input()
	{
		for(size_t i = 0; i < workingSet.size(); i++)
		{
			if (workingSet[i] == this)
				workingSet.erase(workingSet.begin()+i, workingSet.begin()+i+1);
		}
	}
	
	const Input::input_t& Input::getKeyEx(int key) const
	{
		if (key < 0 || key >= MAX_KEYS)
			throw std::string("Input::getKey(): Invalid key value");
		
		return keys[key];
	}
	Input::key_t Input::getKey(int key) const
	{
		return getKeyEx(key).action;
	}
	
	void Input::hold(int key)
	{
		keys[key].action = KEY_LOCKED;
	}
	void Input::release(int key)
	{
		if (keys[key].action == KEY_LOCKED)
			keys[key].action = KEY_PRESSED;
	}
	
	void Input::mouseOptions(double speed, double sensitivity)
	{
		this->speed    = speed;
		this->sensitivity = sensitivity;
	}
	void Input::showMouse(bool show)
	{
		if (show)
			glfwSetInputMode(gamescr->window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(gamescr->window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
	}
	void Input::grabMouse(bool grab)
	{
		this->mousegrab = grab;
		if (grab)
		{
			// move cursor to center of window
			lastMousePos = vec2(gamescr->getWidth(), gamescr->getHeight()) / 2.0;
			mousePos = lastMousePos;
			glfwSetCursorPos(gamescr->window(), mousePos.x, mousePos.y);
		}
	}
	
	const Input::input_t& Input::getMouseEx(int button) const
	{
		return mouse[button];
	}
	Input::key_t Input::getMouse(int button) const
	{
		return getMouseEx(button).action;
	}
	void  Input::holdMouse(int button)
	{
		mouse[button].action = KEY_LOCKED;
	}
	
	int Input::getWheel()
	{
		int wheel = this->wheel;
		this->wheel = 0;
		return wheel;
	}
	
	bool Input::textBackspace()
	{
		if (text.size() == 0) return false;
		
		text = text.substr(0, text.size() - 1);
		return true;
	}
	
	void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Input* input = Input::inputFromWindow(window);
		if (input)
		{
			// action: GLFW_PRESS, GLFW_REPEAT and GLFW_RELEASE
			input->keys[key].action = 
				(action == GLFW_PRESS || action == GLFW_REPEAT)
				 ? Input::KEY_PRESSED
				 : Input::KEY_RELEASED;
			input->keys[key].mods = mods;
		}
	}
	
	void keyboardType(GLFWwindow* window, unsigned int character)
	{
		Input* input = Input::inputFromWindow(window);
		if (input)
		{
			// typing!
			input->text += char(character & 255);
		}
	}
	
	void mouseMove(GLFWwindow* window, double x, double y)
	{
		Input* input = Input::inputFromWindow(window);
		if (input)
		{
			if (input->mousegrab)
			{
				static const double PI = 4 * atan(1);
				static const double degToRad = PI / 180;
				static const double maxX = 89 * degToRad;
				static const double maxY = PI * 2.0;
				
				// in-game
				double dx = (x - input->lastMousePos.x) * input->speed;
				double dy = (y - input->lastMousePos.y) * input->speed;
				
				if (fabs(dx) > input->sensitivity)
					dx = toolbox::signum(dx) * input->sensitivity + dx / input->sensitivity;
				if (fabs(dy) > input->sensitivity)
					dy = toolbox::signum(dy) * input->sensitivity + dy / input->sensitivity;
				
				// rotation on axes
				input->rotation.y += dx * degToRad;
				input->rotation.x += dy * degToRad;
				// clamping
				if (input->rotation.x >  maxX) input->rotation.x =  maxX;
				if (input->rotation.x < -maxX) input->rotation.x = -maxX;
				if (input->rotation.y <     0) input->rotation.y += PI * 2;
				if (input->rotation.y >= maxY) input->rotation.y -= PI * 2;
				
				// move mouse to center
				input->lastMousePos.x = input->gamescr->getWidth() / 2;
				input->lastMousePos.y = input->gamescr->getHeight() / 2;
				glfwSetCursorPos(
					input->gamescr->window(), 
					input->lastMousePos.x, 
					input->lastMousePos.y);
			}
			else
			{
				input->lastMousePos.x = input->mousePos.x;
				input->lastMousePos.y = input->mousePos.y;
			}
			input->mousePos.x = x;
			input->mousePos.y = y;
		}
	}
	
	void mouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		#define MACTION() (action == GLFW_PRESS) ? Input::KEY_PRESSED : Input::KEY_RELEASED
		
		Input* input = Input::inputFromWindow(window);
		if (input)
		{
			if (button == GLFW_MOUSE_BUTTON_1) // left mouse button
			{
				input->mouse[0].action = MACTION();
				input->mouse[0].mods = mods;
			}
			else if (button == GLFW_MOUSE_BUTTON_2)
			{
				input->mouse[1].action = MACTION();
				input->mouse[1].mods = mods;
			}
			else if (button == GLFW_MOUSE_BUTTON_3)
			{
				input->mouse[2].action = MACTION();
				input->mouse[2].mods = mods;
			}
		}
	}
	
	void mouseWheel(GLFWwindow* window, double x, double y)
	{
		Input* input = Input::inputFromWindow(window);
		if (input)
		{
			if (y < 0)      input->wheel -= 1;
			else if (y > 0) input->wheel += 1;
			else            input->wheel  = 0;
		}
	}
	
	Input* Input::inputFromWindow(GLFWwindow* wnd)
	{
		for (Input* input : workingSet)
		{
			if (input->gamescr->window() == wnd) return input;
		}
		return nullptr;
	}
}
