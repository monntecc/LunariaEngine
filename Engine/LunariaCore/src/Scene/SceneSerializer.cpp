#include "lepch.hpp"

#include "LunariaCore/Scene/SceneSerializer.hpp"
#include "LunariaCore/Scene/Entity.hpp"
#include "LunariaCore/Scene/Components.hpp"

using json = nlohmann::json;

namespace Lunaria {

    SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
        : m_Scene(scene)
    {
    }

    void SceneSerializer::Serialize(const std::string& filepath)
    {
        json j = *m_Scene.get();

        // Write to file
        std::ofstream file(filepath);
        file << j.dump(2);
        file.close();
    }

    void SceneSerializer::SerializeRuntime(const std::string& filepath)
    {
        // TODO: Implement
        LU_CORE_ASSERT(false);
    }

    bool SceneSerializer::Deserialize(const std::string& filepath)
    {
        // Read file
        std::ifstream file(filepath);
        json::parse(file).get_to(*m_Scene);

        return true;
    }

    bool SceneSerializer::DeserializeRuntime(const std::string& filepath)
    {
        // TODO: Implement
        LU_CORE_ASSERT(false);
        return false;
    }

}
