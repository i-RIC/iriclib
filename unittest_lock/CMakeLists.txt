project(unittest_lock CXX)

SET(unittest_lock_SOURCES
main.cpp
)

# test executable
add_executable(unittest_lock ${unittest_lock_SOURCES})
if (WIN32)
  # copy iriclib.dll to unittests_cgnsfile directory
  add_custom_command(TARGET unittest_lock POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_BINARY_DIR}/$(Configuration)/iriclib.dll"
    "$<TARGET_FILE_DIR:unittest_lock>"
    )
endif()

# library dependencies
find_library(CGNS_LIBRARY cgns)
find_package(HDF5 NAMES hdf5)

SET(EXTRA_LIBS ${EXTRA_LIBS} iriclib ${CGNS_LIBRARY} ${HDF5_LIBRARIES})

# link
target_link_libraries(unittest_lock ${EXTRA_LIBS})
