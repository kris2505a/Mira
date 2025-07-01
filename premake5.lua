workspace "Mira"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
	
	startproject "Sandbox"
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 


project "MiraEngine"
    location "MiraEngine"
    kind "sharedLib"
    language "C++"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("obj/" .. outputDir .. "/%{prj.name}")
	
	pchheader "MiraPreCompHeader.h"
	pchsource "MiraEngine/src/MiraPreCompHeader.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src"
    }

    libdirs {
		
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
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        buildoptions "/MD"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "consoleApp"
    language "C++"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
		"MiraEngine/src/"
    }

    libdirs {
		
    }
    
    links {
        "opengl32.lib",
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
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        buildoptions "/MD"
        optimize "On"

	