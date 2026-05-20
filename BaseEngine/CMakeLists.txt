cmake_minimum_required(VERSION 3.20)

project(BaseEngine LANGUAGES C CXX)


file(GLOB_RECURSE BASE_ENGINE_SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(BaseEngine SHARED
    ${BASE_ENGINE_SOURCES}
)

target_precompile_headers(BaseEngine PRIVATE
        src/MiraPch.hpp
)

target_include_directories(BaseEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm/
)

target_compile_definitions(BaseEngine PRIVATE
    BUILD_DLL
    MIRA_ENGINE
)

target_link_libraries(BaseEngine PRIVATE
    d3d11
    dxgi
    d3dcompiler
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(BaseEngine PRIVATE
            MIRA_DEBUG
    )
endif()

set_target_properties(BaseEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/Binaries/Debug/BaseEngine
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Binaries/Release/BaseEngine
    LIBRARY_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_SOURCE_DIR}/Binaries/Debug/BaseEngine
    LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/Binaries/Release/BaseEngine
)

add_custom_command(TARGET BaseEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:BaseEngine>
        $<TARGET_FILE_DIR:Sandbox>
)

add_custom_command(TARGET BaseEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:BaseEngine>
        $<TARGET_FILE_DIR:Sandbox>
)