#pragma once

#include "LunariaCore/Core/Base.hpp"
#include "LunariaCore/Core/Window.hpp"
#include "LunariaCore/Core/LayerStack.hpp"

#include "LunariaCore/Events/ApplicationEvent.hpp"
#include "LunariaCore/Events/Event.hpp"

#include "LunariaCore/UI/ImGuiLayer.hpp"

#ifdef LU_PLATFORM_WINDOWS
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow);
#else
int main(int argc, char** argv);
#endif;

namespace Lunaria {

	class LUNARIA_API Application
	{
	public:
		Application(const std::string& name = "Lunaria Application");
		virtual ~Application();
		
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() const { return *m_Window; }

		void Shutdown();
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;
	
		static Application* s_Instance;

#ifdef LU_PLATFORM_WINDOWS
		friend int APIENTRY::WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow);
#else
		friend int ::main(int argc, char** argv);
#endif;
	};

	// To be defined in client
	Application* CreateApplication();
};

