/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include <LunariaCore/Global/Base.hpp>

namespace Lunaria::Windowing::Cursor {

    /**
    * Some cursor shapes.
    * They specify how the mouse pointer should look
    */
    enum class LUNARIA_API LCursorShape
    {
        ARROW = 0x00036001,
        IBEAM = 0x00036002,
        CROSSHAIR = 0x00036003,
        HAND = 0x00036004,
        HRESIZE = 0x00036005,
        VRESIZE = 0x00036006
    };

}
