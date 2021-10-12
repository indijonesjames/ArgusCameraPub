
project(arguscameracommon)

set(SOURCES
    ConditionVariable.cpp
    Mutex.cpp
    Util.cpp
    VideoPipeline.cpp
    )

include_directories(
    ${CMAKE_SOURCE_DIR}/apps/camera/common
    ${CMAKE_SOURCE_DIR}/apps/camera/renderer
    ${CMAKE_SOURCE_DIR}/samples/utils
    ${EGL_INCLUDE_DIR}
    ${OPENGLES_INCLUDE_DIR}
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

# Begin of gstreamer
find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
include_directories(${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})

pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB_LIBRARIES})

add_definitions(-DGST_SUPPORTED)
# End of gstreamer

target_link_libraries(${PROJECT_NAME}
    ${ARGUS_LIBRARIES}
    arguscamerarenderer
    argussampleutils
    )
