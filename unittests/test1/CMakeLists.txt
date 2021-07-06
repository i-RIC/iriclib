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
  # copy iriclib.dll to unittests_cgnsfile directory
  add_custom_command(TARGET test1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "$<TARGET_FILE:iriclib>"
    "$<TARGET_FILE_DIR:test1>"
    )
endif()

