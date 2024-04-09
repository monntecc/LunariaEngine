#include "LunariaEditor/Layer/EditorLayer.hpp"

namespace Lunaria {

	class LunariaEditor final : public Application
	{
	public:
		LunariaEditor()
			: Application("Lunaria Editor")
		{
			PushLayer(new EditorLayer());
		}

		~LunariaEditor() override = default;

	};

	Application* CreateApplication()
	{
		return new LunariaEditor();
	}

}

#ifdef LU_PLATFORM_WINDOWS
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
#else
int main(int argc, char** argv)
#endif
{
	Lunaria::Log::Init();

	const auto app = Lunaria::CreateApplication();
	app->Run();
	delete app;

#ifdef LU_PLATFORM_WINDOWS
    return FALSE;
#else
    return 0;
#endif
}
