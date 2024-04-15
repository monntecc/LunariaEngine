/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include <unordered_map>

#include <SDL/SDL.h>

#include <LunariaCore/Global/Base.hpp>
#include <LunariaCore/Eventing/Event.hpp>

#include "LunariaWindowing/Context/LDeviceError.hpp"
#include "LunariaWindowing/Cursor/LCursorMode.hpp"
#include "LunariaWindowing/Cursor/LCursorShape.hpp"
#include "LunariaWindowing/Settings/DeviceSettings.hpp"
#include "LunariaWindowing/Settings/DeviceSettings.hpp"


namespace Lunaria::Windowing::Context {

    /**
    * The Device represents the windowing context. It is necessary to create a device
    * to create a window
    */
    class LUNARIA_API Device
    {
    public:
        /**
        * Bind a listener to this event to receive device errors
        */
        static Eventing::Event<LDeviceError, std::string> ErrorEvent;

        /**
        * The constructor of the device will take care about GLFW initialization
        */
        Device(const Settings::DeviceSettings& p_deviceSettings);

        /**
        * The destructor of the device will take care about GLFW destruction
        */
        ~Device();

        /**
        * Return the size, in pixels, of the primary monity
        */
        std::pair<int16_t, int16_t> GetMonitorSize() const;

        /**
        * Return an instance of GLFWcursor corresponding to the given shape
        * @param p_cursorShape
        */
        SDL_Cursor* GetCursorInstance(Cursor::LCursorShape p_cursorShape) const;

        /**
        * Return true if the vsync is currently enabled
        */
        bool HasVsync() const;

        /**
        * Enable or disable the vsync
        * @note You must call this method after creating and defining a window as the current context
        * @param p_value (True to enable vsync)
        */
        void SetVsync(bool p_value);

        /**
        * Enable the inputs and events managments with created windows
        * @note Should be called every frames
        */
        void PollEvents();

        /**
        * Returns the elapsed time since the device startup
        */
        float GetElapsedTime() const;

    private:
        void BindErrorCallback();
        void CreateCursors();
        void DestroyCursors();

    private:
        bool m_vsync;
        bool m_isAlive;
        std::unordered_map<Cursor::LCursorShape, SDL_Cursor*> m_cursors;
    };

}
