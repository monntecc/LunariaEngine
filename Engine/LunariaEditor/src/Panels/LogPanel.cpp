#include "LunariaEditor/Panels/LogPanel.hpp"

#include <imgui/imgui.h>

namespace Lunaria {

	LogPanel::LogPanel()
	{
	}

	void LogPanel::Draw()
	{
		ImGui::Begin("Log");

		if (ImGui::Button("Clear"))
		{
			Log::ClearLogs();
		}

		const auto logs = Log::GetLogs();

		// Loop through all logs
		for (const auto& log : logs)
		{
			ImGui::Text(log.c_str());
		}

		ImGui::End();
	}

}