cmake_minimum_required(VERSION 3.20)

project(Game LANGUAGES CXX)

file(GLOB_RECURSE GAME_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources/*.hpp
)

add_executable(Game
    ${GAME_SOURCES}
)

target_compile_features(Game PUBLIC cxx_std_20)

target_include_directories(Game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Sources
    ${CMAKE_SOURCE_DIR}/BaseEngine/Includes/Public
)

target_link_libraries(Game PRIVATE
    BaseEngine
)

target_compile_definitions(Game PRIVATE
    MIRA_GAME
)

set_target_properties(Game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/Binaries/Debug/Game
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Binaries/Release/Game
)