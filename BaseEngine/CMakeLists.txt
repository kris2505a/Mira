cmake_minimum_required(VERSION 3.20)

project(BaseEngine LANGUAGES C CXX)

# =========================
# Source Files
# =========================

file(GLOB_RECURSE BASE_ENGINE_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shader/*.hlsl
)

# =========================
# ImGui
# =========================

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/ImGui)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp

    # Backends
    ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
    ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
)

# =========================
# Library
# =========================

add_library(BaseEngine SHARED
    ${BASE_ENGINE_SOURCES}
    ${IMGUI_SOURCES}
 )

# =========================
# Precompiled Headers
# =========================

target_precompile_headers(BaseEngine PRIVATE
    src/MiraPch.hpp
)

# =========================
# Include Directories
# =========================

target_include_directories(BaseEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# =========================
# Compile Definitions
# =========================

target_compile_definitions(BaseEngine PRIVATE
    BUILD_DLL
    MIRA_ENGINE
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(BaseEngine PRIVATE
        MIRA_DEBUG
    )
endif()

if(WIN32)
    target_compile_definitions(BaseEngine PRIVATE
        PLATFORM_WINDOWS
        IMGUI_IMPL_WIN32_DISABLE_GAMEPAD
    )
endif()

# =========================
# Link Libraries
# =========================

target_link_libraries(BaseEngine PRIVATE
    d3d11
    dxgi
    d3dcompiler
)

# =========================
# Shader Compilation
# =========================

set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shader)

set(OUTPUT_SHADER_DIR
    ${CMAKE_SOURCE_DIR}/Binaries/Debug/Sandbox/shader
)

file(GLOB SHADER_FILES
    ${SHADER_DIR}/*.hlsl
)

foreach(SHADER ${SHADER_FILES})

    get_filename_component(FILE_NAME ${SHADER} NAME_WE)

    if(FILE_NAME MATCHES "VS$")
        set(PROFILE vs_5_0)

    elseif(FILE_NAME MATCHES "PS$")
        set(PROFILE ps_5_0)

    else()
        message(WARNING "Unknown shader type: ${FILE_NAME}")
        continue()
    endif()

    add_custom_command(
        OUTPUT ${OUTPUT_SHADER_DIR}/${FILE_NAME}.cso

        COMMAND ${CMAKE_COMMAND} -E make_directory
            ${OUTPUT_SHADER_DIR}

        COMMAND fxc
            /T ${PROFILE}
            /E main
            /Fo ${OUTPUT_SHADER_DIR}/${FILE_NAME}.cso
            /Zi
            /Od
            ${SHADER}

        DEPENDS ${SHADER}

        COMMENT "Compiling shader: ${FILE_NAME}.hlsl"
    )

    list(APPEND COMPILED_SHADERS
        ${OUTPUT_SHADER_DIR}/${FILE_NAME}.cso
    )

endforeach()

add_custom_target(Shaders ALL
    DEPENDS ${COMPILED_SHADERS}
)

add_dependencies(BaseEngine Shaders)

# =========================
# Output Directories
# =========================

set_target_properties(BaseEngine PROPERTIES

    RUNTIME_OUTPUT_DIRECTORY_DEBUG
        ${CMAKE_SOURCE_DIR}/Binaries/Debug/BaseEngine

    RUNTIME_OUTPUT_DIRECTORY_RELEASE
        ${CMAKE_SOURCE_DIR}/Binaries/Release/BaseEngine

    LIBRARY_OUTPUT_DIRECTORY_DEBUG
        ${CMAKE_SOURCE_DIR}/Binaries/Debug/BaseEngine

    LIBRARY_OUTPUT_DIRECTORY_RELEASE
        ${CMAKE_SOURCE_DIR}/Binaries/Release/BaseEngine
)

# =========================
# Copy DLL to Sandbox
# =========================

add_custom_command(TARGET BaseEngine POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:BaseEngine>
        $<TARGET_FILE_DIR:Sandbox>
)