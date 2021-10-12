
cmake_minimum_required (VERSION 2.6)

project(argus_userautoexposure)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

find_package(Argus REQUIRED)
find_package(OpenGLES REQUIRED)
find_package(EGL REQUIRED)

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

target_link_libraries(${PROJECT_NAME}
    ${ARGUS_LIBRARIES}
    ${OPENGLES_LIBRARIES}
    argussampleutils
    )

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

include(CPack)
