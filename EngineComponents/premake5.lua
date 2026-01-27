outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

-------------------------------------------------
-- STB IMAGE
-------------------------------------------------
include "thirdparty/stb_image"

-------------------------------------------------
-- RENDERER
-------------------------------------------------
project "Renderer"
    location "Renderer"
    kind "StaticLib"
    language "C++"

    cppdialect "C++20"
    staticruntime "Off"
    systemversion "latest"

    targetdir ("../binaries/" .. outputDir .. "/%{prj.name}")
    objdir    ("../intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "Renderer/include/**.h",
        "Renderer/include/**.hpp",
        "Renderer/src/**.h",
        "Renderer/src/**.hpp",
        "Renderer/src/**.cpp"
    }

    includedirs {
        "Renderer/include",
        "Renderer/src",

        -- stb image headers (optional but useful)
        "thirdparty/stb_image/src"
    }

    links {
        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib",

        "STB_Image"
    }

    defines {
        "PLATFORM_WINDOWS"
    }

    filter "system:windows"
        defines { "NOMINMAX" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"


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

    targetdir ("../binaries/" .. outputDir .. "/%{prj.name}")
    objdir    ("../intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "Engine/src/**.h",
        "Engine/src/**.hpp",
        "Engine/src/**.cpp"
    }

    includedirs {
        "Engine/src",

        -- Renderer public headers
        "Renderer/include",

        -- thirdparty
        "thirdparty/stb_image/src"
    }

    links {
        "Renderer",
        "STB_Image"
    }

    defines {
        "PLATFORM_WINDOWS",
        "ENGINE_BUILD"
    }

    filter "system:windows"
        defines { "NOMINMAX" }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
