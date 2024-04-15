#pragma once

#include "LunariaCore/Global/Base.hpp"

#include "LunariaCore/Global/KeyCodes.hpp"
#include "LunariaCore/Global/MouseCodes.hpp"

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