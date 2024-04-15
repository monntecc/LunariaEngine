/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#include "LunariaCore/Tools/Clock.hpp"

namespace Lunaria::Tools {

    float Clock::GetFramerate()
    {
        return 1.0f / (m_delta_time);
    }

    float Clock::GetDeltaTime()
    {
        return m_delta_time * m_time_scale;
    }

    float Clock::GetDeltaTimeUnscaled()
    {
        return m_delta_time;
    }

    float Clock::GetTimeSinceStart()
    {
        return m_time_since_start;
    }

    float Clock::GetTimeScale()
    {
        return m_time_scale;
    }

    void Clock::Scale(float p_coeff)
    {
        m_time_scale *= p_coeff;
    }

    void Clock::SetTimeScale(float p_timeScale)
    {
        m_time_scale = p_timeScale;
    }

    void Clock::Initialize()
    {
        m_delta_time = 0.0f;

        m_start_time = std::chrono::steady_clock::now();
        m_current_time = m_start_time;
        m_last_time = m_start_time;

        m_initialized = true;
    }

    void Clock::Update()
    {
        m_last_time = m_current_time;
        m_current_time = std::chrono::steady_clock::now();
        m_elapsed = m_current_time - m_last_time;

        if (m_initialized)
        {
            m_delta_time = m_elapsed.count() > 0.1 ? 0.1f : static_cast<float>(m_elapsed.count());
            m_time_since_start += m_delta_time * m_time_scale;
        }
        else
            Initialize();
    }

}
