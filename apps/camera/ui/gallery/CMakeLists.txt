
project(arguscamerauigallery)

set(SOURCES
    AppModuleGallery.cpp
    )

include_directories(
    ${EGL_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/apps/camera/ui/common
    ${CMAKE_SOURCE_DIR}/apps/camera/common
    ${CMAKE_SOURCE_DIR}/apps/camera/modules
    ${CMAKE_SOURCE_DIR}/apps/camera/renderer
    ${CMAKE_SOURCE_DIR}/samples/utils
    )

add_library(${PROJECT_NAME} ${SOURCES})
