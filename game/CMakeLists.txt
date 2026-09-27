cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME game)

project(${PROJECT_NAME} LANGUAGES C CXX)

# =========================
# Source Files
# =========================

file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# =========================
# Executable
# =========================

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# =========================
# Include Directories
# =========================

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(${PROJECT_NAME}
    PUBLIC
        cxx_std_23
)

# =========================
# Compile Definitions
# =========================

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
    PRIVATE
        mira
)

