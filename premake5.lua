workspace "Mira2D"
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
    staticruntime "Off"


    targetdir("binaries/" .. outputDir .. "/%{prj.name}")
    objdir("intermediate/" .. outputDir .. "/%{prj.name}")
	
    pchheader "MiraPreCompHeader.h"
    pchsource "MiraEngine/sources/MiraPreCompHeader.cpp"

    files {
        "%{prj.name}/sources/**.h",
        "%{prj.name}/sources/**.cpp"
    }

    includedirs {
        "%{prj.name}/sources",
    }
    
    links {
        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"
        buildoptions { "/wd4251" }


    defines {
        "API_ENGINE"
    }
	
	postbuildcommands {
		"{COPY} %{cfg.buildtarget.abspath} ../binaries/" .. outputDir .. "/Sandbox"
	}

    filter "configurations:Debug"
        defines {
            "MIRA_DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "windowedApp"
    language "C++"
    staticruntime "Off"
    entrypoint "WinMainCRTStartup"  

    targetdir("binaries/" .. outputDir .. "/%{prj.name}")
    objdir("intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/sources/**.h",
        "%{prj.name}/sources/**.cpp"
    }

    includedirs {
        "%{prj.name}/sources",
		"MiraEngine/sources/"
    }

    links {
		"MiraEngine",
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"


    filter "configurations:Debug" 
        defines {
            "MIRA_DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

	