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
        "../BaseEngine/Includes/Public"
    }

    libdirs
    {
        "../Binaries/%{cfg.buildcfg}/BaseEngine"
    }

    links
    {
        "BaseEngine"
    }
    
    defines
    {
        "MIRA_GAME"
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