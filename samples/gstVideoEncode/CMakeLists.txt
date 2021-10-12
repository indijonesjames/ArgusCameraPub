
cmake_minimum_required (VERSION 2.6)

project(argus_gstvideoencode)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

find_package(Argus REQUIRED)

set(SOURCES
    main.cpp
    )

include_directories(
    ${ARGUS_INCLUDE_DIR}
    ${EGL_INCLUDE_DIR}
    ${OPENGLES_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/samples/utils
    )

add_executable(${PROJECT_NAME} ${SOURCES})

# Begin of gstreamer
find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)
include_directories(${GSTREAMER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})

pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${GLIB_LIBRARIES})
# End of gstreamer

target_link_libraries(${PROJECT_NAME}
    ${ARGUS_LIBRARIES}
    argussampleutils
    )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

include(CPack)
