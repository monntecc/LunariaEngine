#pragma once

#include "LunariaCore/Scene/Scene.hpp"

#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

namespace Lunaria {

	class LUNARIA_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			LU_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			// m_Scene->OnComponentAdded<T>(*this, component); TODO: Fix this later
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			LU_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_Scene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent() const
		{
			LU_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		explicit operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return static_cast<uint32_t>(m_EntityHandle); }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};

    static void to_json(nlohmann::json& j, const Entity& entity);
    static void from_json(const nlohmann::json& j, Entity& entity);

}
