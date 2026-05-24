cmake_minimum_required(VERSION 3.20)

project(Sandbox LANGUAGES C CXX)

file(GLOB_RECURSE SANDBOX_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(Sandbox
    ${SANDBOX_SOURCES}
)

target_include_directories(Sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/BaseEngine/src
)

target_compile_definitions(Sandbox PRIVATE
    MIRA_GAME
)

target_link_libraries(Sandbox PRIVATE
    BaseEngine
)

set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG
        ${CMAKE_SOURCE_DIR}/Binaries/Debug/Sandbox

    RUNTIME_OUTPUT_DIRECTORY_RELEASE
        ${CMAKE_SOURCE_DIR}/Binaries/Release/Sandbox
)
