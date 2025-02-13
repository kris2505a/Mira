workspace "Cyan"
    architecture "x64"

    configurations{
        "Debug",
        "Relelase"
    }
    startproject "Game"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Cyan"
    location "Cyan"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")

    files{
        
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs{
        "%{prj.location}/thirdparty/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines{
            "PLATFORM_WINDOWS",
            "PROJECT_ENGINE"
        }

    filter "configurations:Debug"
        defines "CY_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "CY_RELEASE"
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
        symbols "On"

    filter "configurations:Release"
        defines "CY_RELEASE"
        optimize "On"