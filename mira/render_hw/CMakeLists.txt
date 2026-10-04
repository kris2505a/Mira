cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME render_hw)

project(${PROJECT_NAME} LANGUAGES C CXX)

# =========================
# Source Files
# =========================

file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/includes/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp
)

# =========================
# Library
# =========================

add_library(${PROJECT_NAME} SHARED
    ${PROJECT_SOURCES}
)

# =========================
# Include Directories
# =========================

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/pub

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_23
)

# =========================
# Compile Definitions
# =========================

target_compile_definitions(${PROJECT_NAME} PRIVATE
    BUILD_DLL
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        ${PROJECT_NAME}_DEBUG
    )
endif()

if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        PLATFORM_WINDOWS
    )
endif()

# =========================
# Link Libraries
# =========================

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        core

    PRIVATE
)