#include "lepch.hpp"

#include "LunariaCore/Core/Window.hpp"

#ifdef LU_PLATFORM_WINDOWS
    #include "LunariaCore/RHI/Windows/WindowsWindow.hpp"
#endif

#ifdef LU_PLATFORM_LINUX
    #include "LunariaCore/RHI/Linux/LinuxWindow.hpp"
#endif

namespace Lunaria {

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

}