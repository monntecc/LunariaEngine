#pragma once

#include "LunariaCore/Core/Base.hpp"

#include "LunariaCore/Renderer/Texture.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

namespace Lunaria::UI {

	enum class LUNARIA_API ImageFormat
	{
		None = 0,
		RGBA,
		RGBA32F
	};

	void LUNARIA_API ShiftCursorX(float distance);
	void LUNARIA_API ShiftCursorY(float distance);
	void LUNARIA_API ShiftCursor(float x, float y);

	ImRect LUNARIA_API GetItemRect();
	ImRect LUNARIA_API RectExpanded(const ImRect& rect, float x, float y);
	ImRect LUNARIA_API RectOffset(const ImRect& rect, float x, float y);
	ImRect LUNARIA_API RectOffset(const ImRect& rect, ImVec2 xy);

	void LUNARIA_API DrawButtonImage(const Ref<Texture2D>& imageNormal, const Ref<Texture2D>& imageHovered, const Ref<Texture2D>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImVec2 rectMin, ImVec2 rectMax);

	void LUNARIA_API DrawButtonImage(const Ref<Texture2D>& imageNormal, const Ref<Texture2D>& imageHovered, const Ref<Texture2D>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImRect rectangle);

	void LUNARIA_API DrawButtonImage(const Ref<Texture2D>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImVec2 rectMin, ImVec2 rectMax);

	void LUNARIA_API DrawButtonImage(const Ref<Texture2D>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed,
		ImRect rectangle);

	void LUNARIA_API DrawButtonImage(const Ref<Texture2D>& imageNormal, const Ref<Texture2D>& imageHovered, const Ref<Texture2D>& imagePressed,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed);

	void LUNARIA_API DrawButtonImage(const Ref<Texture2D>& image,
		ImU32 tintNormal, ImU32 tintHovered, ImU32 tintPressed);
}