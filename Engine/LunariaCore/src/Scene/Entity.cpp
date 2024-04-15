#include "lepch.hpp"

#include "LunariaCore/Scene/Entity.hpp"
#include "LunariaCore/Scene/Components.hpp"
#include "LunariaCore/Scene/Scene.hpp"

#include "LunariaCore/Scene/JsonTypes.hpp"

using json = nlohmann::json;

namespace Lunaria {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

    [[maybe_unused]] static void to_json(json& j, const Entity& entity)
    {
        Entity& entity_ = const_cast<Entity&>(entity); // TODO: Fix this later

        j = json{
            { "Entity", "12345 "}, // TODO: Entity ID goes here
            {"TagComponent", {
                {"Tag", entity_.GetComponent<TagComponent>().Tag}
            }},
            {"TransformComponent", {
                {"Translation", entity_.GetComponent<TransformComponent>().Translation},
                {"Rotation", entity_.GetComponent<TransformComponent>().Rotation},
                {"Scale", entity_.GetComponent<TransformComponent>().Scale}
            }},
            {"CameraComponent", {
                {"Camera", {
                    {"ProjectionType", static_cast<int>(entity_.GetComponent<CameraComponent>().Camera.GetProjectionType())},
                    {"PerspectiveFOV", entity_.GetComponent<CameraComponent>().Camera.GetPerspectiveVerticalFOV()},
                    {"PerspectiveNear", entity_.GetComponent<CameraComponent>().Camera.GetPerspectiveNearClip()},
                    {"PerspectiveFar", entity_.GetComponent<CameraComponent>().Camera.GetPerspectiveFarClip()},
                    {"OrthographicSize", entity_.GetComponent<CameraComponent>().Camera.GetOrthographicSize()},
                    {"OrthographicNear", entity_.GetComponent<CameraComponent>().Camera.GetOrthographicNearClip()},
                    {"OrthographicFar", entity_.GetComponent<CameraComponent>().Camera.GetOrthographicFarClip()}
                }},
                {"Primary", entity_.GetComponent<CameraComponent>().Primary}
            }}
        
        };
    }

    [[maybe_unused]] static void from_json(const json& j, Entity& entity)
    {
        j.at("TagComponent").at("Tag").get_to(entity.GetComponent<TagComponent>().Tag);
        j.at("TransformComponent").at("Translation").get_to(entity.GetComponent<TransformComponent>().Translation);
        j.at("TransformComponent").at("Rotation").get_to(entity.GetComponent<TransformComponent>().Rotation);
        j.at("TransformComponent").at("Scale").get_to(entity.GetComponent<TransformComponent>().Scale);
        entity.GetComponent<CameraComponent>().Camera.SetProjectionType(j.at("CameraComponent").at("Camera").at("ProjectionType").get<SceneCamera::ProjectionType>());
        entity.GetComponent<CameraComponent>().Camera.SetPerspectiveVerticalFOV(j.at("CameraComponent").at("Camera").at("PerspectiveFOV").get<float>());
        entity.GetComponent<CameraComponent>().Camera.SetPerspectiveNearClip(j.at("CameraComponent").at("Camera").at("PerspectiveNear").get<float>());
        entity.GetComponent<CameraComponent>().Camera.SetPerspectiveFarClip(j.at("CameraComponent").at("Camera").at("PerspectiveFar").get<float>());
        entity.GetComponent<CameraComponent>().Camera.SetOrthographicSize(j.at("CameraComponent").at("Camera").at("OrthographicSize").get<float>());
        entity.GetComponent<CameraComponent>().Camera.SetOrthographicNearClip(j.at("CameraComponent").at("Camera").at("OrthographicNear").get<float>());
        entity.GetComponent<CameraComponent>().Camera.SetOrthographicFarClip(j.at("CameraComponent").at("Camera").at("OrthographicFar").get<float>());
        j.at("CameraComponent").at("Primary").get_to(entity.GetComponent<CameraComponent>().Primary);
    }

}
