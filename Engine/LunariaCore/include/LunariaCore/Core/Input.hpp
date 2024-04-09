#pragma once

#include "LunariaCore/Core/Base.hpp"

#include "LunariaCore/Core/KeyCodes.hpp"
#include "LunariaCore/Core/MouseCodes.hpp"

#include <glm/glm.hpp>

namespace Lunaria {

	class LUNARIA_API Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();

		static float GetMouseX();
		static float GetMouseY();
	};

}