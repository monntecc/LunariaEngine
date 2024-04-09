#include "lepch.hpp"

#include "LunariaCore/Renderer/RendererAPI.hpp"

#include "LunariaCore/RHI/OpenGL/OpenGLRendererAPI.hpp"

namespace Lunaria {

	RendererAPI::API RendererAPI::s_RendererAPI = API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_RendererAPI)
		{
		case API::None:
			LU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			
		case API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
		}

		LU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
