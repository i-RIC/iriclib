project(unittests_cgnsfile CXX)

configure_file(case_gridfunc.cgn case_gridfunc.cgn COPYONLY)

configure_file(case_init.cgn case_init.cgn COPYONLY)

configure_file(case_init_hdf5.cgn case_init_hdf5.cgn COPYONLY)

configure_file(case_initread.cgn case_initread.cgn COPYONLY)

configure_file(case_nogrid.cgn case_nogrid.cgn COPYONLY)

configure_file(case_read_adf.cgn case_read_adf.cgn COPYONLY)

configure_file(case_read_hdf5.cgn case_read_hdf5.cgn COPYONLY)

configure_file(case_read_adf_no_sols.cgn case_read_adf_no_sols.cgn COPYONLY)

configure_file(case_read_hdf5_no_sols.cgn case_read_hdf5_no_sols.cgn COPYONLY)

SET(unittests_cgnsfile_SOURCES
fs_copy.h
cases.h
macros.h
case_add_grid_and_result.cpp
case_bc.cpp
case_calccond.cpp
case_check.cpp
case_complex.cpp
case_grid.cpp
case_init.cpp
case_initcc.cpp
case_initoption_check.cpp
case_initread.cpp
case_no_grid_output.cpp
case_sol_cell_readwrite.cpp
case_sol_readwrite.cpp
case_sol_startend.cpp
main.cpp
)

# test executable
add_executable(unittests_cgnsfile ${unittests_cgnsfile_SOURCES})
if (WIN32)
  # copy iriclib.dll to unittests_cgnsfile directory
  add_custom_command(TARGET unittests_cgnsfile POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_BINARY_DIR}/$(Configuration)/iriclib.dll"
    "$<TARGET_FILE_DIR:unittests_cgnsfile>"
    )
endif()

# library dependencies
find_library(CGNS_LIBRARY cgns)
find_package(HDF5 NAMES hdf5)

SET(EXTRA_LIBS ${EXTRA_LIBS} iriclib ${CGNS_LIBRARY} ${HDF5_LIBRARIES})

# link
target_link_libraries(unittests_cgnsfile ${EXTRA_LIBS})

# test
add_test(UNITTESTS_CGNSFILE unittests_cgnsfile)
set_tests_properties(UNITTESTS_CGNSFILE PROPERTIES FAIL_REGULAR_EXPRESSION "[[]NG[]]")
