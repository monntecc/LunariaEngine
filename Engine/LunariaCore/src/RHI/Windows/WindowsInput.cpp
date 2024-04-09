#include "lepch.hpp"

#include "LunariaCore/Core/Input.hpp"
#include "LunariaCore/Core/Application.hpp"

#include <SDL/SDL.h>

namespace Lunaria {

    bool Input::IsKeyPressed(const KeyCode keycode)
    {
        const Uint8* state = SDL_GetKeyboardState(nullptr);
        return state[SDL_GetScancodeFromKey(keycode)] != 0;
    }

    bool Input::IsMouseButtonPressed(const MouseCode button)
    {
        int x, y;
        const Uint32 state = SDL_GetMouseState(&x, &y);

        return (button == Mouse::ButtonLeft && (state & SDL_BUTTON(SDL_BUTTON_LEFT))) ||
            (button == Mouse::ButtonRight && (state & SDL_BUTTON(SDL_BUTTON_RIGHT))) ||
            (button == Mouse::ButtonMiddle && (state & SDL_BUTTON(SDL_BUTTON_MIDDLE))) ||
            (button == Mouse::ButtonX1 && (state & SDL_BUTTON(SDL_BUTTON_X1))) ||
            (button == Mouse::ButtonX2 && (state & SDL_BUTTON(SDL_BUTTON_X2)));
    }

    glm::vec2 Input::GetMousePosition()
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        return { static_cast<float>(x), static_cast<float>(y) };
    }

    float Input::GetMouseX()
    {
        return GetMousePosition().x;
    }

    float Input::GetMouseY()
    {
        return GetMousePosition().y;
    }

}