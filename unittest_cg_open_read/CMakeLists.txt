project(unittest_cg_open_read CXX)

# test executable
add_executable(unittest_cg_open_read main.cpp)

# unittests_cgnsfile link libraries
target_link_libraries(unittest_cg_open_read
  PRIVATE
    iriclib
)

# POST_BUILD
if (WIN32)
  # copy iriclib.dll to unittests_cgnsfile directory
  add_custom_command(TARGET unittest_cg_open_read POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_BINARY_DIR}/$(Configuration)/iriclib.dll"
    "$<TARGET_FILE_DIR:unittest_cg_open_read>"
    )
endif()
