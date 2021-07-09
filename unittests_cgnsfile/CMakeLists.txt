project(unittests_cgnsfile CXX)

# prepare test files TODO process as list, add check for existing file
configure_file(case_gridfunc.cgn          case_gridfunc.cgn          COPYONLY)
configure_file(case_init.cgn              case_init.cgn              COPYONLY)
configure_file(case_init_hdf5.cgn         case_init_hdf5.cgn         COPYONLY)
configure_file(case_initread.cgn          case_initread.cgn          COPYONLY)
configure_file(case_initread_hdf.cgn      case_initread_hdf.cgn      COPYONLY)
configure_file(case_nogrid.cgn            case_nogrid.cgn            COPYONLY)
configure_file(case_nogrid_hdf5.cgn       case_nogrid_hdf5.cgn       COPYONLY)
configure_file(case_read_adf.cgn          case_read_adf.cgn          COPYONLY)
configure_file(case_read_adf_no_sols.cgn  case_read_adf_no_sols.cgn  COPYONLY)
configure_file(case_read_hdf5.cgn         case_read_hdf5.cgn         COPYONLY)
configure_file(case_read_hdf5_no_sols.cgn case_read_hdf5_no_sols.cgn COPYONLY)
configure_file(case_unst_hdf5.cgn         case_unst_hdf5.cgn         COPYONLY)

# unittests_cgnsfile target
add_executable(unittests_cgnsfile main.cpp)

# unittests_cgnsfile sources
target_sources(unittests_cgnsfile
  PRIVATE
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
    case_initoption_check.cpp
    case_initread.cpp
    case_no_grid_output.cpp
    case_sol_cell_readwrite.cpp
    case_sol_readwrite.cpp
)

# unittests_cgnsfile compile definitions
target_compile_definitions(unittests_cgnsfile
  PRIVATE
  $<$<BOOL:MSVC>:_CRT_SECURE_NO_DEPRECATE>
  $<$<BOOL:MSVC>:_SCL_SECURE_NO_WARNINGS>
)

# unittests_cgnsfile link libraries
target_link_libraries(unittests_cgnsfile
  PRIVATE
    iriclib
)

# POST_BUILD
if (WIN32)
  # copy reqd dlls to test1 directory
  add_custom_command(TARGET unittests_cgnsfile POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:iriclib>"            "$<TARGET_FILE_DIR:unittests_cgnsfile>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:Poco::Foundation>"   "$<TARGET_FILE_DIR:unittests_cgnsfile>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:hdf5::hdf5-shared>"  "$<TARGET_FILE_DIR:unittests_cgnsfile>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:zlib-shared>"        "$<TARGET_FILE_DIR:unittests_cgnsfile>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "$<TARGET_FILE:szip-shared>"        "$<TARGET_FILE_DIR:unittests_cgnsfile>"
    )
endif()

# test
add_test(UNITTESTS_CGNSFILE unittests_cgnsfile)
set_tests_properties(UNITTESTS_CGNSFILE PROPERTIES FAIL_REGULAR_EXPRESSION "[[]NG[]]")
