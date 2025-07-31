workspace "Mira"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
	
	startproject "Sandbox"
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 

IncludeDirectories = {}

IncludeDirectories["SFML"] = "MiraEngine/thirdparty/SFML"


project "MiraEngine"
    location "MiraEngine"
    kind "sharedLib"
    language "C++"
    staticruntime "Off"


    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("obj/" .. outputDir .. "/%{prj.name}")
	
	pchheader "MiraPreCompHeader.h"
	pchsource "MiraEngine/src/MiraPreCompHeader.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
		"%{IncludeDirectories.SFML}/include"
    }

    libdirs {
		"%{IncludeDirectories.SFML}/lib"
    }
    
    links {
        "opengl32.lib",
		"winmm.lib",
		"gdi32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

    defines {
        "API_ENGINE"
    }
	
	postbuildcommands {
		"{COPY} %{cfg.buildtarget.abspath} ../bin/" .. outputDir .. "/Sandbox"
	}


    filter "configurations:Debug"
        links {
            "sfml-audio-d.lib",
            "sfml-graphics-d.lib",
            "sfml-window-d.lib",
            "sfml-main-d.lib",
            "sfml-system-d.lib"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        links {
            "sfml-audio.lib",
            "sfml-graphics.lib",
            "sfml-window.lib",
            "sfml-main.lib",
            "sfml-system.lib"
        }
        runtime "Release"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "consoleApp"
    language "C++"
    staticruntime "Off"


    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{IncludeDirectories.SFML}/include",
        "%{prj.name}/src",
		"MiraEngine/src/"
    }

    libdirs {
		"%{IncludeDirectories.SFML}/lib"
    }
    
    links {
        "opengl32.lib",
		"winmm.lib",
		"gdi32.lib",
		"MiraEngine",
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

    defines {
	
    }

    filter "configurations:Debug" 
        links {
            "sfml-audio-d.lib",
            "sfml-graphics-d.lib",
            "sfml-window-d.lib",
            "sfml-main-d.lib",
            "sfml-system-d.lib"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        links {
            "sfml-audio.lib",
            "sfml-graphics.lib",
            "sfml-window.lib",
            "sfml-main.lib",
            "sfml-system.lib"
        }
        runtime "Release"
        optimize "On"

	