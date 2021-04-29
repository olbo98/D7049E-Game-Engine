#pragma once
#include "../opengl/glew-2.1.0/include/GL/glew.h"
#include "imgui.h"
#include "../imgui/backends/imgui_impl_glfw.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/examples/libs/glfw/include/GLFW/glfw3.h"

namespace UI
{
	class GUI
	{
	public:
		static void initGUI();
		static void Run();

	private:
		static GLFWwindow* window;


	};
}


