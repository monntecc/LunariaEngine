/*
 * @copyright Copyright(c) 2024 Vladyslav Potapenko. All rights reserved.
 * @license Licensed under the MIT License. See LICENSE in the project root for license information.
*/

#include "LunariaWindowing/Inputs/InputManager.hpp"

namespace Lunaria::Windowing::Inputs {

    InputManager::InputManager(Window& p_window) : m_window(p_window)
    {
        m_keyPressedListener = m_window.KeyPressedEvent.AddListener(std::bind(&InputManager::OnKeyPressed, this, std::placeholders::_1));
        m_keyReleasedListener = m_window.KeyReleasedEvent.AddListener(std::bind(&InputManager::OnKeyReleased, this, std::placeholders::_1));
        m_mouseButtonPressedListener = m_window.MouseButtonPressedEvent.AddListener(std::bind(&InputManager::OnMouseButtonPressed, this, std::placeholders::_1));
        m_mouseButtonReleasedListener = m_window.MouseButtonReleasedEvent.AddListener(std::bind(&InputManager::OnMouseButtonReleased, this, std::placeholders::_1));
    }

    InputManager::~InputManager()
    {
        m_window.KeyPressedEvent.RemoveListener(m_keyPressedListener);
        m_window.KeyReleasedEvent.RemoveListener(m_keyReleasedListener);
        m_window.MouseButtonPressedEvent.RemoveListener(m_mouseButtonPressedListener);
        m_window.MouseButtonReleasedEvent.RemoveListener(m_mouseButtonReleasedListener);
    }

    EKeyState InputManager::GetKeyState(EKey p_key) const
    {
        const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

        if (keyboardState[static_cast<SDL_Scancode>(p_key)])
            return EKeyState::KEY_DOWN;
        else
            return EKeyState::KEY_UP;
    }

    EMouseButtonState InputManager::GetMouseButtonState(EMouseButton p_button) const
    {
        Uint32 mouseState = SDL_GetMouseState(NULL, NULL);

        if (mouseState & SDL_BUTTON(static_cast<Uint8>(p_button)))
            return EMouseButtonState::MOUSE_DOWN;
        else
            return EMouseButtonState::MOUSE_UP;
    }

    bool InputManager::IsKeyPressed(EKey p_key) const
    {
        return m_keyEvents.find(p_key) != m_keyEvents.end() && m_keyEvents.at(p_key) == EKeyState::KEY_DOWN;
    }

    bool InputManager::IsKeyReleased(EKey p_key) const
    {
        return m_keyEvents.find(p_key) != m_keyEvents.end() && m_keyEvents.at(p_key) == EKeyState::KEY_UP;
    }

    bool InputManager::IsMouseButtonPressed(EMouseButton p_button) const
    {
        return m_mouseButtonEvents.find(p_button) != m_mouseButtonEvents.end() && m_mouseButtonEvents.at(p_button) == EMouseButtonState::MOUSE_DOWN;
    }

    bool InputManager::IsMouseButtonReleased(EMouseButton p_button) const
    {
        return m_mouseButtonEvents.find(p_button) != m_mouseButtonEvents.end() && m_mouseButtonEvents.at(p_button) == EMouseButtonState::MOUSE_UP;
    }

    std::pair<double, double> InputManager::GetMousePosition() const
    {
        std::pair<double, double> result;
        SDL_GetMouseState(reinterpret_cast<int*>(&result.first), reinterpret_cast<int*>(&result.second));
        return result;
    }

    void InputManager::ClearEvents()
    {
        m_keyEvents.clear();
        m_mouseButtonEvents.clear();
    }

    void InputManager::OnKeyPressed(int p_key)
    {
        m_keyEvents[static_cast<EKey>(p_key)] = EKeyState::KEY_DOWN;
    }

    void InputManager::OnKeyReleased(int p_key)
    {
        m_keyEvents[static_cast<EKey>(p_key)] = EKeyState::KEY_UP;
    }

    void InputManager::OnMouseButtonPressed(int p_button)
    {
        m_mouseButtonEvents[static_cast<EMouseButton>(p_button)] = EMouseButtonState::MOUSE_DOWN;
    }

    void InputManager::OnMouseButtonReleased(int p_button)
    {
        m_mouseButtonEvents[static_cast<EMouseButton>(p_button)] = EMouseButtonState::MOUSE_UP;
    }

}
