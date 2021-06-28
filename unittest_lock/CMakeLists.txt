project(unittest_lock CXX)

# unittest_lock target
add_executable(unittest_lock main.cpp)

# unittest_lock link libraries
target_link_libraries(unittest_lock
  PRIVATE
    iriclib
)

# POST_BUILD
if (WIN32)
  # copy iriclib.dll to unittests_cgnsfile directory
  add_custom_command(TARGET unittest_lock POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_BINARY_DIR}/$(Configuration)/iriclib.dll"
    "$<TARGET_FILE_DIR:unittest_lock>"
    )
endif()
