cmake_minimum_required (VERSION 2.8)

project (iriclib CXX C)
enable_language(Fortran)

# set standard directory locations
include(GNUInstallDirs)

if (NOT DEFINED FORTRAN_NAMING)
  # set(FORTRAN_NAMING "UNKNOWN")
  # set(FORTRAN_NAMING "LOWERCASE")
  set(FORTRAN_NAMING "LOWERCASE_")  # gfortran and ifort
  # set(FORTRAN_NAMING "LOWERCASE__")
  # set(FORTRAN_NAMING "UPPERCASE")
  # set(FORTRAN_NAMING "UPPERCASE_")
  # set(FORTRAN_NAMING "UPPERCASE__")
endif ()

# Disable deprecation warnings for standard C and STL functions in VS2005
# and later
if(MSVC_VERSION EQUAL 1400 OR MSVC_VERSION GREATER 1400)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif() 

add_definitions(-DIRICLIBDLL_LIBRARY)
if(UNIX)
  add_definitions(-std=c++11) # g++ and icpc
endif()

SET(iriclib_SOURCES
error_macros.h
fortran_macros.h
iric_ftoc.c
iriclib.cpp
iriclib.h
iriclib_bstream.cpp
iriclib_bstream.h
iriclib_cgnsfile.h
iriclib_cgnsfile_base.cpp
iriclib_cgnsfile_bc.cpp
iriclib_cgnsfile_cc.cpp
iriclib_cgnsfile_complex_cc.cpp
iriclib_cgnsfile_geo.cpp
iriclib_cgnsfile_grid.cpp
iriclib_cgnsfile_sol.cpp
iriclib_f.h
iriclib_geo.cpp
iriclib_global.h
iriclib_pointmap.cpp
iriclib_pointmap.h
iriclib_polygon.cpp
iriclib_polygon.h
iriclib_riversurvey.cpp
iriclib_riversurvey.h
iriclib_single.c
private/iriclib_cgnsfile_baseiterativet.h
private/iriclib_cgnsfile_baseiterativet_detail.h
private/iriclib_cgnsfile_impl.h
private/iriclib_cgnsfile_solutionwriter.cpp
private/iriclib_cgnsfile_solutionwriter.h
private/iriclib_cgnsfile_solutionwriterdividesolutions.cpp
private/iriclib_cgnsfile_solutionwriterdividesolutions.h
private/iriclib_cgnsfile_solutionwriterstandard.cpp
private/iriclib_cgnsfile_solutionwriterstandard.h
)

# setup include directories
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/private")

add_library(iriclib SHARED ${iriclib_SOURCES})
if (OFF)
  target_compile_features(iriclib PRIVATE cxx_nullptr) # cmake > 2.8 reqd
endif()
set_target_properties(iriclib PROPERTIES DEBUG_POSTFIX "d")
set_target_properties(iriclib PROPERTIES MINSIZEREL_POSTFIX "msr")
set_target_properties(iriclib PROPERTIES RELWITHDEBINFO_POSTFIX "rwdi")


SET(iriclib_Headers
${PROJECT_SOURCE_DIR}/iriclib.h
${PROJECT_SOURCE_DIR}/iriclib_f.h
)

# install
install(TARGETS iriclib DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${iriclib_Headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

enable_testing()
add_subdirectory(unittests_cgnsfile)
