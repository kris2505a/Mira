workspace "Mira-Engine"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

    startproject "Game"

outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

include "Engine/thirdparty/stb_image"

-------------------------------------------------
-- ENGINE
-------------------------------------------------
project "Engine"
    location "Engine"
    kind "StaticLib"
    language "C++"

    cppdialect "C++20"
    staticruntime "Off"
    systemversion "latest"

    targetdir ("binaries/" .. outputDir .. "/%{prj.name}")
    objdir    ("intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/shader/**.hlsl"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/thirdparty/GLFW/include",
        "%{prj.name}/thirdparty/stb_image/src"
    }

    libdirs {
        "%{prj.name}/thirdparty/GLFW/lib"
    }

    links {
        "glfw3.lib",

        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib",
        "dxguid.lib",

        "user32.lib",
        "gdi32.lib",
        "shell32.lib",
        "ole32.lib",
        "STB_Image"
    }

    defines {
        "PLATFORM_WINDOWS",
        "ENGINE_BUILD"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

-------------------------------------------------
-- GAME
-------------------------------------------------
project "Game"
    location "Game"
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
        "Engine/src",
        "Engine/thirdparty/GLFW/include",
        "%{prj.name}/thirdparty/stb_image/src"
    }

    libdirs {
        "Engine/thirdparty/GLFW/lib",
    }

    links {
        "Engine",
        "glfw3.lib",
        "STB_Image"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
