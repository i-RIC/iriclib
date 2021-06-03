project(cgnslib_dummy C)

# unittests_h5 target
add_library(cgnslib_dummy SHARED cgnslib.c)
set_target_properties(cgnslib_dummy PROPERTIES OUTPUT_NAME cgnsdll)

# unittests_h5 sources
target_sources(cgnslib_dummy
  PRIVATE
    cgnslib.h
)

# iriclib compile features
target_compile_features(cgnslib_dummy
  PRIVATE
    cxx_std_11
)

# unittests_h5 compile definitions
target_compile_definitions(cgnslib_dummy
  PRIVATE
    CGNSLIBDLL_LIBRARY
)

# iriclib include directories
target_include_directories(cgnslib_dummy
  PUBLIC
    cgnslib.h
)

# unittests_h5 link libraries
target_link_libraries(cgnslib_dummy
  PRIVATE
    iriclib
)

SET(cgnslib_dummy_Headers
  cgnslib.h
)

# install
install(TARGETS cgnslib_dummy
  LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${cgnslib_dummy_Headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

