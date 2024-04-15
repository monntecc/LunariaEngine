#include "lepch.hpp"

#include "LunariaCore/Global/Log.hpp"

#pragma warning(push, 3) 
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#pragma warning(pop)

namespace Lunaria {

	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

		const time_t now = time(nullptr);
		const tm* ltm = localtime(&now);
		// Create a log file with the current date and time, for example: Logs/Startup-2021-09-01_12-00-00.log
		s_LogFileName = "Logs/Startup-" + std::to_string(1900 + ltm->tm_year) + "-" + std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(ltm->tm_mday) + "_" + std::to_string(ltm->tm_hour) + "-" + std::to_string(ltm->tm_min) + "-" + std::to_string(ltm->tm_sec) + ".log";
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(s_LogFileName, true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$"); 
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_CoreLogger = std::make_shared<spdlog::logger>("RUNTIME", begin(logSinks), end(logSinks));
		register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>("EDITOR", begin(logSinks), end(logSinks));
		register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}

	void Log::ClearLogs()
	{
		// Clear the log file
		std::ofstream ofs;
		ofs.open(s_LogFileName, std::ofstream::out | std::ofstream::trunc);
		ofs.close();
	}

	std::vector<std::string> Log::GetLogs()
	{
		std::vector<std::string> s_Logs;
		std::ifstream file(s_LogFileName);
		std::string str;
		while (std::getline(file, str))
		{
			s_Logs.push_back(str);
		}
		return s_Logs;
	}
}
