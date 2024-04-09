-- premake5.lua
include "Dependecies.lua"

workspace "LunariaEngine"
   architecture "x64"
   configurations { "Debug", "Release" }
   startproject "LunariaEditor"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

include "Engine/LunariaCore/Build-Core.lua"
include "Engine/LunariaEditor/Build-Editor.lua"