#include "GUI.h"
#include "examples/libs/glfw/include/GLFW/glfw3.h"

namespace UI
{

	void GUI::initGUI() {
		window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui::StyleColorsDark();
	}
}