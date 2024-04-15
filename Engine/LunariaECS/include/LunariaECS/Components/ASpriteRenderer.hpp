/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include <LunariaMath/LVector4.hpp>

#include "LunariaECS/Components/AComponent.hpp"

namespace Lunaria::ECS::Components {

    class ASpriteRenderer : public AComponent
    {
    public:
        ASpriteRenderer() = default;
        ASpriteRenderer(const ASpriteRenderer&) = default;
        ASpriteRenderer(Math::LVector4 color) : Color(std::move(color)) {}

    public:
        Math::LVector4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };
    };

}
