workspace "Asteroids"
    architecture "x64"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    include "Game"
    group "Engine"
    include "Renderer"
