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

set(SHADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shader)
set(OUTPUT_SHADER_DIR ${CMAKE_SOURCE_DIR}/Binaries/Debug/Sandbox/shader)

file(GLOB SHADER_FILES
    ${SHADER_DIR}/*.hlsl
)

foreach(SHADER ${SHADER_FILES})

    get_filename_component(FILE_NAME ${SHADER} NAME_WE)

    if(FILE_NAME MATCHES "VS$")
        set(PROFILE vs_5_0)
    elseif(FILE_NAME MATCHES "PS$")
        set(PROFILE ps_5_0)
    endif()

    add_custom_command(
        OUTPUT ${OUTPUT_SHADER_DIR}/${FILE_NAME}.cso

        COMMAND fxc
        /T ${PROFILE}
        /E main
        /Fo ${OUTPUT_SHADER_DIR}/${FILE_NAME}.cso
        /Zi
        /Od
        ${SHADER}

        DEPENDS ${SHADER}
    )

    list(APPEND COMPILED_SHADERS
        ${OUTPUT_SHADER_DIR}/${FILE_NAME}.cso
    )

endforeach()

add_custom_target(Shaders ALL
    DEPENDS ${COMPILED_SHADERS}
)

add_dependencies(Sandbox Shaders)


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