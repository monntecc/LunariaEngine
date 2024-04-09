#include "lepch.hpp"

#include "LunariaCore/Renderer/RenderCommand.hpp"

#include "LunariaCore/RHI/OpenGL/OpenGLRendererAPI.hpp"

namespace Lunaria {

	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
