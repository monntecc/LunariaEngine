#pragma once

#include <SDL/SDL_mouse.h>

namespace Lunaria {

    using MouseCode = uint8_t;

    namespace Mouse {

        enum : MouseCode
        {
            Button0 = SDL_BUTTON_LEFT,
            Button1 = SDL_BUTTON_RIGHT,
            Button2 = SDL_BUTTON_MIDDLE,
            Button3 = SDL_BUTTON_X1,
            Button4 = SDL_BUTTON_X2,
            Button5 = SDL_BUTTON_LMASK,
            Button6 = SDL_BUTTON_MMASK,
            Button7 = SDL_BUTTON_RMASK,

            ButtonLast = Button7,
            ButtonLeft = Button0,
            ButtonRight = Button1,
            ButtonMiddle = Button2,
            ButtonX1 = Button3,
            ButtonX2 = Button4
        };

    }

}
