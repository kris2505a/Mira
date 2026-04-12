project "BaseEngine"
    location "."
    kind "SharedLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("../Binaries/%{cfg.buildcfg}/%{prj.name}")
    objdir ("../Intermediate/%{cfg.buildcfg}/%{prj.name}")

    files
    {
        "Sources/**.cpp",
        "Includes/**.hpp",
        "Includes/**.h"
    }

    includedirs
    {
        "Includes",
        "../Renderer/Includes",
        "deps/include"
    }

    libdirs
    {
        "deps/lib",
        "../Binaries/%{cfg.buildcfg}/Renderer"
    }

    links
    {
        "Renderer",
        "SDL3"
    }

    defines
    {
        "MIRA_ENGINE_BUILD",
        "SDL_MAIN_HANDLED",
        "MIRA_ENGINE"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter {}

    postbuildcommands
    {
        '{COPY} "%{cfg.buildtarget.abspath}" "../Binaries/%{cfg.buildcfg}/Game/"'
    }