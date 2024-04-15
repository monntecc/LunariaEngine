#pragma once

#include "LunariaCore/Global/Base.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 3)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Lunaria {

	class LUNARIA_API Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		enum Level : int {
			Trace = SPDLOG_LEVEL_TRACE,
			Debug = SPDLOG_LEVEL_DEBUG,
			Info = SPDLOG_LEVEL_INFO,
			Warn = SPDLOG_LEVEL_WARN,
			Error = SPDLOG_LEVEL_ERROR,
			Critical = SPDLOG_LEVEL_CRITICAL,
			Off = SPDLOG_LEVEL_OFF
		};

		// Clear logs
		static void ClearLogs();

		static std::vector<std::string> GetLogs();
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;

		inline static std::string s_LogFileName;
	};

}

// Core log macros, used for the engine
// Add each new log level and its text to vector
#define LU_CORE_TRACE(...)			::Lunaria::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LU_CORE_INFO(...)			::Lunaria::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LU_CORE_WARN(...)			::Lunaria::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LU_CORE_ERROR(...)			::Lunaria::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LU_CORE_CRITICAL(...)		::Lunaria::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros, used for the client
#define LU_TRACE(...)				::Lunaria::Log::GetClientLogger()->trace(__VA_ARGS__) 
#define LU_INFO(...)				::Lunaria::Log::GetClientLogger()->info(__VA_ARGS__)
#define LU_WARN(...)				::Lunaria::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LU_ERROR(...)				::Lunaria::Log::GetClientLogger()->error(__VA_ARGS__)
#define LU_CRITICAL(...)			::Lunaria::Log::GetClientLogger()->critical(__VA_ARGS__)