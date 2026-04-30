cmake_minimum_required(VERSION 3.20)

project(BaseEngine LANGUAGES CXX)

add_subdirectory(deps/SDL)

file(GLOB_RECURSE BASEENGINE_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp
)

file(GLOB_RECURSE BASEENGINE_HEADERS
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/*.hpp
)

add_library(BaseEngine SHARED
    ${BASEENGINE_SOURCES}
    ${BASEENGINE_HEADERS}
)

target_compile_features(BaseEngine PUBLIC cxx_std_20)

target_include_directories(BaseEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
    ${CMAKE_SOURCE_DIR}/Renderer/Includes/Public
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/SDL/include
)

target_link_libraries(BaseEngine PRIVATE
    Renderer
    SDL3::SDL3
)

if (WIN32)
    target_compile_definitions(BaseEngine PUBLIC PLATFORM_WINDOWS)
elseif(UNIX)
    target_compile_definitions(BaseEngine PUBLIC PLATFORM_LINUX)
endif()

target_compile_definitions(BaseEngine PRIVATE
    MIRA_ENGINE_BUILD
    MIRA_ENGINE
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
