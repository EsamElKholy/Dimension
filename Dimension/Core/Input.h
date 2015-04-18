#pragma once

#include "GLFW\glfw3.h"
#include "..\Math\vec2.h"

class Input
{
public:
	Input(void);
	Input(GLFWwindow *window);
	~Input(void);

	static bool isKeyPressed(int key);
	static bool ismouseButtonPressed(int key);

	static void setMousePos(const vec2 &pos);

	static vec2 getMousePos();

	static void enableCursor(const int &state);

	static void key_call(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_call(GLFWwindow* window, int button, int action, int mods);
	static void cursor_position_call(GLFWwindow* window, double xpos, double ypos);
private:
	static bool keys[1024];
	static bool buttons[32];
	static vec2 mousePos;
	static GLFWwindow *m_window;
};

