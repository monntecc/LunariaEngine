/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include <LunariaMath/LMatrix4.hpp>
#include <LunariaMath/LVector3.hpp>

#include "LunariaECS/Components/AComponent.hpp"

namespace Lunaria::ECS::Components {

    class ATransform : public AComponent
    {
    public:
        ATransform() = default;
        ATransform(const ATransform&) = default;
        ATransform(Math::LVector3 translation) : Translation(std::move(translation)) {}

        Math::LMatrix4 GetTransform() const
        {
            Math::LMatrix4 rotation = Math::LMatrix4::Rotate(Math::LMatrix4::One, Math::LQuaternion{ 1.0f, 0.0f, 0.0f, Rotation.x })
                * Math::LMatrix4::Rotate(Math::LMatrix4::One, Math::LQuaternion{ 0.0f, 1.0f, 0.0f, Rotation.y })
                * Math::LMatrix4::Rotate(Math::LMatrix4::One, Math::LQuaternion{ 0.0f, 0.0f, 1.0f, Rotation.z });

            return Math::LMatrix4::Translate(Math::LMatrix4::One, Translation)
                * rotation
                * Math::LMatrix4::Scale(Math::LMatrix4::One, Scale);
        }

    public:
        Lunaria::Math::LVector3 Translation = { 0.0f, 0.0f, 0.0f };
        Lunaria::Math::LVector3 Rotation = { 0.0f, 0.0f, 0.0f };
        Lunaria::Math::LVector3 Scale = { 1.0f, 1.0f, 1.0f };
    };

}
