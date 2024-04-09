#pragma once

#include "LunariaCore/Renderer/GraphicsContext.hpp"

struct SDL_Window;

namespace Lunaria {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(SDL_Window* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		SDL_Window* m_WindowHandle;
	};
}
