#pragma once

#include <glm/glm.hpp>
#include <nlohmann/json.hpp>

namespace glm {

    static void to_json(nlohmann::json& j, const vec3& vec)
    {
        j = nlohmann::json{ vec.x, vec.y, vec.z };
    }

    static void from_json(const nlohmann::json& j, vec3& vec)
    {
        vec.x = j[0];
        vec.y = j[1];
        vec.z = j[2];
    }

}
