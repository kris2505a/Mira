workspace "Mira"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
	
	startproject "Sandbox"
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 

IncludeDirectories = {}

IncludeDirectories["SDL2"] = "MiraEngine/thirdparty/SDL2"


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
		"%{IncludeDirectories.SDL2}/include"
    }

    libdirs {
		"%{IncludeDirectories.SDL2}/lib"
    }
    
    links {
        "SDL2.lib",
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
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
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
        "%{IncludeDirectories.SDL2}/include",
        "%{prj.name}/src",
		"MiraEngine/src/"
    }

    libdirs {
		
    }
    
    links {
		"winmm.lib",
		"gdi32.lib",
		"MiraEngine"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

    defines {
	
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

	