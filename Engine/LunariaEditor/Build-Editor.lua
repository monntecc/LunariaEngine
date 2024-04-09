project "LunariaEditor"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	systemversion "latest"

	targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
	debugdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}") -- Set the working directory for the debugger

	files { "**.cpp", "**.hpp" }

	includedirs { "include", "%{wks.location}/Engine/LunariaCore/src", "%{wks.location}/Engine/LunariaCore/include",
		"%{INCLUDES.spdlog}", "%{INCLUDES.ImGui}", "%{INCLUDES.SDL}", "%{INCLUDES.entt}", "%{INCLUDES.glm}" }

	defines { "LU_DYNAMIC_LINK", "IMGUI_DEFINE_MATH_OPERATORS" }
	links { "LunariaCore" }

	postbuildcommands { ("{COPY} %{wks.location}/Resources %{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}/Resources") }

	filter "system:windows"
		kind "WindowedApp"
		defines { "IMGUI_API=__declspec(dllimport)", "LU_WINDOWED" }

	filter "system:linux"
		kind "ConsoleApp"
	    defines { "IMGUI_API=__attribute__ ((dllexport))" }

	filter "configurations:Debug"
		defines "LU_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LU_RELEASE"
		runtime "Release"
		optimize "on"