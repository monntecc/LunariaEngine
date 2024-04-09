#include "lepch.hpp"

#include "LunariaCore/Scene/Entity.hpp"
#include "LunariaCore/Scene/Scene.hpp"

namespace Lunaria {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}