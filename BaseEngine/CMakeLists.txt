cmake_minimum_required(VERSION 3.20)

project(BaseEngine LANGUAGES CXX)

set(BASEENGINE_SOURCES
    Sources/Engine.cpp
    Sources/Window.cpp
    Sources/LayerManager.cpp
)

set(BASEENGINE_HEADERS
    Includes/Core/Core.hpp
    Includes/Core/Engine.hpp

    Includes/Events/Event.hpp
    Includes/Events/EventSystem.hpp

    Includes/Logging/Log.hpp

    Includes/Layers/Layer.hpp
    Includes/Layers/LayerManager.hpp

    Includes/Public/MiraEngine.hpp

    Includes/Window/Window.hpp
)

add_library(BaseEngine SHARED
    ${BASEENGINE_SOURCES}
    ${BASEENGINE_HEADERS}
)

target_compile_features(BaseEngine PUBLIC cxx_std_20)

target_include_directories(BaseEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
    ${CMAKE_SOURCE_DIR}/Renderer/Includes/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/include
)


target_link_libraries(BaseEngine PRIVATE
    Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib/glfw3.lib
)

target_compile_definitions(BaseEngine PRIVATE
    MIRA_ENGINE_BUILD
    MIRA_ENGINE
    GLFW_STATIC
)

set_target_properties(BaseEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/Binaries/Debug/BaseEngine
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Binaries/Release/BaseEngine
    LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/Binaries/Debug/BaseEngine
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Binaries/Release/BaseEngine
)

add_custom_command(TARGET BaseEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:BaseEngine>
        ${CMAKE_SOURCE_DIR}/Binaries/$<CONFIG>/Game
)