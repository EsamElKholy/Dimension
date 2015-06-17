#pragma once

#include <GL\glew.h>

#include <iostream>
#include <GLFW\glfw3.h>
#include "Input.h"
#include "..\Audio\SoundManager.h"

class ScreenManager
{
public:
	ScreenManager(void);
	ScreenManager(int width ,int height ,char *title);
	~ScreenManager(void);

	bool init();

	inline static int getWidth(){ return m_Width; }
	inline static int getHeight(){ return m_Height; }

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

