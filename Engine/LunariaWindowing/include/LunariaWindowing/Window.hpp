/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#pragma once

#include <LunariaCore/Global/Base.hpp>

#include "LunariaWindowing/Context/Device.hpp"
#include "LunariaWindowing/Settings/WindowSettings.hpp"
#include "LunariaWindowing/Cursor/LCursorMode.hpp"
#include "LunariaWindowing/Cursor/LCursorShape.hpp"

namespace Lunaria::Windowing {

    /**
    * A simple OS-based window.
    * It needs a Device (SDL) to work
    */
    class LUNARIA_API Window
    {
    public:
        /* Inputs relatives */
        static Eventing::Event<int> KeyPressedEvent;
        static Eventing::Event<int> KeyReleasedEvent;
        static Eventing::Event<int> MouseButtonPressedEvent;
        static Eventing::Event<int> MouseButtonReleasedEvent;

        /* Window events */
        static Eventing::Event<uint16_t, uint16_t> ResizeEvent;
        static Eventing::Event<uint16_t, uint16_t> FramebufferResizeEvent;
        static Eventing::Event<int16_t, int16_t> MoveEvent;
        static Eventing::Event<int16_t, int16_t> CursorMoveEvent;
        static Eventing::Event<> MinimizeEvent;
        static Eventing::Event<> MaximizeEvent;
        static Eventing::Event<> GainFocusEvent;
        static Eventing::Event<> LostFocusEvent;
        static Eventing::Event<> CloseEvent;

        /**
        * Create the window
        * @param p_device
        * @param p_windowSettings
        */
        Window(const Context::Device& p_device, const Settings::WindowSettings& p_windowSettings);

        /**
        * Destructor of the window, responsible of the GLFW window memory free
        */
        ~Window();

        /**
        * Set Icon
        * @param p_filePath
        */
        void SetIcon(const std::string& p_filePath);

        /**
        * Set Icon from memory
        * @param p_data
        * @param p_width
        * @param p_height
        */
        void SetIconFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height);

        /**
        * Find an instance of window with a given SDL_Window
        * @param p_sdlWindow
        */
        static Window* FindInstance(SDL_Window* p_sdlWindow);

        /**
        * Resize the window
        * @param p_width
        * @param p_height
        */
        void SetSize(uint16_t p_width, uint16_t p_height);

        /**
        * Defines a minimum size for the window
        * @param p_minimumWidth
        * @param p_minimumHeight
        * @note -1 (WindowSettings::DontCare) value means no limitation
        */
        void SetMinimumSize(int16_t p_minimumWidth, int16_t p_minimumHeight);

        /**
        * Defines a maximum size for the window
        * @param p_maximumWidth
        * @param p_maximumHeight
        * @note -1 (WindowSettings::DontCare) value means no limitation
        */
        void SetMaximumSize(int16_t p_maximumWidth, int16_t p_maximumHeight);

        /**
        * Define a position for the window
        * @param p_x
        * @param p_y
        */
        void SetPosition(int16_t p_x, int16_t p_y);

        /**
        * Minimize the window
        */
        void Minimize() const;

        /**
        * Maximize the window
        */
        void Maximize() const;

        /**
        * Restore the window
        */
        void Restore() const;

        /**
        * Hides the specified window if it was previously visible
        */
        void Hide() const;

        /**
        * Show the specified window if it was previously hidden
        */
        void Show() const;

        /**
        * Focus the window
        */
        void Focus() const;

        /**
        * Set the should close flag of the window to true
        * @param p_value
        */
        void SetShouldClose(bool p_value) const;

        /**
        * Return true if the window should close
        */
        bool ShouldClose() const;

        /**
        * Set the window in fullscreen or windowed mode
        * @param p_value (True for fullscreen mode, false for windowed)
        */
        void SetFullscreen(bool p_value);

        /**
        * Switch the window to fullscreen or windowed mode depending
        * on the current state
        */
        void ToggleFullscreen();

        /**
        * Return true if the window is fullscreen
        */
        bool IsFullscreen() const;

        /**
        * Return true if the window is hidden
        */
        bool IsHidden() const;

        /**
        * Return true if the window is visible
        */
        bool IsVisible() const;

        /**
        * Return true if the windows is maximized
        */
        bool IsMaximized() const;

        /**
        * Return true if the windows is minimized
        */
        bool IsMinimized() const;

        /**
        * Return true if the windows is focused
        */
        bool IsFocused() const;

        /**
        * Return true if the windows is resizable
        */
        bool IsResizable() const;

        /**
        * Return true if the windows is decorated
        */
        bool IsDecorated() const;

        /**
        * Define the window as the current context
        */
        void MakeCurrentContext() const;

        /**
        * Handle the buffer swapping with the current window
        */
        void SwapBuffers() const;

        /**
        * Define a mode for the mouse cursor
        * @param p_cursorMode
        */
        void SetCursorMode(Cursor::LCursorMode p_cursorMode);

        /**
        * Define a shape to apply to the current cursor
        * @param p_cursorShape
        */
        void SetCursorShape(Cursor::LCursorShape p_cursorShape);

        /**
        * Move the cursor to the given position
        */
        void SetCursorPosition(int16_t p_x, int16_t p_y);

        /**
        * Define a title for the window
        * @param p_title
        */
        void SetTitle(const std::string& p_title);

        /**
        * Defines a refresh rate (Use WindowSettings::DontCare to use the highest available refresh rate)
        * @param p_refreshRate
        * @note You need to switch to fullscreen mode to apply this effect (Or leave fullscreen and re-apply)
        */
        void SetRefreshRate(int32_t p_refreshRate);

        /**
        * Return the title of the window
        */
        std::string GetTitle() const;

        /**
        * Return the current size of the window
        */
        std::pair<uint16_t, uint16_t> GetSize() const;

        /**
        * Return the current minimum size of the window
        * @note -1 (WindowSettings::DontCare) values means no limitation
        */
        std::pair<int16_t, int16_t> GetMinimumSize() const;

        /**
        * Return the current maximum size of the window
        * @note -1 (WindowSettings::DontCare) values means no limitation
        */
        std::pair<int16_t, int16_t> GetMaximumSize() const;

        /**
        * Return the current position of the window
        */
        std::pair<int16_t, int16_t> GetPosition() const;

        /**
        * Return the framebuffer size (Viewport size)
        */
        std::pair<uint16_t, uint16_t> GetFramebufferSize() const;

        /**
        * Return the current cursor mode
        */
        Cursor::LCursorMode GetCursorMode() const;

        /**
        * Return the current cursor shape
        */
        Cursor::LCursorShape GetCursorShape() const;

        /**
        * Return the current refresh rate (Only applied to the fullscreen mode).
        * If the value is -1 (WindowSettings::DontCare) the highest refresh rate will be used
        */
        int32_t GetRefreshRate() const;

        /**
        * Return SDL window
        */
        SDL_Window* GetNativeWindow() const;

    private:
        void CreateNativeWindow(const Settings::WindowSettings& p_windowSettings);

        /* Callbacks binding */
        void BindKeyCallback() const;
        void BindMouseCallback() const;
        void BindResizeCallback() const;
        void BindFramebufferResizeCallback() const;
        void BindCursorMoveCallback() const;
        void BindMoveCallback() const;
        void BindIconifyCallback() const;
        void BindFocusCallback() const;
        void BindCloseCallback() const;

        /* Event listeners */
        void OnResize(uint16_t p_width, uint16_t p_height);
        void OnMove(int16_t p_x, int16_t p_y);

        /* Internal helpers */
        void UpdateSizeLimit() const;

    private:
        /* This map is used by callbacks to find a "Window" instance out of a "SDL_Window" instance*/
        static std::unordered_map<SDL_Window*, Window*> s_windows_map;

        const Context::Device& m_device;
        SDL_Window* m_sdlWindow;

        /* Window settings */
        std::string m_title;
        std::pair<uint16_t, uint16_t> m_size;
        std::pair<int16_t, int16_t> m_minimumSize;
        std::pair<int16_t, int16_t> m_maximumSize;
        std::pair<int16_t, int16_t> m_position;
        bool m_fullscreen = false;
        int32_t m_refreshRate = -1;
        Cursor::LCursorMode m_cursorMode;
        Cursor::LCursorShape m_cursorShape;
    };

}
