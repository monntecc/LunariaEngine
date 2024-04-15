/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include "LunariaECS/Components/AComponent.hpp"

namespace Lunaria { class SceneCamera; }

namespace Lunaria::ECS::Components {

    class ACamera : public AComponent
    {
    public:
        ACamera() = default;
        ACamera(const ACamera&) = default;

    public:
        SceneCamera Camera;
        bool Primary = true; // TODO: think about moving to Scene

        bool FixedAspectRatio = false;
    };

}
