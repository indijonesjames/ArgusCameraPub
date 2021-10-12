
cmake_minimum_required (VERSION 2.6)

project(ArgusCamera)

set (ArgusCamera_VERSION_MAJOR 1)
set (ArgusCamera_VERSION_MINOR 0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

find_package(Argus REQUIRED)
find_package(OpenGLES REQUIRED)
find_package(EGL REQUIRED)
find_package(EXPAT REQUIRED)

add_subdirectory(ui)
add_subdirectory(common)
add_subdirectory(modules)
add_subdirectory(renderer)

include(CPack)
