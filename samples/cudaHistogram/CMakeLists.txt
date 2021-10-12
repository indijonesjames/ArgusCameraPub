
cmake_minimum_required (VERSION 2.6)

project(argus_cudahistogram)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

find_package(CUDA)

# Fail silently if CUDA is not found
if(CUDA_FOUND)
    find_package(Argus REQUIRED)

    set(SOURCES
        main.cpp
        histogram.cu
        )

    include_directories(
        ${ARGUS_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/samples/utils
        )

    cuda_add_executable(${PROJECT_NAME} ${SOURCES})

    target_link_libraries(${PROJECT_NAME}
        ${ARGUS_LIBRARIES}
        argussampleutils
        cuda
        )

    install(TARGETS ${PROJECT_NAME} DESTINATION bin)

    include(CPack)
else(CUDA_FOUND)
    message(CUDA toolkit not found, skipping ${PROJECT_NAME})
endif(CUDA_FOUND)
