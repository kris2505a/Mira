workspace "Cyan"
    architecture "x64"

    configurations{
        "Debug",
        "Relelase"
    }
    startproject "Game"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


includeDirs = {}

includeDirs["GLFW"] = "Cyan/thirdparty/GLFW/include"
include "Cyan/thirdparty/GLFW"

project "Cyan"
    location "Cyan"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")
    pchheader "PreCompHeaders.hpp"
    pchsource "Cyan/src/PreCompHeaders.cpp"

    files{
        
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "%{prj.name}/src",
        "%{prj.location}/thirdparty/spdlog/include",
        "%{includeDirs.GLFW}"
    }

    links{
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

        defines{
            "PLATFORM_WINDOWS",
            "PROJECT_ENGINE"
        }

    filter "configurations:Debug"
        defines "CY_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "CY_RELEASE"
        buildoptions "/MD"
        optimize "On"
        

project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files{
        
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "Cyan/thirdparty/spdlog/include",
        "Cyan/src"
    }

    links{
        "Cyan"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines{
            "PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "CY_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "CY_RELEASE"
        buildoptions "/MD"
        optimize "On"