#pragma once

#include "LunariaCore/Global/Base.hpp"
#include "LunariaCore/Global/Timestep.hpp"

#include "LunariaCore/Events/Event.hpp"

namespace Lunaria
{
	class LUNARIA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}