#include "lepch.hpp"

#include "LunariaCore/RHI/OpenGL/OpenGLContext.hpp"

#include <glad/glad.h>

#include <SDL/SDL.h>

namespace Lunaria {

	OpenGLContext::OpenGLContext(SDL_Window* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LU_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		SDL_GL_CreateContext(m_WindowHandle);
		int status = gladLoadGLLoader(SDL_GL_GetProcAddress);
		LU_CORE_ASSERT(status, "Failed to initialize Glad!");

		LU_CORE_INFO("OpenGL Info:");
		LU_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		LU_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		LU_CORE_INFO("  Version: {0}\n", reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		LU_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Lunaria requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		SDL_GL_SwapWindow(m_WindowHandle);
	}

}
