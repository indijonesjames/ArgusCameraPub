
project(arguscameramodules)

find_package(JPEG)

set(SOURCES
    tasks/Gallery.cpp
    tasks/MultiExposure.cpp
    tasks/MultiSession.cpp
    tasks/StillCapture.cpp
    tasks/VideoRecord.cpp
    Dispatcher.cpp
    EventThread.cpp
    PerfTracker.cpp
    XMLConfig.cpp
    )

include_directories(
    ${ARGUS_INCLUDE_DIR}
    ${EXPAT_INCLUDE_DIR}
    ${JPEG_INCLUDE_DIR}
    ${EGL_INCLUDE_DIR}
    ${OPENGLES_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/apps/camera/common
    ${CMAKE_SOURCE_DIR}/apps/camera/renderer
    ${CMAKE_SOURCE_DIR}/samples/utils
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    ${ARGUS_LIBRARIES}
    ${EXPAT_LIBRARIES}
    ${JPEG_LIBRARIES}
    arguscameracommon
    arguscamerarenderer
    argussampleutils
    )
