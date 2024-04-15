#include "LunariaEditor/Widgets/TitlebarWidget.hpp"

namespace Lunaria {

	TitlebarWidget::TitlebarWidget()
	{
		// Load images
		m_AppHeaderIcon = Texture2D::Create("Resources/Icons/Logo.png");
		m_IconMinimize = Texture2D::Create("Resources/Icons/Minimize.png");
		m_IconMaximize = Texture2D::Create("Resources/Icons/Maximize.png");
		m_IconRestore = Texture2D::Create("Resources/Icons/Restore.png");
		m_IconClose = Texture2D::Create("Resources/Icons/Close.png");
	}

	void TitlebarWidget::DrawUITitlebar()
	{
		const auto& window = Application::Get().GetWindow();

        constexpr float titlebarHeight = 50.0f;
		const bool isMaximized = window.IsMaximized();
		float titlebarVerticalOffset = isMaximized ? -6.0f : 0.0f;
		const ImVec2 windowPadding = ImGui::GetCurrentWindow()->WindowPadding;

		ImGui::SetCursorPos(ImVec2(windowPadding.x, windowPadding.y + titlebarVerticalOffset));
		const ImVec2 titlebarMin = ImGui::GetCursorScreenPos();
		const ImVec2 titlebarMax = { ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth() - windowPadding.y * 2.0f,
									 ImGui::GetCursorScreenPos().y + titlebarHeight };
		auto* fgDrawList = ImGui::GetForegroundDrawList();
		//fgDrawList->AddRectFilled(titlebarMin, titlebarMax, UI::Colors::Theme::titlebar);
		// DEBUG TITLEBAR BOUNDS
		//fgDrawList->AddRect(titlebarMin, titlebarMax, UI::Colors::Theme::invalidPrefab);

		// Logo
		{
			constexpr int logoWidth = 32;// m_LogoTex->GetWidth();
            constexpr int logoHeight = 32; // m_LogoTex->GetHeight();
			const ImVec2 logoOffset(16.0f + windowPadding.x, 5.0f + windowPadding.y + titlebarVerticalOffset);
			const ImVec2 logoRectStart = { ImGui::GetWindowPos().x + logoOffset.x, ImGui::GetWindowPos().y + logoOffset.y };
			const ImVec2 logoRectMax = { logoRectStart.x + logoWidth, logoRectStart.y + logoHeight };
			fgDrawList->AddImage(reinterpret_cast<void*>(m_AppHeaderIcon->GetRendererID()), logoRectStart, logoRectMax);
		}

		ImGui::BeginHorizontal("Titlebar", { ImGui::GetWindowWidth() - windowPadding.y * 2.0f, ImGui::GetFrameHeightWithSpacing() });

		static float moveOffsetX;
		static float moveOffsetY;
		const float w = ImGui::GetContentRegionAvail().x;
		constexpr float buttonsAreaWidth = 94;

		// Title bar drag area
		// On Windows we hook into the GLFW win32 window internals
		ImGui::SetCursorPos(ImVec2(windowPadding.x, windowPadding.y + titlebarVerticalOffset)); // Reset cursor pos
		// DEBUG DRAG BOUNDS
		//fgDrawList->AddRect(ImGui::GetCursorScreenPos(), ImVec2(ImGui::GetCursorScreenPos().x + w - buttonsAreaWidth, ImGui::GetCursorScreenPos().y + titlebarHeight), UI::Colors::Theme::invalidPrefab);
		ImGui::InvisibleButton("##titleBarDragZone", ImVec2(w - buttonsAreaWidth, titlebarHeight));

		m_TitleBarHovered = ImGui::IsItemHovered();

		if (m_TitleBarHovered && ImGui::IsMouseDown(ImGuiMouseButton_Left))
		{
			window.StartDrag();
		}

		if (isMaximized)
		{
			float windowMousePosY = ImGui::GetMousePos().y - ImGui::GetCursorScreenPos().y;
			if (windowMousePosY >= 0.0f && windowMousePosY <= 5.0f)
				m_TitleBarHovered = true; // Account for the top-most pixels which don't register
		}

		// Draw Menubar
		{
			ImGui::SuspendLayout();
			{
				ImGui::SetItemAllowOverlap();
				const float logoHorizontalOffset = 16.0f * 2.0f + 48.0f + windowPadding.x;
				ImGui::SetCursorPos(ImVec2(logoHorizontalOffset, 6.0f + titlebarVerticalOffset));
				m_MenubarWidget.Draw();

				if (ImGui::IsItemHovered())
					m_TitleBarHovered = false;
			}

			ImGui::ResumeLayout();
		}

		{
			// Centered Window title
			ImVec2 currentCursorPos = ImGui::GetCursorPos();
			ImVec2 textSize = ImGui::CalcTextSize(window.GetWindowData().Title.c_str());
			ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() * 0.5f - textSize.x * 0.5f, 2.0f + windowPadding.y + 6.0f));
			ImGui::Text("%s", window.GetWindowData().Title.c_str()); // Draw title
			ImGui::SetCursorPos(currentCursorPos);
		}

		// Window buttons
        const ImU32 buttonColN = UI::Colors::ColorWithMultipliedValue(IM_COL32(192, 192, 192, 255), 0.9f);
        const ImU32 buttonColH = UI::Colors::ColorWithMultipliedValue(IM_COL32(192, 192, 192, 255), 1.2f);
        constexpr ImU32 buttonColP = IM_COL32(128, 128, 128, 255);
        constexpr float buttonWidth = 14.0f;
        constexpr float buttonHeight = 14.0f;

		// Minimize Button

		ImGui::Spring();
		UI::ShiftCursorY(8.0f);
		{
			const int iconHeight = static_cast<int>(m_IconMinimize->GetHeight());
			const float padY = (buttonHeight - static_cast<float>(iconHeight)) / 2.0f;
			if (ImGui::InvisibleButton("Minimize", ImVec2(buttonWidth, buttonHeight)))
			{
				window.Minimize();
			}

			UI::DrawButtonImage(m_IconMinimize, buttonColN, buttonColH, buttonColP, UI::RectExpanded(UI::GetItemRect(), 0.0f, -padY));
		}

		// Maximize Button
		ImGui::Spring(-1.0f, 17.0f);
		UI::ShiftCursorY(8.0f);
		{
			if (ImGui::InvisibleButton("Maximize", ImVec2(buttonWidth, buttonHeight)))
			{
				window.Maximize(isMaximized);
			}

			UI::DrawButtonImage(isMaximized ? m_IconRestore : m_IconMaximize, buttonColN, buttonColH, buttonColP);
		}

		// Close Button
		ImGui::Spring(-1.0f, 15.0f);
		UI::ShiftCursorY(8.0f);
		{
			if (ImGui::InvisibleButton("Close", ImVec2(buttonWidth, buttonHeight)))
				Application::Get().Shutdown();

			UI::DrawButtonImage(m_IconClose, IM_COL32(192, 192, 192, 255), UI::Colors::ColorWithMultipliedValue(IM_COL32(192, 192, 192, 255), 1.4f), buttonColP);
		}

		ImGui::Spring(-1.0f, 18.0f);
		ImGui::EndHorizontal();

		ImGui::SetCursorPosY(titlebarHeight);
	}

}
