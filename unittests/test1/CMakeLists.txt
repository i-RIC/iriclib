project(test1 Fortran)

configure_file(data/test_input_hdf5.cgn test_input_hdf5.cgn COPYONLY)

add_executable(test1
  test1.f90
 )

target_link_libraries(test1
  PRIVATE
    iriclib
)

# POST_BUILD
if (WIN32)
  # copy reqd dlls to test1 directory
  add_custom_command(TARGET test1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:iriclib>"            "$<TARGET_FILE_DIR:test1>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:Poco::Foundation>"   "$<TARGET_FILE_DIR:test1>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:hdf5::hdf5-shared>"  "$<TARGET_FILE_DIR:test1>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:zlib-shared>"        "$<TARGET_FILE_DIR:test1>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:szip-shared>"        "$<TARGET_FILE_DIR:test1>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$ENV{IFORT_COMPILER21}\\redist\\intel64_win\\compiler\\libifcoremd.dll" "$<TARGET_FILE_DIR:test1>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$ENV{IFORT_COMPILER21}\\redist\\intel64_win\\compiler\\libmmd.dll"      "$<TARGET_FILE_DIR:test1>"
    )
endif()

# test
add_test(Fortran.test1 test1)
set_tests_properties(Fortran.test1 PROPERTIES FAIL_REGULAR_EXPRESSION "Error detected in HDF5")
