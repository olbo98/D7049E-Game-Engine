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
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() {
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Enginge log macros
#define ENGINE_LOG_ERROR(...)			::Logging::Log::GetCoreLogger()->error(__VA_ARGS__);
#define ENGINE_LOG_WARN(...)			::Logging::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define ENGINE_LOG_INFO(...)			::Logging::Log::GetCoreLogger()->info(__VA_ARGS__);
#define ENGINE_LOG_TRACE(...)			::Logging::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define ENGINE_LOG_CRITICAL(...)		::Logging::Log::GetCoreLogger()->critical(__VA_ARGS__);

// Client log macros
#define CLIENT_LOG_ERROR(...)			::Logging::Log::GetClientLogger()->error(__VA_ARGS__);
#define CLIENT_LOG_WARN(...)			::Logging::Log::GetClientLogger()->warn(__VA_ARGS__);
#define CLIENT_LOG_INFO(...)			::Logging::Log::GetClientLogger()->info(__VA_ARGS__);
#define CLIENT_LOG_TRACE(...)			::Logging::Log::GetClientLogger()->trace(__VA_ARGS__);
#define CLIENT_LOG_CRITICAL(...)		::Logging::Log::GetClientLogger()->critical(__VA_ARGS__);