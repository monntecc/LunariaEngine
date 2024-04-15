/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include "LunariaECS/Components/AComponent.hpp"

namespace Lunaria::ECS::Components {

    class ATag : public AComponent
    {
    public:
        ATag() = default;
        ATag(const ATag&) = default;
        ATag(std::string tag) : Tag(std::move(tag)) {}

    public:
        std::string Tag;
    };

}
