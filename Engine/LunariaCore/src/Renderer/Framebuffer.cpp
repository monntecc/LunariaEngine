#include "lepch.hpp"

#include "LunariaCore/Renderer/FrameBuffer.hpp"
#include "LunariaCore/Renderer/Renderer.hpp"

#include "LunariaCore/RHI/OpenGL/OpenGLFrameBuffer.hpp"

namespace Lunaria {

	Ref<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& specification)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(specification);

		case RendererAPI::API::None:
			LU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		}

		LU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	
}
