/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#include "LunariaWindowing/Window.hpp"

#include "LunariaWindowing/Context/Device.hpp"

namespace Lunaria::Windowing::Context {

    Eventing::Event<LDeviceError, std::string> Device::ErrorEvent;

    Device::Device(const Settings::DeviceSettings& p_deviceSettings)
    {
        BindErrorCallback();

        int initializationCode = SDL_Init(SDL_WINDOW_OPENGL);

        if (initializationCode == SDL_FALSE)
        {
            LU_CORE_ASSERT(false, "Failed to Init SDL");
            SDL_Quit();
        }
        else
        {
            CreateCursors();

            if (p_deviceSettings.debugProfile)
                SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, p_deviceSettings.contextMajorVersion);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, p_deviceSettings.contextMinorVersion);

            m_isAlive = true;
        }
    }

    Device::~Device()
    {
        if (m_isAlive)
        {
            DestroyCursors();
            SDL_Quit();
        }
    }

    std::pair<int16_t, int16_t> Device::GetMonitorSize() const
    {
        SDL_DisplayMode mode;
        SDL_GetCurrentDisplayMode(0, &mode);
        return std::pair<int16_t, int16_t>(static_cast<int16_t>(mode.w), static_cast<int16_t>(mode.h));
    }

    SDL_Cursor* Device::GetCursorInstance(Cursor::LCursorShape p_cursorShape) const
    {
        return m_cursors.at(p_cursorShape);
    }

    bool Device::HasVsync() const
    {
        return m_vsync;
    }

    void Device::SetVsync(bool p_value)
    {
        SDL_GL_SetSwapInterval(p_value ? 1 : 0);
        m_vsync = p_value;
    }

    void Device::PollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                switch (event.window.event)
                {
                case SDL_WINDOWEVENT_RESIZED:
                    Window::ResizeEvent.Invoke(event.window.data1, event.window.data2);
                    break;
                case SDL_WINDOWEVENT_CLOSE:
                    Window::CloseEvent.Invoke();
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                Window::MouseButtonPressedEvent.Invoke(event.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                Window::MouseButtonReleasedEvent.Invoke(event.button.button);
                break;
            case SDL_KEYDOWN:
                break;
                Window::KeyPressedEvent.Invoke(event.key.keysym.scancode);
                break;
            case SDL_KEYUP:
                Window::KeyReleasedEvent.Invoke(event.key.keysym.scancode);
                break;
            case SDL_QUIT:
                m_isAlive = false;
                break;
            }
        }
    }

    float Device::GetElapsedTime() const
    {
        return static_cast<float>(SDL_GetTicks()) / 1000.0f;
    }

    void Device::BindErrorCallback()
    {
        auto errorCallback = [](void* userdata, int category, SDL_LogPriority priority, const char* message)
        {
            ErrorEvent.Invoke(static_cast<LDeviceError>(reinterpret_cast<intptr_t>(userdata)), message);
        };

        SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR);
        SDL_LogSetPriority(SDL_LOG_CATEGORY_ASSERT, SDL_LOG_PRIORITY_ERROR);
        SDL_LogSetPriority(SDL_LOG_CATEGORY_SYSTEM, SDL_LOG_PRIORITY_ERROR);
        SDL_LogSetPriority(SDL_LOG_CATEGORY_AUDIO, SDL_LOG_PRIORITY_ERROR);
        SDL_LogSetPriority(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_ERROR);
        SDL_LogSetPriority(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_ERROR);
        SDL_LogSetPriority(SDL_LOG_CATEGORY_INPUT, SDL_LOG_PRIORITY_ERROR);
        SDL_LogSetPriority(SDL_LOG_CATEGORY_TEST, SDL_LOG_PRIORITY_ERROR);

        SDL_LogSetOutputFunction([](void* userdata, int category, SDL_LogPriority priority, const char* message)
            {
                SDL_LogMessage(category, priority, "%s", message);
            }, nullptr);

        SDL_LogSetOutputFunction(static_cast<SDL_LogOutputFunction>(errorCallback), reinterpret_cast<void*>(static_cast<intptr_t>(LDeviceError::NOT_INITIALIZED)));

        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Error callback bound.");
    }

    void Device::CreateCursors()
    {
        m_cursors[Cursor::LCursorShape::ARROW] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
        m_cursors[Cursor::LCursorShape::IBEAM] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
        m_cursors[Cursor::LCursorShape::CROSSHAIR] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
        m_cursors[Cursor::LCursorShape::HAND] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
        m_cursors[Cursor::LCursorShape::HRESIZE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
        m_cursors[Cursor::LCursorShape::VRESIZE] = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    }

    void Device::DestroyCursors()
    {
        for (auto& pair : m_cursors)
        {
            SDL_FreeCursor(pair.second);
        }
    }

}
