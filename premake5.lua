workspace "CyanEngine"
    architecture "x64"

    configurations {
        "Debug", "Release"
    }
    startproject "Game"

outputDir = "%{cfg.buildcfg}-%{cfg.architecture}" 


project "Engine"
    location "Engine"
    kind "sharedLib"
    language "C++"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("obj/" .. outputDir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/src/Core",
        "%{prj.name}/src/stb_image",
        "%{prj.name}/src/ECS",
        "%{prj.name}/src/Components",
        "%{prj.name}/thirdparty/SDL2/include"
    }

    libdirs {
        "%{prj.name}/thirdparty/SDL2/lib"
    }
    
    links {
        "SDL2.lib",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "Off"
        systemversion "latest"

    defines {
        "SDL_MAIN_HANDLED",
        "API_ENGINE"
    }

    filter "configurations:Debug"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        buildoptions "/MD"
        optimize "On"

project "Game"
    location "Game"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputDir .. "/%{prj.name}")
    objdir("obj/" .. outputDir .. "/%{prj.name}")

    files {       
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs {
        "Engine/thirdparty/SDL2/include",
        "Engine/src"
    }
    libdirs {
        "Engine/thirdparty/SDL2/lib"
    }
    
    links {
        "Engine",
        "SDL2.lib"
    }

    defines {
        "SDL_MAIN_HANDLED",
        "API_ENGINE"
    }

    postbuildcommands {
        -- Copy SDL2.dll to Game output dir
        "{COPY} %{wks.location}Engine/thirdparty/SDL2/lib/SDL2.dll %{cfg.targetdir}",

        -- Copy Engine.dll to Game output dir
        "{COPY} %{wks.location}bin/" .. outputDir .. "/Engine/Engine.dll %{cfg.targetdir}"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

    filter "configurations:Debug"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        buildoptions "/MD"
        optimize "On"
    
   
