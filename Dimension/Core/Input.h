#pragma once

#include "GLFW\glfw3.h"
#include <vector>

class Input
{
public:
	Input(void);
	Input(GLFWwindow *window);
	~Input(void);

	static bool isKeyPressed(int key);
	static void key_call(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void cursor_position_call(GLFWwindow* window, double xpos, double ypos);
private:
	static bool keys[1024];
	static std::pair<double, double> mousePos;
};

