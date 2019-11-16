TEMPLATE = lib
TARGET = cgnsdll
CONFIG += dll
CONFIG += c++11

INCLUDEPATH += ".."

DEFINES += CGNSLIBDLL_LIBRARY

win32 {
	CONFIG(debug, debug|release) {
		LIBS += -L"../debug"
	} else {
		LIBS += -L"../release"
	}
}

LIBS += -liriclib

# Input
HEADERS += cgnslib.h
SOURCES += cgnslib.c
