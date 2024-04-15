#include "lepch.hpp"

#include "LunariaCore/Global/Application.hpp"
#include "LunariaCore/Events/ApplicationEvent.hpp"
#include "LunariaCore/Events/KeyEvent.hpp"
#include "LunariaCore/Events/MouseEvent.hpp"

#include "LunariaCore/RHI/Windows/WindowsWindow.hpp"

#include "LunariaCore/Renderer/Renderer.hpp"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_sdl2.h>

#include <SDL/SDL.h>
#include <SDL/SDL_syswm.h>

namespace Lunaria {

	static uint32_t s_SDLWindowCount = 0;

    static bool s_SplashScreenShown = true;

	WindowsWindow::WindowsWindow(const WindowProps& props)
		: m_WindowProps(props)
	{
		WindowsWindow::Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

	    // Initialize video subsystem (if needed)
	    if (SDL_WasInit(SDL_INIT_VIDEO) != 1)
	    {
	        if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
	            LU_CORE_ERROR("Failed to initialise SDL video subsystem: %s.", SDL_GetError());
	    }

	    // Initialize events subsystem (if needed)
	    if (SDL_WasInit(SDL_INIT_EVENTS) != 1)
	    {
	        if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0)
	            LU_CORE_ERROR("Failed to initialise SDL events subsystem: %s.", SDL_GetError());
	    }

	    // Show splash screen
	    if (s_SplashScreenShown)
	        CreateAndShowSplashScreen();

		LU_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			LU_CORE_ERROR("Unable to initialize SDL: {0}", SDL_GetError());

		m_Window = SDL_CreateWindow(props.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			static_cast<int>(props.Width), static_cast<int>(props.Height), SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE);
	    SDL_HideWindow(m_Window);

#if defined(LU_DEBUG)
    if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

		if (!m_Window)
		{
			LU_CORE_ERROR("Failed to create SDL window: {0}", SDL_GetError());
			SDL_Quit();
			return;
		}

		m_Context = GraphicsContext::Create(m_Window);
		m_Context->Init();

		SetVSync(true);

		// Set window icon
		SetIcon("Resources/Icons/Logo.png");

		SDL_SetWindowResizable(m_Window, SDL_TRUE);
		SDL_SetWindowData(m_Window, "this", this);

		// Hide decorations

		// Set SDL callbacks
		SDL_SetEventFilter([](void* userdata, SDL_Event* event) {
			const WindowsWindow* window = static_cast<WindowsWindow*>(userdata);
			if (event->type == SDL_WINDOWEVENT && event->window.event == SDL_WINDOWEVENT_CLOSE &&
				event->window.windowID == SDL_GetWindowID(window->m_Window))
			{
				WindowCloseEvent e;
				window->m_Data.EventCallback(e);
			}
			return 1;
		}, this);

	    // Hide splash screen
	    if (s_SplashScreenShown)
	    {
            // Wait for a few seconds
	        std::this_thread::sleep_for(std::chrono::seconds(2));

            s_SplashScreenShown = false;
            HideSplashScreen();

	        // Show the window
	        SDL_ShowWindow(m_Window);
        }
	}

	void WindowsWindow::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
		--s_SDLWindowCount;

		if (s_SDLWindowCount == 0) {
			LU_CORE_INFO("Terminating SDL...");
			SDL_Quit();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event); // Process events for ImGui

			switch (event.type)
			{
			case SDL_QUIT:
			{
				WindowCloseEvent e;
				m_Data.EventCallback(e);
				break;
			}
			case SDL_WINDOWEVENT:
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_SIZE_CHANGED:
				{
					m_Data.Width = event.window.data1;
					m_Data.Height = event.window.data2;
					WindowResizeEvent e(event.window.data1, event.window.data2);
					m_Data.EventCallback(e);
					break;
				}
				case SDL_WINDOWEVENT_CLOSE:
				{
					WindowCloseEvent e;
					m_Data.EventCallback(e);
					break;
				}
				default:
					break;
				}
				break;
			}
			case SDL_KEYDOWN:
			case SDL_KEYUP:
			{
				const int key = event.key.keysym.sym;
				const int scancode = event.key.keysym.scancode;
				KeyPressedEvent e(key, scancode);
				m_Data.EventCallback(e);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
			{
				const int button = event.button.button;

				// Check if left mouse button is pressed
				if (button == SDL_BUTTON_LEFT && event.type == SDL_MOUSEBUTTONDOWN)
				{
					// Start resizing window
					constexpr int borderSize = 4;

					int xPos, yPos;
					int width, height;
					SDL_GetMouseState(&xPos, &yPos);
					SDL_GetWindowSize(m_Window, &width, &height);

					if (yPos < borderSize)
					{
						if (xPos < borderSize)
							StartResize(WindowBorder::TopLeft);
						else if (xPos > width - borderSize)
							StartResize(WindowBorder::TopRight);
						else
							StartResize(WindowBorder::Top);
					}
					else if (yPos > height - borderSize)
					{
						if (xPos < borderSize)
							StartResize(WindowBorder::BottomLeft);
						else if (xPos > width - borderSize)
							StartResize(WindowBorder::BottomRight);
						else
							StartResize(WindowBorder::Bottom);
					}
					else
					{
						if (xPos < borderSize)
							StartResize(WindowBorder::Left);
						else if (xPos > width - borderSize)
							StartResize(WindowBorder::Right);
					}
				}

				MouseButtonPressedEvent e(button);
				m_Data.EventCallback(e);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			{
				// Reset cursor after resizing
				SDL_SetCursor(nullptr);

				const int button = event.button.button;
				MouseButtonReleasedEvent e(button);
				m_Data.EventCallback(e);
				break;
			}
			case SDL_MOUSEMOTION:
			{
				const float xPos = static_cast<float>(event.motion.x);
				const float yPos = static_cast<float>(event.motion.y);
				MouseMovedEvent e(xPos, yPos);
				m_Data.EventCallback(e);
				break;
			}
			case SDL_MOUSEWHEEL:
			{
				const float xOffset = static_cast<float>(event.wheel.x);
				const float yOffset = static_cast<float>(event.wheel.y);
				MouseScrolledEvent e(xOffset, yOffset);
				m_Data.EventCallback(e);
				break;
			}
			default:
				break;
			}
		}

		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		SDL_GL_SetSwapInterval(enabled ? 1 : -1);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::StartDrag() const
	{
		if (!m_Window)
			return;

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(m_Window, &wmInfo);

#if defined(SDL_VIDEO_DRIVER_WINDOWS)
		const HWND hwnd = wmInfo.info.win.window;
		ReleaseCapture();
		SendMessageA(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
#endif
	}

	void WindowsWindow::SetIcon(const std::string& filepath) const
	{
		if (!m_Window)
			return;

		SDL_Surface* icon = SDL_LoadBMP(filepath.c_str());
		if (!icon)
		{
			LU_CORE_ERROR("Failed to load icon: {0}", SDL_GetError());
			return;
		}

		SDL_SetWindowIcon(m_Window, icon);
		SDL_FreeSurface(icon);
	}

	void WindowsWindow::StartResize(WindowBorder border) const
	{
		if (!m_Window)
			return;

		// Convert from WindowBorder enum to SDL2 border constant
		WPARAM windowsBorder = 0;
		SDL_Cursor* cursor = nullptr;
		switch (border)
		{
			case WindowBorder::Left:
			{
				windowsBorder = HTLEFT;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
				break;
			}
			case WindowBorder::Right:
			{
				windowsBorder = HTRIGHT;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
				break;
			}
			case WindowBorder::Top:
			{
				windowsBorder = HTTOP;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
				break;
			}
			case WindowBorder::Bottom:
			{
				windowsBorder = HTBOTTOM;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
				break;
			}
			case WindowBorder::TopLeft:
			{
				windowsBorder = HTTOPLEFT;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
				break;
			}
			case WindowBorder::TopRight:
			{
				windowsBorder = HTTOPRIGHT;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
				break;
			}
			case WindowBorder::BottomLeft:
			{
				windowsBorder = HTBOTTOMLEFT;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENESW);
				break;
			}
			case WindowBorder::BottomRight:
			{
				windowsBorder = HTBOTTOMRIGHT;
				cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
				break;
			}
		}

		// Set cursor and capture mouse
		if (cursor)
			SDL_SetCursor(cursor);

		// Resize window until mouse button is released
		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(m_Window, &wmInfo);

#if defined(SDL_VIDEO_DRIVER_WINDOWS)
		const HWND hwnd = wmInfo.info.win.window;
		ReleaseCapture();
		SendMessageA(hwnd, WM_NCLBUTTONDOWN, windowsBorder, 0);
#endif

	}

	bool WindowsWindow::IsMaximized() const
	{
		return static_cast<bool>(SDL_GetWindowFlags(m_Window) & SDL_WINDOW_MAXIMIZED);
	}

	bool WindowsWindow::IsMinimized() const
	{
		return static_cast<bool>(SDL_GetWindowFlags(m_Window) & SDL_WINDOW_MINIMIZED);
	}

	void WindowsWindow::Maximize(bool restore) const
	{
		if (!m_Window)
			return;

		if (restore)
			SDL_RestoreWindow(m_Window);
		else
			SDL_MaximizeWindow(m_Window);
	}

	void WindowsWindow::Minimize() const
	{
		if (!m_Window)
			return;

		SDL_MinimizeWindow(m_Window);
	}

}
