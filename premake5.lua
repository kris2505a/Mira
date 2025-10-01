workspace "Mira2D"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
	
	startproject "Sandbox"
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 

project "Engine"
    location "Engine"
    kind "sharedLib"
    language "C++"
    staticruntime "Off"


    targetdir("binaries/" .. outputDir .. "/%{prj.name}")
    objdir("intermediate/" .. outputDir .. "/%{prj.name}")

    pchheader("MiraPreCompHeader.h")
    pchsource("Engine/sources/MiraPreCompHeader.cpp")
	

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
        cppdialect "C++23"
        staticruntime "Off"
        systemversion "latest"
        buildoptions { "/wd4251" }
        defines {"PLATFORM_WINDOWS"}  


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
    -- kind "WindowedApp"
    kind "ConsoleApp"
    language "C++"
    staticruntime "Off"

    targetdir("binaries/" .. outputDir .. "/%{prj.name}")
    objdir("intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/sources/**.h",
        "%{prj.name}/sources/**.cpp"
    }

    includedirs {
        "%{prj.name}/sources",
		"Engine/sources/"
    }

    links {
		"Engine",
        "d3d11.lib",
        "dxgi.lib",
        "d3dcompiler.lib"
    }

    filter "system:windows"
        cppdialect "C++23"
        staticruntime "Off"
        systemversion "latest"
        defines {"PLATFORM_WINDOWS"}  
        -- entrypoint "WinMainCRTStartup"  
        -- linkoptions { "/SUBSYSTEM:WINDOWS" }



    filter "configurations:Debug" 
        defines {
            "MIRA_DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
