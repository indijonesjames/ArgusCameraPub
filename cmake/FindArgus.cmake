
# - Try to find Argus
# Once done this will define
#  ARGUS_FOUND - System has Argus
#  ARGUS_INCLUDE_DIRS - The Argus include directories
#  ARGUS_LIBRARIES - The libraries needed to use Argus
#  ARGUS_DEFINITIONS - Compiler switches required for using Argus

find_package(PkgConfig)

find_path(ARGUS_INCLUDE_DIR Argus/Argus.h
          HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

find_library(ARGUS_LIBRARY NAMES nvargus
             HINTS /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/tegra)
find_library(ARGUS_LIBRARY_MULTIPROCESS NAMES nvargus_socketclient
             HINTS /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}/tegra)

if (DISABLE_MULTIPROCESS)
set(ARGUS_LIBRARIES ${ARGUS_LIBRARY})
else()
set(ARGUS_LIBRARIES ${ARGUS_LIBRARY_MULTIPROCESS})
endif()

set(ARGUS_INCLUDE_DIRS ${ARGUS_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set ARGUS_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(Argus DEFAULT_MSG
                                  ARGUS_LIBRARY ARGUS_INCLUDE_DIR)

mark_as_advanced(ARGUS_INCLUDE_DIR ARGUS_LIBRARY)
