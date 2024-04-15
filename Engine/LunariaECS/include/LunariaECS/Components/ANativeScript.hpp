/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include "LunariaECS/Components/AComponent.hpp"

namespace Lunaria { class ScriptableEntity; }

namespace Lunaria::ECS::Components {

    class ANativeScript : public AComponent
    {
    public:
        ScriptableEntity* (*InstantiateScript)();
        void (*DestroyScript)(ANativeScript*);

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
            DestroyScript = [](ANativeScript* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
        }

    public:
        ScriptableEntity* Instance = nullptr;
    };

}
