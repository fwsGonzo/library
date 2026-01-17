#include <library/opengl/input.hpp>

#include <cmath>
#include <cstdio>
#include <library/log.hpp>
#include <library/math/toolbox.hpp>
#include <library/opengl/opengl.hpp>

namespace library
{
static Input* currentInput = nullptr;

void Input::init(GLFWwindow* window, const bool kbd, const bool mouse)
{
	currentInput = this;
	// set owning window
	this->m_window = window;
	this->m_speed = 0.12;
	this->m_sensitivity = 8;
	// default rotation
	this->m_rot = glm::vec2(0.0f);

	if (kbd) { restore_keyboard(); }
	if (mouse) { restore_mouse(); }
}
void Input::restore_keyboard()
{
	// hook keyboard events
	glfwSetKeyCallback(m_window, &Input::keyboard);
	// disable sticky keys
	glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
}
void Input::restore_mouse()
{
	// hook mouse events
	glfwSetCursorPosCallback(m_window, &Input::mouseMove);
	// mouse button event
	glfwSetMouseButtonCallback(m_window, &Input::mouseButton);
	// mouse wheel event
	glfwSetScrollCallback(m_window, &Input::mouseWheel);
	// Reset keyboard and mouse input states
	this->m_keys = {};
	this->m_mouse = {};
}
Input::~Input() { currentInput = nullptr; }

void Input::mouse_options(double speed, double sensitivity)
{
	this->m_speed = speed;
	this->m_sensitivity = sensitivity;
}
void Input::mouse_grab(const bool grab)
{
	this->m_mousegrab = grab;
	if (grab)
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

int Input::mouse_wheel() const
{
	const int wheel = this->m_wheel;
	this->m_wheel = 0;
	return wheel;
}

void Input::keyboard(GLFWwindow* window, int key, int, int action, int mods)
{
	auto* input = Input::inputFromWindow(window);
	assert(input != nullptr);
	// action: GLFW_PRESS, GLFW_REPEAT or GLFW_RELEASE
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		// as long as the key isnt force-held, set to pressed
		if (input->m_keys[key].action != Input::KEY_LOCKED)
			input->m_keys[key].action = Input::KEY_PRESSED;
	} // key is no longer pressed
	else
		input->m_keys[key].action = Input::KEY_RELEASED;
	// keypress modifiers: SHIFT, CTRL, ALT
	input->m_keys[key].mods = mods;
}

void Input::rotate_degrees(glm::vec2 degrees)
{
	static const float degToRad = PI / 180;

	this->m_rot += degrees * degToRad;
	this->clamp_rotation();
}
void Input::clamp_rotation()
{
	static const float PI = 4 * atan(1);
	static const float maxX = 89 * (PI / 180);
	static const float maxY = PI * 2.0;

	// clamping
	if (this->m_rot.x > maxX) this->m_rot.x = maxX;
	if (this->m_rot.x < -maxX) this->m_rot.x = -maxX;
	while (this->m_rot.y < 0) this->m_rot.y += PI * 2;
	while (this->m_rot.y >= maxY) this->m_rot.y -= PI * 2;
}

void Input::mouseMove(GLFWwindow* window, double x, double y)
{
	Input* input = Input::inputFromWindow(window);
	assert(input != nullptr);
	if (input->m_mousegrab)
	{
		// in-game
		double dx = (x - input->m_last_mouse_xy.x) * input->m_speed;
		double dy = (y - input->m_last_mouse_xy.y) * input->m_speed;

		if (fabs(dx) > input->m_sensitivity)
			dx = signum(dx) * input->m_sensitivity + dx / input->m_sensitivity;
		if (fabs(dy) > input->m_sensitivity)
			dy = signum(dy) * input->m_sensitivity + dy / input->m_sensitivity;

		// rotation on axes
		input->rotate_degrees(glm::vec2(dy, dx));

		// remember the last pos >:|
		input->m_last_mouse_xy = {x, y};
	}
	else
	{
		input->m_last_mouse_xy.x = input->m_mouse_xy.x;
		input->m_last_mouse_xy.y = input->m_mouse_xy.y;
	}
	input->m_mouse_xy = {x, y};
}

void Input::mouseButton(GLFWwindow* window, int button, int action, int mods)
{
#define MACTION() (action == GLFW_PRESS) ? Input::KEY_PRESSED : Input::KEY_RELEASED

	auto* input = Input::inputFromWindow(window);
	assert(input != nullptr);
	input->m_mouse.at(button).action = MACTION();
	input->m_mouse.at(button).mods = mods;
}

void Input::mouseWheel(GLFWwindow* window, double, double y)
{
	Input* input = Input::inputFromWindow(window);
	if (input)
	{
		if (y < 0)
			input->m_wheel -= 1;
		else if (y > 0)
			input->m_wheel += 1;
		else
			input->m_wheel = 0;
	}
}

Input* Input::inputFromWindow(GLFWwindow*) { return currentInput; }

void Input::poll_gamepad_state()
{
	// Update gamepad state
	m_gamepad_state.connected = false;
	m_gamepad_state.buttons = {};
	m_gamepad_state.axes = {};

	// Check if current gamepad is still connected
	if (m_gamepad_index >= 0 && glfwJoystickPresent(m_gamepad_index))
	{
		bool is_gamepad = glfwJoystickIsGamepad(m_gamepad_index);

		if (is_gamepad)
		{
			// Use GLFW gamepad API for standard controllers
			GLFWgamepadstate state;
			if (glfwGetGamepadState(m_gamepad_index, &state))
			{
				m_gamepad_state.connected = true;

				// Copy button states
				for (size_t i = 0; i < m_gamepad_state.buttons.size() && i <= GLFW_GAMEPAD_BUTTON_LAST; i++)
				{
					m_gamepad_state.buttons[i] = state.buttons[i];
				}

				// Copy axis states
				for (size_t i = 0; i < m_gamepad_state.axes.size() && i <= GLFW_GAMEPAD_AXIS_LAST; i++)
				{
					m_gamepad_state.axes[i] = state.axes[i];
				}

				// Update name if empty
				if (m_gamepad_state.name.empty())
				{
					const char* name = glfwGetGamepadName(m_gamepad_index);
					if (name) m_gamepad_state.name = name;
				}
			}
		}
		else
		{
			// Fall back to raw joystick API for non-standard controllers (e.g., Steam Controller)
			int button_count;
			const unsigned char* buttons = glfwGetJoystickButtons(m_gamepad_index, &button_count);

			int axis_count;
			const float* axes = glfwGetJoystickAxes(m_gamepad_index, &axis_count);

			if (buttons && axes)
			{
				m_gamepad_state.connected = true;

				// Copy button states (clamp to array size)
				for (size_t i = 0; i < m_gamepad_state.buttons.size(); i++)
				{
					if (i < (size_t)button_count)
						m_gamepad_state.buttons[i] = buttons[i];
					else
						m_gamepad_state.buttons[i] = 0;
				}

				// Copy axis states (clamp to array size)
				for (size_t i = 0; i < m_gamepad_state.axes.size(); i++)
				{
					if (i < (size_t)axis_count)
						m_gamepad_state.axes[i] = axes[i];
					else
						m_gamepad_state.axes[i] = 0.0f;
				}

				// Update name if empty
				if (m_gamepad_state.name.empty())
				{
					const char* name = glfwGetJoystickName(m_gamepad_index);
					if (name) m_gamepad_state.name = name;
				}
			}
		}
	}
	else
	{
		// Try to find a connected gamepad/joystick
		for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
		{
			if (glfwJoystickPresent(i))
			{
				m_gamepad_index = i;
				const char* name = glfwGetJoystickName(i);
				if (name) m_gamepad_state.name = name;
				break;
			}
		}
	}

	// Update modifier key state
	m_modifiers.shift = (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
	                     glfwGetKey(m_window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
	m_modifiers.control = (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS ||
	                       glfwGetKey(m_window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS);
	m_modifiers.alt = (glfwGetKey(m_window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
	                   glfwGetKey(m_window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS);
	m_modifiers.super = (glfwGetKey(m_window, GLFW_KEY_LEFT_SUPER) == GLFW_PRESS ||
	                     glfwGetKey(m_window, GLFW_KEY_RIGHT_SUPER) == GLFW_PRESS);
}
} // namespace library
