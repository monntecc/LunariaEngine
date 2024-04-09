﻿#include "lepch.hpp"

#include "LunariaCore/Renderer/Texture.hpp"
#include "LunariaCore/Renderer/Renderer.hpp"

#include "LunariaCore/RHI/OpenGL/OpenGLTexure.hpp"

namespace Lunaria {
    
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(path);

        case RendererAPI::API::None:    
            LU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        }

        LU_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::OpenGL:
            return CreateRef<OpenGLTexture2D>(width, height);

        case RendererAPI::API::None:    
            LU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
            return nullptr;
        }

        LU_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

}
