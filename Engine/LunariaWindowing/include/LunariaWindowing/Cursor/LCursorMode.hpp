/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include <LunariaCore/Global/Base.hpp>

namespace Lunaria::Windowing::Cursor {

    /**
    * Some cursor modes.
    * They defines if the mouse pointer should be visible, locked or normal
    */
    enum class LUNARIA_API LCursorMode
    {
        NORMAL = 0x00034001,
        DISABLED = 0x00034003,
        HIDDEN = 0x00034002
    };

}
