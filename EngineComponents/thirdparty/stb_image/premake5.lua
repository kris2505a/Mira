outputDir = "%{cfg.buildcfg}-%{cfg.architecture}"

-------------------------------------------------
-- STB_IMAGE
-------------------------------------------------
project "STB_Image"
    kind "StaticLib"
    language "C++"

    cppdialect "C++20"
    staticruntime "Off"
    systemversion "latest"

    targetdir ("binaries/" .. outputDir .. "/%{prj.name}")
    objdir    ("intermediate/" .. outputDir .. "/%{prj.name}")

    files {
        "src/stb_image.h",
        "src/stb_image.cpp"
    }

    includedirs {
        "src"    
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"
        defines { "_DEBUG" }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

