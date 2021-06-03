##cmake_minimum_required (VERSION 2.8)
##cmake_minimum_required(VERSION 3.15)
cmake_minimum_required(VERSION 3.12)

project (
  iriclib
  VERSION 0.0.0
  LANGUAGES CXX C
)

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

# # cgns (set CMAKE_PREFIX_PATH)
# find_path(CGNS_INC cgns_io.h)
# find_library(CGNS_LIBRARY cgnsdll)
# message(STATUS "CGNS_INC=${CGNS_INC}")
# message(STATUS "CGNS_LIBRARY=${CGNS_LIBRARY}")

find_package(HDF5 1.8 REQUIRED)

find_package(PocoFoundation REQUIRED)

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

SET(iriclib_SOURCES
  error_macros.h
  fortran_macros.h
  h5attributecloser.cpp
  h5attributecloser.h
  h5cgnsbase.cpp
  h5cgnsbase.h
  h5cgnsbaseiterativedata.cpp
  h5cgnsbaseiterativedata.h
  h5cgnsbc.cpp
  h5cgnsbc.h
  h5cgnscellflowsolution.cpp
  h5cgnscellflowsolution.h
  h5cgnsconditiongroup.cpp
  h5cgnsconditiongroup.h
  h5cgnsfile.cpp
  h5cgnsfile.h
  h5cgnsfiles.cpp
  h5cgnsfiles.h
  h5cgnsfileseparatesolutionutil.cpp
  h5cgnsfileseparatesolutionutil.h
  h5cgnsfilesolutionreader.cpp
  h5cgnsfilesolutionreader.h
  h5cgnsfilesolutionwriter.cpp
  h5cgnsfilesolutionwriter.h
  h5cgnsflowsolution.cpp
  h5cgnsflowsolution.h
  h5cgnsgeographicdatagroup.cpp
  h5cgnsgeographicdatagroup.h
  h5cgnsgeographicdatatop.cpp
  h5cgnsgeographicdatatop.h
  h5cgnsgridattributes.cpp
  h5cgnsgridattributes.h
  h5cgnsgridcomplexconditiongroup.cpp
  h5cgnsgridcomplexconditiongroup.h
  h5cgnsgridcomplexconditiontop.cpp
  h5cgnsgridcomplexconditiontop.h
  h5cgnsgridcoordinates.cpp
  h5cgnsgridcoordinates.h
  h5cgnsifaceflowsolution.cpp
  h5cgnsifaceflowsolution.h
  h5cgnsjfaceflowsolution.cpp
  h5cgnsjfaceflowsolution.h
  h5cgnskfaceflowsolution.cpp
  h5cgnskfaceflowsolution.h
  h5cgnsnodeflowsolution.cpp
  h5cgnsnodeflowsolution.h
  h5cgnsparticlegroupsolution.cpp
  h5cgnsparticlegroupsolution.h
  h5cgnsparticlesolution.cpp
  h5cgnsparticlesolution.h
  h5cgnspolydatasolution.cpp
  h5cgnspolydatasolution.h
  h5cgnssolutioni.h
  h5cgnssolverinformation.cpp
  h5cgnssolverinformation.h
  h5cgnszone.cpp
  h5cgnszone.h
  h5cgnszonebc.cpp
  h5cgnszonebc.h
  h5datasetcloser.cpp
  h5datasetcloser.h
  h5dataspacecloser.cpp
  h5dataspacecloser.h
  h5datatypecloser.cpp
  h5datatypecloser.h
  h5groupcloser.cpp
  h5groupcloser.h
  h5objectcloser.cpp
  h5objectcloser.h
  h5propertylistcloser.cpp
  h5propertylistcloser.h
  h5util.cpp
  h5util.h
  intarraycontainer.cpp
  intarraycontainer.h
  internal/iric_h5cgnsfiles.cpp
  internal/iric_h5cgnsfiles.h
  internal/iric_logger.cpp
  internal/iric_logger.h
  internal/iric_outputerror.cpp
  internal/iric_outputerror.h
  internal/iric_util.cpp
  internal/iric_util.h
  iriclib.h
  iriclib_bc.cpp
  iriclib_bc.h
  iriclib_bstream.cpp
  iriclib_bstream.h
  iriclib_cc.cpp
  iriclib_cc.h
  iriclib_combine.cpp
  iriclib_combine.h
  iriclib_complex.cpp
  iriclib_complex.h
  iriclib_errorcodes.h
  iriclib_ftoc.cpp
  iriclib_geo.cpp
  iriclib_geo.h
  iriclib_geoutil.cpp
  iriclib_geoutil.h
  iriclib_global.h
  iriclib_grid.cpp
  iriclib_grid.h
  iriclib_gui_coorp.cpp
  iriclib_gui_coorp.h
  iriclib_init.cpp
  iriclib_init.h
  iriclib_not_mul.cpp
  iriclib_not_mul.h
  iriclib_not_withbaseid.cpp
  iriclib_not_withbaseid.h
  iriclib_not_withgridid.cpp
  iriclib_not_withgridid.h
  iriclib_pointmap.cpp
  iriclib_pointmap.h
  iriclib_polygon.cpp
  iriclib_polygon.h
  iriclib_polyline.cpp
  iriclib_polyline.h
  iriclib_riversurvey.cpp
  iriclib_riversurvey.h
  iriclib_sol_cell.cpp
  iriclib_sol_cell.h
  iriclib_sol_gridcoord.cpp
  iriclib_sol_gridcoord.h
  iriclib_sol_iface.cpp
  iriclib_sol_iface.h
  iriclib_sol_jface.cpp
  iriclib_sol_jface.h
  iriclib_sol_kface.cpp
  iriclib_sol_kface.h
  iriclib_sol_node.cpp
  iriclib_sol_node.h
  iriclib_sol_particle.cpp
  iriclib_sol_particle.h
  iriclib_sol_particlegroup.cpp
  iriclib_sol_particlegroup.h
  iriclib_sol_polydata.cpp
  iriclib_sol_polydata.h
  iriclib_solution.cpp
  iriclib_solution.h
  iriclib_wrapper.cpp
  iriclib_wrapper.h
  iricsolver_ftoc.c
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
  private/h5cgnsbase_impl.cpp
  private/h5cgnsbase_impl.h
  private/h5cgnsbaseiterativedata_impl.cpp
  private/h5cgnsbaseiterativedata_impl.h
  private/h5cgnsbc_impl.cpp
  private/h5cgnsbc_impl.h
  private/h5cgnsconditiongroup_impl.cpp
  private/h5cgnsconditiongroup_impl.h
  private/h5cgnsfile_impl.cpp
  private/h5cgnsfile_impl.h
  private/h5cgnsfilesolutionreader_impl.cpp
  private/h5cgnsfilesolutionreader_impl.h
  private/h5cgnsfilesolutionwriter_impl.cpp
  private/h5cgnsfilesolutionwriter_impl.h
  private/h5cgnsflowsolution_impl.h
  private/h5cgnsgeographicdatagroup_impl.cpp
  private/h5cgnsgeographicdatagroup_impl.h
  private/h5cgnsgeographicdatatop_impl.cpp
  private/h5cgnsgeographicdatatop_impl.h
  private/h5cgnsgridattributes_impl.cpp
  private/h5cgnsgridattributes_impl.h
  private/h5cgnsgridcomplexconditiongroup_impl.cpp
  private/h5cgnsgridcomplexconditiongroup_impl.h
  private/h5cgnsgridcomplexconditiontop_impl.cpp
  private/h5cgnsgridcomplexconditiontop_impl.h
  private/h5cgnsgridcoordinates_impl.cpp
  private/h5cgnsgridcoordinates_impl.h
  private/h5cgnsparticlegroupsolution_impl.cpp
  private/h5cgnsparticlegroupsolution_impl.h
  private/h5cgnsparticlesolution_impl.h
  private/h5cgnspolydatasolution_impl.cpp
  private/h5cgnspolydatasolution_impl.h
  private/h5cgnssolverinformation_impl.cpp
  private/h5cgnssolverinformation_impl.h
  private/h5cgnszone_impl.cpp
  private/h5cgnszone_impl.h
  private/h5cgnszonebc_impl.cpp
  private/h5cgnszonebc_impl.h
  private/iricsolverlib_cell2d_impl.h
  private/iricsolverlib_grid2d_impl.h
  private/iricsolverlib_point2d_detail.h
  private/vectorutil_detail.h
  public/h5cgnsparticlegroupsolution_groupreader.cpp
  public/h5cgnsparticlegroupsolution_groupreader.h
  public/h5cgnspolydatasolution_groupreader.cpp
  public/h5cgnspolydatasolution_groupreader.h
  realarraycontainer.cpp
  realarraycontainer.h
  vectorutil.h
)

# iriclib target
add_library(iriclib SHARED ${iriclib_SOURCES})

# iriclib compile features
target_compile_features(iriclib
  PRIVATE
    cxx_std_11
)

# iriclib compile definitions
target_compile_definitions(iriclib
  PRIVATE
    _CRT_SECURE_NO_DEPRECATE
    _SCL_SECURE_NO_WARNINGS
    IRICLIBDLL_LIBRARY
    IRICSOLVERLIBDLL_LIBRARY
    ${FORTRAN_NAMING}
    ${HDF5_DEFINITIONS}
)

# iriclib include directories
target_include_directories(iriclib
  PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/private>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    # "${CGNS_INC}"
    "${HDF5_INCLUDE_DIRS}"
)

# iriclib link libraries
target_link_libraries(iriclib
  PRIVATE
    ${HDF5_LIBRARIES}
    Poco::Foundation
  # ${CGNS_LIBRARY}
)

SET(iriclib_Headers
  # ${PROJECT_SOURCE_DIR}/filelocker.h
  # ${PROJECT_SOURCE_DIR}/iriclib.h
  # ${PROJECT_SOURCE_DIR}/iriclib_f.h
  # ${PROJECT_SOURCE_DIR}/iriclib_global.h
  # ${PROJECT_SOURCE_DIR}/iriclib_pointmap.h
  # ${PROJECT_SOURCE_DIR}/iriclib_polygon.h
  # ${PROJECT_SOURCE_DIR}/iriclib_polyline.h
  # ${PROJECT_SOURCE_DIR}/iriclib_riversurvey.h
  # ${PROJECT_SOURCE_DIR}/iricsolverlib.h
  # ${PROJECT_SOURCE_DIR}/iricsolverlib_api.h
)

SET(iriclib_private_Headers
  # ${PROJECT_SOURCE_DIR}/private/filelocker_impl.h
)

include(CMakePackageConfigHelpers)
  
configure_package_config_file(iriclibConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/iriclibConfig.cmake
  INSTALL_DESTINATION cmake/iriclib
)

write_basic_package_version_file("iriclibConfigVersion.cmake"
  VERSION ${iriclib}
  COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/iriclibConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/iriclibConfigVersion.cmake
  DESTINATION cmake/iriclib
)

# install
install(TARGETS iriclib
  EXPORT   iriclibTargets
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT iriclibTargets
  FILE iriclibTargets.cmake
  NAMESPACE iriclib::
  DESTINATION cmake/iriclib
)

install(FILES ${iriclib_Headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES ${iriclib_private_Headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/private)
if(MSVC)
  install(FILES ${PROJECT_BINARY_DIR}/Debug/iriclib.pdb
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
    CONFIGURATIONS Debug)
endif()

add_subdirectory(cgnslib_dummy)

include(CTest)

if (BUILD_TESTING)
  add_subdirectory(unittests_cgnsfile)
  # add_subdirectory(unittest_lock)
  # add_subdirectory(unittest_cg_open_modify)
  # add_subdirectory(unittest_cg_open_read)
  # add_subdirectory(unittests_h5)
endif()

get_cmake_property(_variableNames VARIABLES)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
  message(STATUS "${_variableName}=${${_variableName}}")
endforeach()
