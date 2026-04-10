project "Game"
    location "."

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("../Binaries/%{cfg.buildcfg}/%{prj.name}")
    objdir ("../Intermediate/%{cfg.buildcfg}/%{prj.name}")

    files
    {
        "Sources/**.cpp",
        "Sources/**.hpp"
    }

    includedirs
    {
        "Includes",
        "../Renderer/Includes/Public",
        "t_deps/include/"
    }

    libdirs
    {
        "../Binaries/%{cfg.buildcfg}/Renderer",
        "t_deps/lib/"
    }

    links
    {
        "Renderer",
        "SDL3.lib"
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
