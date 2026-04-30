cmake_minimum_required(VERSION 3.20)

project(Renderer LANGUAGES CXX)

# -----------------------------
# Collect sources recursively
# -----------------------------
file(GLOB_RECURSE RENDERER_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp
)

file(GLOB_RECURSE RENDERER_HEADERS CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes/*.h
)

# -----------------------------
# Create library
# -----------------------------
add_library(Renderer SHARED
    ${RENDERER_SOURCES}
    ${RENDERER_HEADERS}
)

target_compile_features(Renderer PUBLIC cxx_std_20)

# -----------------------------
# Include directories
# -----------------------------
target_include_directories(Renderer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Includes
)

# -----------------------------
# Platform-specific config
# -----------------------------
if (WIN32)
    target_compile_definitions(Renderer PUBLIC PLATFORM_WINDOWS)

    target_link_libraries(Renderer PRIVATE
        d3d11
        dxgi
        d3dcompiler
    )

    # Optional: Only compile DX11 sources on Windows
    file(GLOB_RECURSE DX11_SOURCES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Dx11/*.cpp
    )

    target_sources(Renderer PRIVATE ${DX11_SOURCES})

elseif(UNIX)
    target_compile_definitions(Renderer PUBLIC PLATFORM_LINUX)

    # Exclude DX11 files on Linux
    file(GLOB_RECURSE DX11_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Sources/Dx11/*.cpp
    )

    list(REMOVE_ITEM RENDERER_SOURCES ${DX11_SOURCES})
endif()

# -----------------------------
# Internal definitions
# -----------------------------
target_compile_definitions(Renderer PRIVATE
    MIRE_RENDERER_BUILD
)

# -----------------------------
# Output directories
# -----------------------------
set_target_properties(Renderer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/Binaries/Debug/Renderer
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Binaries/Release/Renderer
    LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/Binaries/Debug/Renderer
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Binaries/Release/Renderer
)

# -----------------------------
# Post-build copy
# -----------------------------
add_custom_command(TARGET Renderer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Renderer>
        ${CMAKE_SOURCE_DIR}/Binaries/$<CONFIG>/Game
)