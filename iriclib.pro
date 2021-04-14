TEMPLATE = lib
TARGET = iriclib
DEPENDPATH += .
win32 {
	INCLUDEPATH += "E:/iricdev_2013/lib/install/cgnslib-3.2.1/debug/include"
}
unix {
	INCLUDEPATH += /usr/include
}
CONFIG += dll

DEFINES += IRICLIBDLL_LIBRARY
DEFINES += IRICSOLVERLIBDLL_LIBRARY

QT =
DEFINES += UPPERCASE

include( ../paths.pri )

win32 {
	LIBS += -lcgnsdll
}
unix {
	LIBS += -lcgns
	LIBS += -lhdf5
}

#installation settings

unix {
  inst_headers.path = /usr/local/iRIC/include
  inst_headers.files = iriclib.h iriclib_global.h iriclib_f.h iriclib_pointmap.h iriclib_riversurvey.h iriclib_polygon.h iriclib_bstream.h
	INSTALLS += inst_headers

	target.path = /usr/local/iRIC/lib
	INSTALLS += target
}

# Input
HEADERS += error_macros.h \
           filelocker.h \
           fortran_macros.h \
           iriclib.h \
           iriclib_bstream.h \
           iriclib_cgnsfile.h \
           iriclib_cgnsfiles.h \
           iriclib_global.h \
           iriclib_pointmap.h \
           iriclib_polygon.h \
           iriclib_polyline.h \
           iriclib_riversurvey.h \
           iriclib_wrapper_api.h \
           iricsolverlib.h \
           iricsolverlib_api.h \
           iricsolverlib_cell2d.h \
           iricsolverlib_grid2d.h \
           iricsolverlib_point2d.h \
           iricsolverlib_quadcell.h \
           iricsolverlib_rect2d.h \
           iricsolverlib_tricell.h \
           private/filelocker_impl.h \
           private/iriclib_cgnsfile_baseiterativet.h \
           private/iriclib_cgnsfile_baseiterativet_detail.h \
           private/iriclib_cgnsfile_impl.h \
           private/iriclib_cgnsfile_solutionwriter.h \
           private/iriclib_cgnsfile_solutionwriterdividesolutions.h \
           private/iriclib_cgnsfile_solutionwriterstandard.h \
           private/iricsolverlib_cell2d_impl.h \
           private/iricsolverlib_grid2d_impl.h \
           private/iricsolverlib_point2d_detail.h
SOURCES += filelocker.cpp \
           iric_ftoc.c \
           iriclib.cpp \
           iriclib_bstream.cpp \
           iriclib_cgnsfile_base.cpp \
           iriclib_cgnsfile_bc.cpp \
           iriclib_cgnsfile_cc.cpp \
           iriclib_cgnsfile_complex_cc.cpp \
           iriclib_cgnsfile_geo.cpp \
           iriclib_cgnsfile_grid.cpp \
           iriclib_cgnsfile_sol.cpp \
           iriclib_cgnsfiles.cpp \
           iriclib_geo.cpp \
           iriclib_pointmap.cpp \
           iriclib_polygon.cpp \
           iriclib_polyline.cpp \
           iriclib_riversurvey.cpp \
           iriclib_single.c \
           iriclib_wrapper_api.cpp \
           iricsolver_ftoc.c \
           iricsolverlib.cpp \
           iricsolverlib_cell2d.cpp \
           iricsolverlib_grid2d.cpp \
           iricsolverlib_quadcell.cpp \
           iricsolverlib_rect2d.cpp \
           iricsolverlib_tricell.cpp \
           private/iriclib_cgnsfile_solutionwriter.cpp \
           private/iriclib_cgnsfile_solutionwriterdividesolutions.cpp \
           private/iriclib_cgnsfile_solutionwriterstandard.cpp
