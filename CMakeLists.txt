cmake_minimum_required (VERSION 2.8)

project (iriclib CXX C)

# set standard directory locations
include(GNUInstallDirs)

# Fortran (Not currently used)
if (NOT IRICLIB_FORTRAN_TESTING)
  if (NOT CMAKE_Fortran_COMPILER OR CMAKE_Fortran_COMPILER STREQUAL "CMAKE_Fortran_COMPILER-NOTFOUND")
    option (IRICLIB_FORTRAN_TESTING "Build Fortran test" OFF)
  else()
    option (IRICLIB_FORTRAN_TESTING "Build Fortran test" ON)
  endif()
else()
  if (IRICLIB_FORTRAN_TESTING)
    enable_language(Fortran)
  endif()  
endif()

if(NOT DEFINED FORTRAN_NAMING)
  # set(FORTRAN_NAMING "UNKNOWN")
  # set(FORTRAN_NAMING "LOWERCASE")
  set(FORTRAN_NAMING "LOWERCASE_")  # gfortran and ifort
  # set(FORTRAN_NAMING "LOWERCASE__")
  # set(FORTRAN_NAMING "UPPERCASE")
  # set(FORTRAN_NAMING "UPPERCASE_")
  # set(FORTRAN_NAMING "UPPERCASE__")
  if(WIN32)
    set(FORTRAN_NAMING "UPPERCASE")
  endif()
endif()
add_definitions(-D${FORTRAN_NAMING})

# Disable deprecation warnings for standard C and STL functions in VS2005
# and later
if(MSVC_VERSION EQUAL 1400 OR MSVC_VERSION GREATER 1400)
  add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif() 

add_definitions(-DIRICLIBDLL_LIBRARY)
add_definitions(-DIRICSOLVERLIBDLL_LIBRARY)

SET(iriclib_SOURCES
error_macros.h
filelocker.h
filelocker.cpp
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
iriclib_polyline.cpp
iriclib_polyline.h
iriclib_riversurvey.cpp
iriclib_riversurvey.h
iriclib_single.c
iricsolverlib.cpp
iricsolverlib.h
iricsolverlib_api.h
iricsolverlib_cell2d.cpp
iricsolverlib_cell2d.h
iricsolverlib_grid2d.cpp
iricsolverlib_grid2d.h
iricsolverlib_point2d.h
iricsolverlib_quadcell.cpp
iricsolverlib_quadcell.h
iricsolverlib_rect2d.cpp
iricsolverlib_rect2d.h
iricsolverlib_tricell.cpp
iricsolverlib_tricell.h
iricsolver_ftoc.c
private/filelocker_impl.h
private/iriclib_cgnsfile_baseiterativet.h
private/iriclib_cgnsfile_baseiterativet_detail.h
private/iriclib_cgnsfile_impl.h
private/iriclib_cgnsfile_solutionwriter.cpp
private/iriclib_cgnsfile_solutionwriter.h
private/iriclib_cgnsfile_solutionwriterdividesolutions.cpp
private/iriclib_cgnsfile_solutionwriterdividesolutions.h
private/iriclib_cgnsfile_solutionwriterstandard.cpp
private/iriclib_cgnsfile_solutionwriterstandard.h
private/iricsolverlib_cell2d_impl.h
private/iricsolverlib_grid2d_impl.h
private/iricsolverlib_point2d_detail.h
)

# cgns include (set CMAKE_PREFIX_PATH)
find_path(CGNS_INC cgns_io.h)
include_directories("${CGNS_INC}")

# setup include directories
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/private")

add_library(iriclib SHARED ${iriclib_SOURCES})

if(WIN32)
  # cgns library (set CMAKE_PREFIX_PATH)
  find_library(CGNS_LIBRARY cgnsdll)
  SET(EXTRA_LIBS ${EXTRA_LIBS} ${CGNS_LIBRARY})
  
  # link
  target_link_libraries(iriclib ${EXTRA_LIBS})
endif()

if(CMAKE_VERSION VERSION_LESS "3.1")
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # g++
    if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
      set_target_properties(iriclib PROPERTIES COMPILE_OPTIONS -std=c++11)
    elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.4)
      message(FATAL_ERROR "g++ version must be at least 4.7")
    endif()
  endif()
  if (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    # icpc
    set_target_properties(iriclib PROPERTIES COMPILE_OPTIONS -std=c++11)
  endif()
elseif(CMAKE_VERSION VERSION_LESS "3.6" AND CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    # icpc compile_features not implemented until 3.6
    set_target_properties(iriclib PROPERTIES COMPILE_OPTIONS -std=c++11)
else()
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # g++
    if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.7)
      target_compile_features(iriclib PRIVATE cxx_nullptr) # cmake >= 3.1 reqd
    else()
      message(FATAL_ERROR "g++ version must be at least 4.7")
    endif()
  else()
    target_compile_features(iriclib PRIVATE cxx_nullptr) # cmake >= 3.1 reqd
  endif()
endif()
# set_target_properties(iriclib PROPERTIES DEBUG_POSTFIX "d")
# set_target_properties(iriclib PROPERTIES MINSIZEREL_POSTFIX "msr")
# set_target_properties(iriclib PROPERTIES RELWITHDEBINFO_POSTFIX "rwdi")


SET(iriclib_Headers
${PROJECT_SOURCE_DIR}/filelocker.h
${PROJECT_SOURCE_DIR}/iriclib.h
${PROJECT_SOURCE_DIR}/iriclib_f.h
${PROJECT_SOURCE_DIR}/iriclib_global.h
${PROJECT_SOURCE_DIR}/iriclib_pointmap.h
${PROJECT_SOURCE_DIR}/iriclib_polygon.h
${PROJECT_SOURCE_DIR}/iriclib_polyline.h
${PROJECT_SOURCE_DIR}/iriclib_riversurvey.h
${PROJECT_SOURCE_DIR}/iricsolverlib.h
${PROJECT_SOURCE_DIR}/iricsolverlib_api.h
)

SET(iriclib_private_Headers
${PROJECT_SOURCE_DIR}/private/filelocker_impl.h
)

# install
install(TARGETS iriclib DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${iriclib_Headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${iriclib_private_Headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/private)
if(MSVC)
  install(FILES ${PROJECT_BINARY_DIR}/Debug/iriclib.pdb
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    CONFIGURATIONS Debug)
endif()

include(CTest)

if (BUILD_TESTING)
  add_subdirectory(unittests_cgnsfile)
  add_subdirectory(unittest_lock)
  add_subdirectory(unittest_cg_open_modify)
  add_subdirectory(unittest_cg_open_read)
endif()
