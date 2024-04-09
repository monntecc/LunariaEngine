#pragma once

#include "LunariaCore/Renderer/RendererAPI.hpp"

namespace Lunaria {

	class LUNARIA_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;

		void SetViewport(int x, int y, uint32_t width, uint32_t height) override;
		
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
	};

}
