cmake_minimum_required(VERSION 3.20)


set(GLFW_BUILD_WAYLAND OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)

set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)

set(GLFW_LIBRARY_TYPE STATIC CACHE STRING "" FORCE)

add_subdirectory(thirdparty/GLFW)


project(BaseEngine LANGUAGES C CXX)

# =========================
# Source Files
# =========================

file(GLOB_RECURSE BASE_ENGINE_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
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

    # GLFW + Vulkan Backends
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm/
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends,
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/GLFW/include
)

# =========================
# Compile Definitions
# =========================

target_compile_definitions(BaseEngine PRIVATE
    BUILD_DLL
    MIRA_ENGINE
    GLFW_INCLUDE_NONE
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
    Vulkan::Vulkan
    glfw
)

# =========================
# Platform
# =========================

find_package(Vulkan REQUIRED)

if(WIN32)

    target_compile_definitions(BaseEngine PRIVATE
        PLATFORM_WINDOWS
        VK_USE_PLATFORM_WIN32_KHR
    )

elseif(UNIX AND NOT APPLE)

    find_package(X11 REQUIRED)

    target_compile_definitions(BaseEngine PRIVATE
        PLATFORM_LINUX_X11
        VK_USE_PLATFORM_XLIB_KHR
    )

    target_link_libraries(BaseEngine PRIVATE
        X11
    )

endif()


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
# Copy Build files to Sandbox
# =========================

add_custom_command(TARGET BaseEngine POST_BUILD

    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:BaseEngine>
        $<TARGET_FILE_DIR:Sandbox>

)