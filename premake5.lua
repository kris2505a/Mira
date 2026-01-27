workspace "Mira"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

-------------------------------------------------
-- Include thirdparty & engine components
-------------------------------------------------
include "EngineComponents/thirdparty/stb_image"
include "EngineComponents"

-------------------------------------------------
-- SANDBOX
-------------------------------------------------
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "Off"
    systemversion "latest"

    targetdir ("binaries/" .. outputDir .. "/%{prj.name}")
    objdir    ("intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",

        -- Engine includes
        "EngineComponents/Engine/src",
        "EngineComponents/Renderer/include",

        -- thirdparty includes
        "EngineComponents/thirdparty/stb_image/src"
    }

    links {
        "Engine",
        "Renderer",
        "STB_Image"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
