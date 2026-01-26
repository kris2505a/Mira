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
        "%{prj.name}/thirdparty/stb_image/src",
        "%{prj.name}/thirdparty/assimp/include"
    }

    libdirs {
        "%{prj.name}/thirdparty/assimp/lib"
    }

    links {

        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib",
        
        "STB_Image",
        "assimp-vc143-mt.lib"
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
        "%{prj.name}/thirdparty/stb_image/src"
    }

    libdirs {
    }

    links {
        "Engine",
        "STB_Image"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
