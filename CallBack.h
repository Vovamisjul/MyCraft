#pragma once
#include <glew.h>
#include <glfw3.h>
#include "Control.h"
static class CallBack {
public:
	static void Initialize(Control *control);
	static void Mouse(GLFWwindow* window, double xpos, double ypos);
	static void MouseButton(GLFWwindow* window, int button, int action, int mods);
	static void Key(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void Scroll(GLFWwindow* window, double xoffset, double yoffset);
private:
	static Control *control;
};