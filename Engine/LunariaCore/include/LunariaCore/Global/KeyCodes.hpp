#pragma once

#include <SDL/SDL_keycode.h>

namespace Lunaria {

    using KeyCode = SDL_Keycode;

    namespace Key
    {
        enum : KeyCode
        {
            Space = SDLK_SPACE,
            Apostrophe = SDLK_QUOTE, /* ' */
            Comma = SDLK_COMMA, /* , */
            Minus = SDLK_MINUS, /* - */
            Period = SDLK_PERIOD, /* . */
            Slash = SDLK_SLASH, /* / */

            D0 = SDLK_0, /* 0 */
            D1 = SDLK_1, /* 1 */
            D2 = SDLK_2, /* 2 */
            D3 = SDLK_3, /* 3 */
            D4 = SDLK_4, /* 4 */
            D5 = SDLK_5, /* 5 */
            D6 = SDLK_6, /* 6 */
            D7 = SDLK_7, /* 7 */
            D8 = SDLK_8, /* 8 */
            D9 = SDLK_9, /* 9 */

            Semicolon = SDLK_SEMICOLON, /* ; */
            Equal = SDLK_EQUALS, /* = */

            A = SDLK_a,
            B = SDLK_b,
            C = SDLK_c,
            D = SDLK_d,
            E = SDLK_e,
            F = SDLK_f,
            G = SDLK_g,
            H = SDLK_h,
            I = SDLK_i,
            J = SDLK_j,
            K = SDLK_k,
            L = SDLK_l,
            M = SDLK_m,
            N = SDLK_n,
            O = SDLK_o,
            P = SDLK_p,
            Q = SDLK_q,
            R = SDLK_r,
            S = SDLK_s,
            T = SDLK_t,
            U = SDLK_u,
            V = SDLK_v,
            W = SDLK_w,
            X = SDLK_x,
            Y = SDLK_y,
            Z = SDLK_z,

            LeftBracket = SDLK_LEFTBRACKET,  /* [ */
            Backslash = SDLK_BACKSLASH,  /* \ */
            RightBracket = SDLK_RIGHTBRACKET,  /* ] */
            GraveAccent = SDLK_BACKQUOTE,  /* ` */

            /* Function keys */
            Escape = SDLK_ESCAPE,
            Enter = SDLK_RETURN,
            Tab = SDLK_TAB,
            Backspace = SDLK_BACKSPACE,
            Insert = SDLK_INSERT,
            Delete = SDLK_DELETE,
            Right = SDLK_RIGHT,
            Left = SDLK_LEFT,
            Down = SDLK_DOWN,
            Up = SDLK_UP,
            PageUp = SDLK_PAGEUP,
            PageDown = SDLK_PAGEDOWN,
            Home = SDLK_HOME,
            End = SDLK_END,
            CapsLock = SDLK_CAPSLOCK,
            ScrollLock = SDLK_SCROLLLOCK,
            NumLock = SDLK_NUMLOCKCLEAR,
            PrintScreen = SDLK_PRINTSCREEN,
            Pause = SDLK_PAUSE,
            F1 = SDLK_F1,
            F2 = SDLK_F2,
            F3 = SDLK_F3,
            F4 = SDLK_F4,
            F5 = SDLK_F5,
            F6 = SDLK_F6,
            F7 = SDLK_F7,
            F8 = SDLK_F8,
            F9 = SDLK_F9,
            F10 = SDLK_F10,
            F11 = SDLK_F11,
            F12 = SDLK_F12,
            F13 = SDLK_F13,
            F14 = SDLK_F14,
            F15 = SDLK_F15,
            F16 = SDLK_F16,
            F17 = SDLK_F17,
            F18 = SDLK_F18,
            F19 = SDLK_F19,
            F20 = SDLK_F20,
            F21 = SDLK_F21,
            F22 = SDLK_F22,
            F23 = SDLK_F23,
            F24 = SDLK_F24,

            /* Keypad */
            KP0 = SDLK_KP_0,
            KP1 = SDLK_KP_1,
            KP2 = SDLK_KP_2,
            KP3 = SDLK_KP_3,
            KP4 = SDLK_KP_4,
            KP5 = SDLK_KP_5,
            KP6 = SDLK_KP_6,
            KP7 = SDLK_KP_7,
            KP8 = SDLK_KP_8,
            KP9 = SDLK_KP_9,
            KPDecimal = SDLK_KP_DECIMAL,
            KPDivide = SDLK_KP_DIVIDE,
            KPMultiply = SDLK_KP_MULTIPLY,
            KPSubtract = SDLK_KP_MINUS,
            KPAdd = SDLK_KP_PLUS,
            KPEnter = SDLK_KP_ENTER,
            KPEqual = SDLK_KP_EQUALS,

            LeftShift = SDLK_LSHIFT,
            LeftControl = SDLK_LCTRL,
            LeftAlt = SDLK_LALT,
            LeftSuper = SDLK_LGUI,
            RightShift = SDLK_RSHIFT,
            RightControl = SDLK_RCTRL,
            RightAlt = SDLK_RALT,
            RightSuper = SDLK_RGUI,
            Menu = SDLK_MENU
        };
    }

}