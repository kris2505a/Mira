cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME engine)

project(${PROJECT_NAME} LANGUAGES C CXX)

# =========================
# Source Files
# =========================

set(PROJECT_SOURCES
    mi_engine_core.hpp
    mi_engine.hpp
    mi_engine.cpp
    events/event.hpp
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

target_include_directories(${PROJECT_NAME} PUBLIC
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
    _UNICODE
    UNICODE
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
        render_hw
)

# =========================
# Engine Dependencies
# =========================

# target_link_libraries(${PROJECT_NAME}
#     PRIVATE
#         Core
#         RenderHardware
# )
