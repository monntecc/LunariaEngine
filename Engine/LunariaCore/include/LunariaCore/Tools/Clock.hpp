/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include "LunariaCore/Global/Base.hpp"

namespace Lunaria::Tools {

    class LUNARIA_API Clock
    {
    public:
        /**
        * Update the clock
        */
        void Update();

        /**
        * Return the actual framerate (Depend on the delta time)
        */
        float GetFramerate();

        /**
        * Return the actual delta time (Scale applied)
        */
        float GetDeltaTime();

        /**
        * Return the actual delta time (Scale not applied)
        */
        float GetDeltaTimeUnscaled();

        /**
        * Return the time elapsed since clock creation
        */
        float GetTimeSinceStart();

        /**
        * Return the current timescale
        */
        float GetTimeScale();

        /**
        * Multiply the timescale by the given coefficient
        * @param p_coeff
        */
        void Scale(float p_coeff);

        /**
        * Define a timescale
        * @param p_timescale
        */
        void SetTimeScale(float p_timeScale);

    private:
        void Initialize();

        std::chrono::steady_clock::time_point m_start_time;
        std::chrono::steady_clock::time_point m_last_time;
        std::chrono::steady_clock::time_point m_current_time;
        std::chrono::duration<double> m_elapsed;

        bool m_initialized = false;
        float m_time_scale = 1.0f;
        float m_delta_time = 0.0f;
        float m_time_since_start = 0.0f;
    };

}
