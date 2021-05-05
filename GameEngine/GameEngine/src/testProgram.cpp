#include "LoggingSystem/Log.h"
#include "GUI/GUI.h"
#include <iostream>
#include <string>

using namespace Logging;

int main()
{
	GUI g;
	//g.initGUI();
	g.Run();
	//GUI::initGUI();
	//GUI::Run();


	/*Log::Init();

	std::string aloha = "hello";
	ENGINE_LOG_INFO("Test_var = {}", aloha);

	CLIENT_LOG_WARN("Initialized client logger");*/
	

	

}

