#pragma once

#include "spdlog/spdlog.h"


namespace Logging
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { 
			return s_CoreLogger; 
		}
		inline static std::shared_ptr<spdlog::logger>& ClientLogger() {
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

