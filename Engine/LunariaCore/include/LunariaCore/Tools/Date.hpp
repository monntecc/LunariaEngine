/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include "LunariaCore/Global/Base.hpp"

namespace Lunaria::Tools {

    /*
    * Date system to get the current date in a string format
    */
    class LUNARIA_API Date
    {
    public:
        /**
        * Default constructor
        */
        Date() = delete;

        /*
        * Return the current date in a string format
        */
        static std::string GetDateAsString();
    };

}
