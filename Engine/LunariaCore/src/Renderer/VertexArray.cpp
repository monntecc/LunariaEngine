#include "lepch.hpp"

#include "LunariaCore/Renderer/VertexArray.hpp"
#include "LunariaCore/Renderer/Renderer.hpp"

#include "LunariaCore/RHI/OpenGL/OpenGLVertexArray.hpp"

namespace Lunaria {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();

		case RendererAPI::API::None:    
			LU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		LU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}
