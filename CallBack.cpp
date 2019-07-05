#include "CallBack.h"

Control *CallBack::control;

void CallBack::Initialize(Control *_control)
{
	control = _control;
}

void CallBack::Mouse(GLFWwindow* window, double xpos, double ypos)
{
	control->mouse_callback(window, xpos, ypos);
}

void CallBack::MouseButton(GLFWwindow* window, int button, int action, int mods)
{
	control->mouse_button_callback(window, button, action, mods);
}


void CallBack::Key(GLFWwindow* window, int key, int scancode, int action, int mode) 
{
	control->key_callback(window, key, scancode, action, mode);
}

void CallBack::Scroll(GLFWwindow* window, double xoffset, double yoffset)
{
	control->scroll_callback(window, xoffset, yoffset);
}