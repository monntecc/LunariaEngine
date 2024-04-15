/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#include <stdexcept>
#include <functional>

#include "LunariaWindowing/Window.hpp"

namespace Lunaria::Windowing {

    std::unordered_map<SDL_Window*, Window*> Window::s_windows_map;

    Window::Window(const Context::Device& p_device, const Settings::WindowSettings& p_windowSettings) :
        m_device(p_device),
        m_title(p_windowSettings.title),
        m_size{ p_windowSettings.width, p_windowSettings.height },
        m_minimumSize{ p_windowSettings.minimumWidth, p_windowSettings.minimumHeight },
        m_maximumSize{ p_windowSettings.maximumWidth, p_windowSettings.maximumHeight },
        m_fullscreen(p_windowSettings.fullscreen),
        m_refreshRate(p_windowSettings.refreshRate),
        m_cursorMode(p_windowSettings.cursorMode),
        m_cursorShape(p_windowSettings.cursorShape)
    {
        /* Window creation */
        CreateNativeWindow(p_windowSettings);

        /* Window settings */
        SetCursorMode(p_windowSettings.cursorMode);
        SetCursorShape(p_windowSettings.cursorShape);

        /* Callback binding */
        BindKeyCallback();
        BindMouseCallback();
        BindIconifyCallback();
        BindCloseCallback();
        BindResizeCallback();
        BindCursorMoveCallback();
        BindFramebufferResizeCallback();
        BindMoveCallback();
        BindFocusCallback();

        /* Event listening */
        ResizeEvent.AddListener(std::bind(&Window::OnResize, this, std::placeholders::_1, std::placeholders::_2));
        MoveEvent.AddListener(std::bind(&Window::OnMove, this, std::placeholders::_1, std::placeholders::_2));
    }

    Window::~Window()
    {
        SDL_DestroyWindow(m_sdlWindow);
    }

    void Window::SetIcon(const std::string& p_filePath)
    {
        SDL_Surface* icon = SDL_LoadBMP(p_filePath.c_str());
        if (!icon)
        {
            LU_CORE_ERROR("Failed to load icon: {0}", SDL_GetError());
            return;
        }

        SDL_SetWindowIcon(m_sdlWindow, icon);
        SDL_FreeSurface(icon);
    }

    void Window::SetIconFromMemory(uint8_t* p_data, uint32_t p_width, uint32_t p_height)
    {
        SDL_Surface *icon = SDL_CreateRGBSurfaceFrom(p_data, p_width, p_height, 32, 4 * p_width, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
        if (!icon)
        {
            LU_CORE_ERROR("Failed to load icon: {0}", SDL_GetError());
            return;
        }

        SDL_SetWindowIcon(m_sdlWindow, icon);
        SDL_FreeSurface(icon);
    }

    Window* Window::FindInstance(SDL_Window* p_sdl_Window)
    {
        return s_windows_map.find(p_sdl_Window) != s_windows_map.end() ? s_windows_map[p_sdl_Window] : nullptr;
    }

    void Window::SetSize(uint16_t p_width, uint16_t p_height)
    {
        SDL_SetWindowSize(m_sdlWindow, static_cast<int>(p_width), static_cast<int>(p_height));
    }

    void Window::SetMinimumSize(int16_t p_minimumWidth, int16_t p_minimumHeight)
    {
        m_minimumSize.first = p_minimumWidth;
        m_minimumSize.second = p_minimumHeight;

        UpdateSizeLimit();
    }

    void Window::SetMaximumSize(int16_t p_maximumWidth, int16_t p_maximumHeight)
    {
        m_maximumSize.first = p_maximumWidth;
        m_maximumSize.second = p_maximumHeight;

        UpdateSizeLimit();
    }

    void Window::SetPosition(int16_t p_x, int16_t p_y)
    {
        SDL_SetWindowPosition(m_sdlWindow, static_cast<int>(p_x), static_cast<int>(p_y));
    }

    void Window::Minimize() const
    {
        SDL_MinimizeWindow(m_sdlWindow);
    }

    void Window::Maximize() const
    {
        SDL_MaximizeWindow(m_sdlWindow);
    }

    void Window::Restore() const
    {
        SDL_RestoreWindow(m_sdlWindow);
    }

    void Window::Hide() const
    {
        SDL_HideWindow(m_sdlWindow);
    }

    void Window::Show() const
    {
        SDL_ShowWindow(m_sdlWindow);
    }

    void Window::Focus() const
    {
        SDL_RaiseWindow(m_sdlWindow);
    }

    void Window::SetShouldClose(bool p_value) const
    {
        // TODO: Implement
    }

    bool Window::ShouldClose() const
    {
        return SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_SHOWN;
    }

    void Window::SetFullscreen(bool p_value)
    {

        if (p_value)
            m_fullscreen = true;

        SDL_SetWindowFullscreen(m_sdlWindow, p_value ? SDL_WINDOW_FULLSCREEN : 0);

        if (!p_value)
            m_fullscreen = false;
    }

    void Window::ToggleFullscreen()
    {
        SetFullscreen(!m_fullscreen);
    }

    bool Window::IsFullscreen() const
    {
        return m_fullscreen;
    }

    bool Window::IsHidden() const
    {
        return SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_HIDDEN;
    }

    bool Window::IsVisible() const
    {
        return SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_SHOWN;
    }

    bool Window::IsMaximized() const
    {
        return SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_MAXIMIZED;
    }

    bool Window::IsMinimized() const
    {
        return SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_MINIMIZED;
    }

    bool Window::IsFocused() const
    {
        return SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_INPUT_FOCUS;
    }

    bool Window::IsResizable() const
    {
        return SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_RESIZABLE;
    }

    bool Window::IsDecorated() const
    {
        return SDL_GetWindowFlags(m_sdlWindow) & SDL_WINDOW_BORDERLESS;
    }

    void Window::MakeCurrentContext() const
    {
        SDL_GL_MakeCurrent(m_sdlWindow, SDL_GL_GetCurrentContext());
    }

    void Window::SwapBuffers() const
    {
        SDL_GL_SwapWindow(m_sdlWindow);
    }

    void Window::SetCursorMode(Cursor::LCursorMode p_cursorMode)
    {
        m_cursorMode = p_cursorMode;

        SDL_Cursor* cursor = nullptr;
        switch (p_cursorMode)
        {
        case Cursor::LCursorMode::NORMAL:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
            break;
        case Cursor::LCursorMode::HIDDEN:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
            break;
        case Cursor::LCursorMode::DISABLED:
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
            break;
        }

        SDL_SetCursor(cursor);
        SDL_ShowCursor(SDL_ENABLE);
    }

    void Window::SetCursorShape(Cursor::LCursorShape p_cursorShape)
    {
        m_cursorShape = p_cursorShape;

        SDL_Cursor* cursor = nullptr;
        switch (p_cursorShape)
        {
            case Cursor::LCursorShape::ARROW:
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
                break;
            case Cursor::LCursorShape::IBEAM:
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
                break;
            case Cursor::LCursorShape::CROSSHAIR:
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
                break;
            case Cursor::LCursorShape::HAND:
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
                break;
            case Cursor::LCursorShape::HRESIZE:
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
                break;
            case Cursor::LCursorShape::VRESIZE:
                cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
                break;
        }

        SDL_SetCursor(cursor);
        SDL_ShowCursor(SDL_ENABLE);
    }

    void Window::SetCursorPosition(int16_t p_x, int16_t p_y)
    {
        SDL_WarpMouseInWindow(m_sdlWindow, static_cast<int>(p_x), static_cast<int>(p_y));
    }

    void Window::SetTitle(const std::string& p_title)
    {
        m_title = p_title;
        SDL_SetWindowTitle(m_sdlWindow, p_title.c_str());
    }

    void Window::SetRefreshRate(int32_t p_refreshRate)
    {
        m_refreshRate = p_refreshRate;
    }

    std::string Window::GetTitle() const
    {
        return m_title;
    }

    std::pair<uint16_t, uint16_t> Window::GetSize() const
    {
        int width, height;
        SDL_GetWindowSize(m_sdlWindow, &width, &height);
        return std::make_pair(static_cast<uint16_t>(width), static_cast<uint16_t>(height));
    }

    std::pair<int16_t, int16_t> Window::GetMinimumSize() const
    {
        return m_minimumSize;
    }

    std::pair<int16_t, int16_t> Window::GetMaximumSize() const
    {
        return m_maximumSize;
    }

    std::pair<int16_t, int16_t> Window::GetPosition() const
    {
        int x, y;
        SDL_GetWindowPosition(m_sdlWindow, &x, &y);
        return std::make_pair(static_cast<int16_t>(x), static_cast<int16_t>(y));
    }

    std::pair<uint16_t, uint16_t> Window::GetFramebufferSize() const
    {
        int width, height;
        SDL_GL_GetDrawableSize(m_sdlWindow, &width, &height);
        return std::make_pair(static_cast<uint16_t>(width), static_cast<uint16_t>(height));
    }

    Cursor::LCursorMode Window::GetCursorMode() const
    {
        return m_cursorMode;
    }

    Cursor::LCursorShape Window::GetCursorShape() const
    {
        return m_cursorShape;
    }

    int32_t Window::GetRefreshRate() const
    {
        return m_refreshRate;
    }

    SDL_Window* Window::GetNativeWindow() const
    {
        return m_sdlWindow;
    }

    void Window::CreateNativeWindow(const Settings::WindowSettings& p_windowSettings)
    {
        SDL_DisplayMode displayMode;

        if (m_fullscreen)
        {
            SDL_GetCurrentDisplayMode(0, &displayMode);
            m_size.first = displayMode.w;
            m_size.second = displayMode.h;
        }

        m_sdlWindow = SDL_CreateWindow
        (
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            m_size.first,
            m_size.second,
            p_windowSettings.resizable ? SDL_WINDOW_RESIZABLE : 0 |
            p_windowSettings.decorated ? SDL_WINDOW_BORDERLESS : 0 |
            p_windowSettings.focused ? SDL_WINDOW_INPUT_FOCUS : 0 |
            p_windowSettings.maximized ? SDL_WINDOW_MAXIMIZED : 0 |
            p_windowSettings.floating ? SDL_WINDOW_ALWAYS_ON_TOP : 0 |
            p_windowSettings.visible ? SDL_WINDOW_SHOWN : 0 |
            p_windowSettings.autoIconify ? SDL_WINDOW_ALLOW_HIGHDPI : 0 |
            p_windowSettings.fullscreen ? SDL_WINDOW_FULLSCREEN : 0 |
            SDL_WINDOW_OPENGL
        );

        if (!m_sdlWindow)
        {
            LU_CORE_ASSERT(!m_sdlWindow, "Failed to create SDL window: {0}", SDL_GetError());
        }
        else
        {
            UpdateSizeLimit();

            auto [x, y] = GetPosition();
            m_position.first = x;
            m_position.second = y;

            s_windows_map[m_sdlWindow] = this;
        }
    }

    void Window::BindKeyCallback() const
    {
        auto keyCallback = [](SDL_Window* p_window, int p_key, int p_scancode, int p_action, int p_mods)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    if (p_action == SDL_KEYDOWN)
                        windowInstance->KeyPressedEvent.Invoke(p_key);

                    if (p_action == SDL_KEYUP)
                        windowInstance->KeyReleasedEvent.Invoke(p_key);
                }
            };
    }

    void Window::BindMouseCallback() const
    {
        auto mouseCallback = [](SDL_Window* p_window, int p_button, int p_action, int p_mods)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    if (p_action == SDL_MOUSEBUTTONDOWN)
                        windowInstance->MouseButtonPressedEvent.Invoke(p_button);

                    if (p_action == SDL_MOUSEBUTTONUP)
                        windowInstance->MouseButtonReleasedEvent.Invoke(p_button);
                }
            };
    }


    void Window::BindResizeCallback() const
    {
        auto resizeCallback = [](SDL_Window* p_window, int p_width, int p_height)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->ResizeEvent.Invoke(static_cast<uint16_t>(p_width), static_cast<uint16_t>(p_height));
                }
            };
    }

    void Window::BindFramebufferResizeCallback() const
    {
        auto framebufferResizeCallback = [](SDL_Window* p_window, int p_width, int p_height)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->FramebufferResizeEvent.Invoke(static_cast<uint16_t>(p_width), static_cast<uint16_t>(p_height));
                }
            };
    }

    void Window::BindCursorMoveCallback() const
    {
        auto cursorMoveCallback = [](SDL_Window* p_window, double p_x, double p_y)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->CursorMoveEvent.Invoke(static_cast<int16_t>(p_x), static_cast<int16_t>(p_y));
                }
            };
    }

    void Window::BindMoveCallback() const
    {
        auto moveCallback = [](SDL_Window* p_window, int p_x, int p_y)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->MoveEvent.Invoke(static_cast<int16_t>(p_x), static_cast<int16_t>(p_y));
                }
            };
    }

    void Window::BindIconifyCallback() const
    {
        auto iconifyCallback = [](SDL_Window* p_window, int p_iconified)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    if (p_iconified == SDL_TRUE)
                        windowInstance->MinimizeEvent.Invoke();

                    if (p_iconified == SDL_FALSE)
                        windowInstance->MaximizeEvent.Invoke();
                }
            };
    }

    void Window::BindFocusCallback() const
    {
        auto focusCallback = [](SDL_Window* p_window, int p_focused)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    if (p_focused == SDL_TRUE)
                        windowInstance->GainFocusEvent.Invoke();

                    if (p_focused == SDL_FALSE)
                        windowInstance->LostFocusEvent.Invoke();
                }
            };
    }

    void Window::BindCloseCallback() const
    {
        auto closeCallback = [](SDL_Window* p_window)
            {
                Window* windowInstance = FindInstance(p_window);

                if (windowInstance)
                {
                    windowInstance->CloseEvent.Invoke();
                }
            };
    }

    void Window::OnResize(uint16_t p_width, uint16_t p_height)
    {
        m_size.first = p_width;
        m_size.second = p_height;
    }

    void Window::OnMove(int16_t p_x, int16_t p_y)
    {
        if (!m_fullscreen)
        {
            m_position.first = p_x;
            m_position.second = p_y;
        }
    }

    void Window::UpdateSizeLimit() const
    {

        SDL_SetWindowMaximumSize(m_sdlWindow, static_cast<int>(m_maximumSize.first), static_cast<int>(m_maximumSize.second));
        SDL_SetWindowMinimumSize(m_sdlWindow, static_cast<int>(m_minimumSize.first), static_cast<int>(m_minimumSize.second));
    }

}
