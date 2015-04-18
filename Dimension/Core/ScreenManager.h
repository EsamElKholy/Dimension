#pragma once

#include <GL\glew.h>

#include <iostream>
#include <GLFW\glfw3.h>
#include "Input.h"
	

class ScreenManager
{
public:
	ScreenManager(void);
	ScreenManager(int width ,int height ,char *title);
	~ScreenManager(void);

	bool init();

	static int getWidth();
	static int getHeight();

	void clear() const;
	void update() const;
	void render() const;
	void dispose() const;
	bool isClosed() const;

private:
	static int m_Width ,m_Height;
	char *m_Title;

	Input input;
	GLFWwindow *window;

};

