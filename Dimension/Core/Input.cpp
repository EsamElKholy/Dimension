#include "Input.h"

bool Input::keys[1024];
bool Input::buttons[32];

vec2 Input::mousePos;

GLFWwindow *Input::m_window;

Input::Input(void)
{
}


Input::~Input(void)
{
}

Input::Input(GLFWwindow *window){
	m_window = window;

	for (int i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}

	for (int i = 0; i < 32; i++)
	{
		buttons[i] = false;
	}

	glfwSetKeyCallback(m_window, key_call);
	glfwSetMouseButtonCallback(m_window, mouse_button_call);
	glfwSetCursorPosCallback(m_window, cursor_position_call);
}

void Input::enableCursor(const int &state){
	glfwSetInputMode(m_window, GLFW_CURSOR, state);
}

void Input::key_call(GLFWwindow* window, int key, int scancode, int action, int mods){
	keys[key] = (action != GLFW_RELEASE);
}

void Input::mouse_button_call(GLFWwindow* window, int button, int action, int mods){
	buttons[button] = (action != GLFW_RELEASE);
}

void Input::cursor_position_call(GLFWwindow* window, double xpos, double ypos){
	mousePos.x = (float)xpos;
	mousePos.y = (float)ypos;
}

bool Input::isKeyPressed(int key){
	return keys[key];
}

bool Input::ismouseButtonPressed(int button){
	return buttons[button];
}

void Input::setMousePos(const vec2 &pos){
	glfwSetCursorPos(m_window, (double)pos.x, (double)pos.y);
}

vec2 Input::getMousePos(){
	return mousePos;
}