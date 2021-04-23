#include "libclass.h":
#include "Log.h"

using namespace LOGGING;

int main()
{
	/*libclass test;
	int x = 9;
	int y = 9;
	test.test_function(x,y);*/

	Logging::Log::Init();
	Logging::Log::GetCoreLogger()->critical("Initialized Log");

	

}

