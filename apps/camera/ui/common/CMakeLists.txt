
project(arguscamerauicommon)

set(SOURCES
    App.cpp
    AppModuleGeneric.cpp
    )

include_directories(
    ${ARGUS_INCLUDE_DIR}
    ${EGL_INCLUDE_DIR}
    ${OPENGLES_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/apps/camera/common
    ${CMAKE_SOURCE_DIR}/apps/camera/modules
    ${CMAKE_SOURCE_DIR}/apps/camera/renderer
    ${CMAKE_SOURCE_DIR}/samples/utils
    )

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    arguscameracommon
    arguscameramodules
    arguscamerarenderer
    argussampleutils
    )
