add_library(mira INTERFACE)

add_subdirectory(core)
add_subdirectory(render_hw)
add_subdirectory(engine)


target_include_directories(mira
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(mira
    INTERFACE
        core
        render_hw
        engine
)