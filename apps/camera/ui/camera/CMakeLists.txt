
project(argus_camera)

# begin generate source
set(GEN_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/cameraBuilder.glade)
set(GEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cameraBuilder.h)

add_custom_command(
   OUTPUT ${GEN_OUTPUT}
   COMMAND xxd -i < ${GEN_INPUT} > ${GEN_OUTPUT}
   DEPENDS ${GEN_INPUT}
)
#end generate source

set(SOURCES
    Main.cpp
    ${GEN_OUTPUT}
    )

include_directories(
    ${ARGUS_INCLUDE_DIR}
    ${EGL_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/apps/camera/ui/capture
    ${CMAKE_SOURCE_DIR}/apps/camera/ui/common
    ${CMAKE_SOURCE_DIR}/apps/camera/ui/gallery
    ${CMAKE_SOURCE_DIR}/apps/camera/ui/multiExposure
    ${CMAKE_SOURCE_DIR}/apps/camera/ui/multiSession
    ${CMAKE_SOURCE_DIR}/apps/camera/ui/video
    ${CMAKE_SOURCE_DIR}/apps/camera/common
    ${CMAKE_SOURCE_DIR}/apps/camera/modules
    ${CMAKE_SOURCE_DIR}/apps/camera/renderer
    ${CMAKE_SOURCE_DIR}/samples/utils
    ${CMAKE_CURRENT_BINARY_DIR}
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    arguscamerauicapture
    arguscamerauicommon
    arguscamerauigallery
    arguscamerauimultiexposure
    arguscamerauimultisession
    arguscamerauivideo
    arguscameracommon
    arguscameramodules
    arguscamerarenderer
    argussampleutils
    )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
