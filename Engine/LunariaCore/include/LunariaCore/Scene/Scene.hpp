#pragma once

#include "LunariaCore/Global/Timestep.hpp"

#include <entt/entt.hpp>
#include <nlohmann/json.hpp>

namespace Lunaria {

	class Entity;

	class LUNARIA_API Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdate(Timestep timestep);
		void OnViewportResize(uint32_t width, uint32_t height);
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);
	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

        friend void to_json(nlohmann::json& j, const Scene& scene);
        friend void from_json(const nlohmann::json& j, Scene& scene);

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};

}
