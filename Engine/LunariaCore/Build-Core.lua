project "LunariaCore"
    kind "SharedLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	systemversion "latest"

	pchheader "lepch.hpp"
	pchsource "src/lepch.cpp"

	targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
    debugdir("%{wks.location}")

	files { "**.hpp", "**.cpp" }

	defines { "_CRT_SECURE_NO_WARNINGS", "GLFW_INCLUDE_NONE", "LU_DYNAMIC_LINK", "LU_BUILD_DLL", "IMGUI_DEFINE_MATH_OPERATORS" }

	includedirs { "src", "include", "%{LOCAL.MATH}", "%{LOCAL.ECS}", "%{LOCAL.WINDOW}",
		"%{INCLUDES.spdlog}", "%{INCLUDES.SDL}", "%{INCLUDES.Glad}", "%{INCLUDES.VulkanSDK}", "%{INCLUDES.ImGui}", "%{INCLUDES.glm}", "%{INCLUDES.stb_image}", "%{INCLUDES.entt}",  "%{INCLUDES.spirv_cross}", "%{INCLUDES.nlohmann}" }

	links { "LunariaMath", "LunariaECS", "LunariaWindowing" } -- Link engine local dependencies
	libdirs { "%{wks.location}/Libraries" }

	postbuildcommands
	{
		-- Create editor binaries directory if not exists
		"{MKDIR} %{wks.location}/Binaries/" .. OutputDir .. "/LunariaEditor",

		-- Copy core shared library to editor project
		"{COPY} %{cfg.buildtarget.relpath} %{wks.location}/Binaries/" .. OutputDir .. "/LunariaEditor/",

		-- Copy SDL2 shared library to editor project
		"{COPY} %{wks.location}/Libraries/SDL2.dll %{wks.location}/Binaries/" .. OutputDir .. "/LunariaEditor/"
	}

	filter "system:windows"
		links { "opengl32.lib" }
        removefiles { "src/RHI/Linux/**.cpp", "include/LunariaCore/RHI/Linux/**.hpp" }

	filter "system:linux"
	    links { "GL" }
        removefiles { "src/RHI/Windows/**.cpp", "include/LunariaCore/RHI/Windows/**.hpp" }

	filter "configurations:Debug"
		links { "SDL2", "Glad", "ImGui", "spirv-cross-c_debug", "spirv-cross-core_debug", "spirv-cross-cpp_debug", "spirv-cross-glsl_debug", "vulkan", "stb_image" }
		defines "LU_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		links { "SDL2", "Glad", "ImGui", "spirv-cross-c", "spirv-cross-core", "spirv-cross-cpp", "spirv-cross-glsl", "vulkan", "stb_image" }
		defines "LU_RELEASE"
		runtime "Release"
		optimize "on"
