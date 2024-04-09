#include "lepch.hpp"

#include "LunariaCore/Renderer/GraphicsContext.hpp"

#include "LunariaCore/Renderer/Renderer.hpp"
#include "LunariaCore/RHI/OpenGL/OpenGLContext.hpp"

namespace Lunaria {

    Scope<GraphicsContext> GraphicsContext::Create(void* window)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            LU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            
        case RendererAPI::API::OpenGL:
            return CreateScope<OpenGLContext>(static_cast<SDL_Window*>(window));
        }

        LU_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}