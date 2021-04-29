#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Logging
{
	std::shared_ptr<spdlog::logger>	Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger>	Log::s_ClientLogger;

	void Log::Init()
	{
		//formatting the log format to -> [HH:MM:SS] [log_level] (my_loggername) [the actual text to log] 
		spdlog::set_pattern("%^[%T] [%l] (%n) %v %$");
		
		//Creating the enginelogger and the applicationlogger
		s_CoreLogger = spdlog::stdout_color_mt("ENGINE LOG");
		
		
		//s_CoreLogger->set_level(spdlog::level::trace);
		//s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APPLICATION LOG");
		//s_ClientLogger->set_level(spdlog::level::trace);


	}
}