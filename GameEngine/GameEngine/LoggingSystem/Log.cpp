#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Logging
{
	std::shared_ptr<spdlog::logger>	Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger>	Log::s_ClientLogger;

	void Log::Init()
	{
		//formatting the log format to -> [2014-10-31 23:46:59.678] [my_loggername] [info] Some message
		//spdlog::set_pattern("[%H:%M:%S %z] [thread %t] %v");
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		//Creating the enginelogger and the applicationlogger
		s_CoreLogger = spdlog::stdout_color_mt("ENGINE LOG");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APPLICATION");
		s_ClientLogger->set_level(spdlog::level::trace);


	}
}