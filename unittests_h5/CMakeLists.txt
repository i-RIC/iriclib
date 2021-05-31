project(unittests_h5 CXX)

# prepare test files
# configure_file(case_gridfunc.cgn case_gridfunc.cgn COPYONLY)
# configure_file(case_init.cgn case_init.cgn COPYONLY)
# configure_file(case_init_hdf5.cgn case_init_hdf5.cgn COPYONLY)
# configure_file(case_initread.cgn case_initread.cgn COPYONLY)
# configure_file(case_nogrid.cgn case_nogrid.cgn COPYONLY)
# configure_file(case_read_adf.cgn case_read_adf.cgn COPYONLY)
# configure_file(case_read_hdf5.cgn case_read_hdf5.cgn COPYONLY)
# configure_file(case_read_adf_no_sols.cgn case_read_adf_no_sols.cgn COPYONLY)
# configure_file(case_read_hdf5_no_sols.cgn case_read_hdf5_no_sols.cgn COPYONLY)

# extra dependencies
# find_package(HDF5 1.8 REQUIRED)

# unittests_h5 target
add_executable(unittests_h5 main.cpp)

# unittests_h5 sources
target_sources(unittests_h5
  PRIVATE
    fs_copy.h
    macros.h
    test_h5cgnsbase.cpp
    test_h5cgnsfile.cpp
    tests.h
)

# unittests_h5 compile definitions
target_compile_definitions(unittests_h5
  PRIVATE
    _CRT_SECURE_NO_DEPRECATE
    _SCL_SECURE_NO_WARNINGS
)

# iriclib include directories
target_include_directories(unittests_h5
  PUBLIC
    # "${CGNS_INC}"
  PRIVATE
    # "${HDF5_INCLUDE_DIRS}"
    "${CGNS_INC}"
)


# unittests_h5 link libraries
target_link_libraries(unittests_h5
  PRIVATE
    iriclib
    ${CGNS_LIBRARY}
    # ${HDF5_LIBRARIES}
)

# POST_BUILD
if (WIN32)
  # copy iriclib.dll to unittests_h5 directory
  add_custom_command(TARGET unittests_h5 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_BINARY_DIR}/$(Configuration)/iriclib.dll"
    "$<TARGET_FILE_DIR:unittests_h5>"
    )
endif()

# test
add_test(unittests_h5 unittests_h5)
# set_tests_properties(unittests_h5 PROPERTIES FAIL_REGULAR_EXPRESSION "[[]NG[]]")
