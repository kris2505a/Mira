cmake_minimum_required(VERSION 3.20)

project(Mira LANGUAGES C CXX)

# =========================
# C++ Standard
# =========================

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =========================
# Output Directories
# =========================

set(BINARY_DIR
    ${CMAKE_SOURCE_DIR}/bin
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${BINARY_DIR}/$<CONFIG>
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${BINARY_DIR}/$<CONFIG>
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${BINARY_DIR}/$<CONFIG>
)

# =========================
# Compile Commands
# =========================

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
    DEPENDS ${CMAKE_BINARY_DIR}/compile_commands.json
)

# =========================
# Projects
# =========================

add_subdirectory(mira)
add_subdirectory(sandbox)