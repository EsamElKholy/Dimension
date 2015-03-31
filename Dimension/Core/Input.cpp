#include "Input.h"

bool Input::keys[1024];
std::pair<double, double> Input::mousePos;

Input::Input(void)
{
}


Input::~Input(void)
{
}

Input::Input(GLFWwindow *window){
	for (int i = 0; i < 1024; i++)
	{
		keys[i] = false;
	}

	glfwSetKeyCallback(window, key_call);
	glfwSetCursorPosCallback(window, cursor_position_call);
}

void Input::key_call(GLFWwindow* window, int key, int scancode, int action, int mods){
	keys[key] = (action != GLFW_RELEASE);
}

void Input::cursor_position_call(GLFWwindow* window, double xpos, double ypos){
	mousePos.first = xpos;
	mousePos.second = ypos;
}

bool Input::isKeyPressed(int key){
	return keys[key];
}