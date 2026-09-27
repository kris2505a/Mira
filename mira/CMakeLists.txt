add_library(mira INTERFACE)

add_subdirectory(src/core)
add_subdirectory(src/render_hw)
add_subdirectory(src/engine)


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
