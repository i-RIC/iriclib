TEMPLATE = app
TARGET = unittests_h5
CONFIG   += console
CONFIG   += c++11

CONFIG(debug, debug|release) {
	# cgnslib
	LIBS += -L"D:/iRIC/dev_vc2013_64/iricdev/lib/install/cgnslib-3.2.1-patch1/debug/lib"

	# iriclib
	LIBS += -L"../debug"
}
else {
	# cgnslib
	LIBS += -L"D:/iRIC/dev_vc2013_64/iricdev/lib/install/cgnslib-3.2.1-patch1/release/lib"

	# iriclib
	LIBS += -L"../release"
}
LIBS += -lcgnsdll
LIBS += -liriclib

# cgnslib
INCLUDEPATH += "D:/iRIC/dev_vc2013_64/iricdev/lib/install/cgnslib-3.2.1-patch1/debug/include"

# iriclib
INCLUDEPATH += ".."

# hdf5
INCLUDEPATH += "D:/iRIC/dev_vc2013_64/iricdev/lib/install/hdf5-1.8.14/release/include"

# Input
HEADERS += tests.h fs_copy.h macros.h
SOURCES += test_h5cgnsfile.cpp \
           main.cpp \
           test_h5cgnsbase.cpp
