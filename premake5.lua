workspace "Mira"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
	
	startproject "Grass"
	
outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 

project "Engine"
    location "Engine"
    kind "sharedLib"
    language "C++"
    staticruntime "Off"


    targetdir("binaries/" .. outputDir .. "/%{prj.name}")
    objdir("intermediate/" .. outputDir .. "/%{prj.name}")

    -- pchheader("MiraPreCompHeader.h")
    -- pchsource("Engine/sources/MiraPreCompHeader.cpp")
	

    files {
        "%{prj.name}/Sources/**.h",
        "%{prj.name}/Sources/**.cpp"
    }

    includedirs {
        "%{prj.name}/Sources",
        "%{prj.name}/thirdparty/json/include"
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
        defines {"PLATFORM_WINDOWS"}  


    defines {
        "API_ENGINE"
    }
	
	postbuildcommands {
		"{COPY} %{cfg.buildtarget.abspath} ../binaries/" .. outputDir .. "/Grass"
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


project "Grass"
    location "Grass"
    kind "ConsoleApp"
    language "C++"
    staticruntime "Off"

    targetdir("Binaries/" .. outputDir .. "/%{prj.name}")
    objdir("Intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/Sources/**.h",
        "%{prj.name}/Sources/**.cpp"
    }

    includedirs {
        "%{prj.name}/Sources",
		"Engine/Sources/"
    }

    links {
		"Engine",

    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"
        defines {"PLATFORM_WINDOWS"}  


    filter "configurations:Debug" 
        defines {
            "MIRA_DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"
