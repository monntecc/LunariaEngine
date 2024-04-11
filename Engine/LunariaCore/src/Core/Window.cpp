#include "lepch.hpp"

#include "LunariaCore/Core/Window.hpp"

#ifdef LU_PLATFORM_WINDOWS
    #include "LunariaCore/RHI/Windows/WindowsWindow.hpp"
#endif

#ifdef LU_PLATFORM_LINUX
    #include "LunariaCore/RHI/Linux/LinuxWindow.hpp"
#endif

#include <SDL/SDL.h>

namespace Lunaria {

    struct SplashScreen
    {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;
        SDL_Surface* surface;

        int width = 1200;
        int height = 600;
    };

    SplashScreen s_SplashScreen = {};

    Window::Window()
    {
    }

    Scope<Window> Window::Create(const WindowProps& props)
    {
    #ifdef LU_PLATFORM_WINDOWS
        return CreateScope<WindowsWindow>(props);
    #elif defined(LU_PLATFORM_LINUX)
        return CreateScope<LinuxWindow>(props);
    #else
        LU_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
    #endif
    }

    void Window::CreateAndShowSplashScreen()
    {
        // Initialize SDL for the splash screen
        s_SplashScreen.surface = SDL_LoadBMP("Resources/Images/SplashScreen.bmp");

        // Create a window for the splash screen
        s_SplashScreen.window = SDL_CreateWindow(
            "lunaria_splash_screen",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            s_SplashScreen.width,
            s_SplashScreen.height,
            SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
        );

        // Create a renderer for the splash screen
        s_SplashScreen.renderer = SDL_CreateRenderer(s_SplashScreen.window, -1, SDL_RENDERER_ACCELERATED);

        // Create a texture for the splash screen and free the surface
        s_SplashScreen.texture = SDL_CreateTextureFromSurface(s_SplashScreen.renderer, s_SplashScreen.surface);
        SDL_FreeSurface(s_SplashScreen.surface);

        // Draw the splash screen
        SDL_RenderCopy(s_SplashScreen.renderer, s_SplashScreen.texture, nullptr, nullptr);
        SDL_RenderPresent(s_SplashScreen.renderer);
    }

    void Window::HideSplashScreen()
    {
        // Hide and destroy the splash screen
        SDL_DestroyTexture(s_SplashScreen.texture);
        SDL_DestroyRenderer(s_SplashScreen.renderer);
        SDL_DestroyWindow(s_SplashScreen.window);
    }
}
