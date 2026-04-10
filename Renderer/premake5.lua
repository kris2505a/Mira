project "Renderer"
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
        "Includes/**.hpp"
    }

    includedirs
    {
        "Includes"
    }
    
    links 
    {
        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib"
    }
    
    defines 
    {
    "MIRE_RENDERER_BUILD"
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
