#pragma once
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace UI
{
	class GUI
	{
	public:
		static void initGUI();


	private:
		static GLFWwindow* window;


	};
}


