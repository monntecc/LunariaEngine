project "LunariaWindowing"
    kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"
	systemversion "latest"

	targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

	files { "**.hpp", "**.cpp" }

	includedirs { "include", "%{LOCAL.MATH}", "%{INCLUDES.SDL}", "%{LOCAL.CORE}", "%{INCLUDES.stb_image}", "%{INCLUDES.spdlog}" }

    libdirs { "%{wks.location}/Libraries" }
    links { "SDL2", "stb_image" } 

	filter "configurations:Debug"
		defines "LU_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LU_RELEASE"
		runtime "Release"
		optimize "on"
