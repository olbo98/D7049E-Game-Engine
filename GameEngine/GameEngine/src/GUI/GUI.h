#pragma once
#include "GL/glew.h"
#include "../Imgui/glfw3.h"
#include "../Imgui/imgui.h"
#include "../Imgui/imgui_impl_glfw.h"
#include "../Imgui/imgui_impl_opengl3.h"

//#include "GLFW/glfw3.h"

class GUI
{
public:
	GUI();
	//void initGUI();
	void Run();

private:
	GLFWwindow* window;


};



