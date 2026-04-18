# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("Mira")

# Include sub-projects.
add_subdirectory ("Renderer")
add_subdirectory ("BaseEngine")
add_subdirectory ("Game")
