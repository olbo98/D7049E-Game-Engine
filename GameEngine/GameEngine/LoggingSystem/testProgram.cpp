#include "libclass.h"
#include "Log.h"
#include <iostream>
#include <string>

using namespace Logging;


int main()
{
	/*libclass test;
	int x = 9;
	int y = 9;
	test.test_function(x,y);*/

	Log::Init();

	std::string aloha = "hello";
	ENGINE_LOG_INFO("Test_var = {}", aloha);

	CLIENT_LOG_WARN("Initialized client logger");
	
	

}

