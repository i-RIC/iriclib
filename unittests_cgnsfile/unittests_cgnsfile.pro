TEMPLATE = app
TARGET = unittests_cgnsfile
CONFIG   += console
CONFIG   += c++11

CONFIG(debug, debug|release) {
	# iriclib
	LIBS += -L"../debug"
}
else {
	# iriclib
	LIBS += -L"../release"
}
LIBS += -liriclib

# iriclib
INCLUDEPATH += ".."

# Input
HEADERS += cases.h fs_copy.h macros.h
SOURCES += case_add_grid_and_result.cpp \
           case_bc.cpp \
           case_calccond.cpp \
           case_check.cpp \
           case_complex.cpp \
           case_grid.cpp \
           case_init.cpp \
           case_initoption_check.cpp \
           case_initread.cpp \
           case_no_grid_output.cpp \
           case_sol_cell_readwrite.cpp \
           case_sol_readwrite.cpp \
           main.cpp
