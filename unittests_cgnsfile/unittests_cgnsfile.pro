TEMPLATE = app
TARGET = unittests_cgnsfile
CONFIG   += console
CONFIG   += c++11

CONFIG(debug, debug|release) {
	# cgnslib
        LIBS += -L"../cgnslib_dummy/debug"

	# iriclib
	LIBS += -L"../debug"
}
else {
	# cgnslib
        LIBS += -L"../cgnslib_dummy/release"

	# iriclib
	LIBS += -L"../release"
}
LIBS += -lcgnsdll
LIBS += -liriclib

# cgnslib
INCLUDEPATH += "../cgnslib_dummy/"

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
           case_initcc.cpp \
           case_initoption_check.cpp \
           case_initread.cpp \
           case_no_grid_output.cpp \
           case_sol_cell_readwrite.cpp \
           case_sol_readwrite.cpp \
           case_sol_startend.cpp \
           main.cpp
