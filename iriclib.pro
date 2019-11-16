TEMPLATE = lib
TARGET = iriclib
CONFIG += dll
CONFIG += c++11

DEPENDPATH += .
unix {
	INCLUDEPATH += /usr/include
}

DEFINES += IRICLIBDLL_LIBRARY
DEFINES += IRICSOLVERLIBDLL_LIBRARY

QT =
DEFINES += UPPERCASE

include( ../paths.pri )

win32 {
	CONFIG(debug, debug|release) {
                LIBS += -lPocoFoundationd
                LIBS += -lhdf5_D
	}else {
                LIBS += -lPocoFoundation
                LIBS += -lhdf5
        }
}

unix {
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
           fortran_macros.h \
           h5attributecloser.h \
           h5cgnsbase.h \
           h5cgnsbaseiterativedata.h \
           h5cgnsbc.h \
           h5cgnscellflowsolution.h \
           h5cgnsconditiongroup.h \
           h5cgnsfile.h \
           h5cgnsfiles.h \
           h5cgnsfileseparatesolutionutil.h \
           h5cgnsfilesolutionreader.h \
           h5cgnsfilesolutionwriter.h \
           h5cgnsflowsolution.h \
           h5cgnsgeographicdatagroup.h \
           h5cgnsgeographicdatatop.h \
           h5cgnsgridattributes.h \
           h5cgnsgridcomplexconditiongroup.h \
           h5cgnsgridcomplexconditiontop.h \
           h5cgnsgridcoordinates.h \
           h5cgnsifaceflowsolution.h \
           h5cgnsjfaceflowsolution.h \
           h5cgnskfaceflowsolution.h \
           h5cgnsnodeflowsolution.h \
           h5cgnsparticlegroupsolution.h \
           h5cgnsparticlesolution.h \
           h5cgnspolydatasolution.h \
           h5cgnssolutioni.h \
           h5cgnssolverinformation.h \
           h5cgnszone.h \
           h5cgnszonebc.h \
           h5datasetcloser.h \
           h5dataspacecloser.h \
           h5datatypecloser.h \
           h5groupcloser.h \
           h5objectcloser.h \
           h5util.h \
           intarraycontainer.h \
           iriclib.h \
           iriclib_bc.h \
           iriclib_bstream.h \
           iriclib_cc.h \
           iriclib_combine.h \
           iriclib_complex.h \
           iriclib_errorcodes.h \
           iriclib_geo.h \
           iriclib_geoutil.h \
           iriclib_global.h \
           iriclib_grid.h \
           iriclib_gui_coorp.h \
           iriclib_init.h \
           iriclib_not_mul.h \
           iriclib_not_withbaseid.h \
           iriclib_not_withgridid.h \
           iriclib_pointmap.h \
           iriclib_polygon.h \
           iriclib_polyline.h \
           iriclib_riversurvey.h \
           iriclib_sol_cell.h \
           iriclib_sol_gridcoord.h \
           iriclib_sol_iface.h \
           iriclib_sol_jface.h \
           iriclib_sol_kface.h \
           iriclib_sol_node.h \
           iriclib_sol_particle.h \
           iriclib_sol_particlegroup.h \
           iriclib_sol_polydata.h \
           iriclib_solution.h \
           iriclib_wrapper.h \
           iricsolverlib.h \
           iricsolverlib_api.h \
           iricsolverlib_cell2d.h \
           iricsolverlib_grid2d.h \
           iricsolverlib_point2d.h \
           iricsolverlib_quadcell.h \
           iricsolverlib_rect2d.h \
           iricsolverlib_tricell.h \
           realarraycontainer.h \
           vectorutil.h \
           internal/iric_h5cgnsfiles.h \
           internal/iric_logger.h \
           internal/iric_outputerror.h \
           internal/iric_util.h \
           private/h5cgnsbase_impl.h \
           private/h5cgnsbaseiterativedata_impl.h \
           private/h5cgnsbc_impl.h \
           private/h5cgnsconditiongroup_impl.h \
           private/h5cgnsfile_impl.h \
           private/h5cgnsfilesolutionreader_impl.h \
           private/h5cgnsfilesolutionwriter_impl.h \
           private/h5cgnsflowsolution_impl.h \
           private/h5cgnsgeographicdatagroup_impl.h \
           private/h5cgnsgeographicdatatop_impl.h \
           private/h5cgnsgridattributes_impl.h \
           private/h5cgnsgridcomplexconditiongroup_impl.h \
           private/h5cgnsgridcomplexconditiontop_impl.h \
           private/h5cgnsgridcoordinates_impl.h \
           private/h5cgnsparticlegroupsolution_impl.h \
           private/h5cgnsparticlesolution_impl.h \
           private/h5cgnspolydatasolution_impl.h \
           private/h5cgnssolverinformation_impl.h \
           private/h5cgnszone_impl.h \
           private/h5cgnszonebc_impl.h \
           private/iricsolverlib_cell2d_impl.h \
           private/iricsolverlib_grid2d_impl.h \
           private/iricsolverlib_point2d_detail.h \
           private/vectorutil_detail.h \
           public/h5cgnsparticlegroupsolution_groupreader.h \
           public/h5cgnspolydatasolution_groupreader.h
SOURCES += h5attributecloser.cpp \
           h5cgnsbase.cpp \
           h5cgnsbaseiterativedata.cpp \
           h5cgnsbc.cpp \
           h5cgnscellflowsolution.cpp \
           h5cgnsconditiongroup.cpp \
           h5cgnsfile.cpp \
           h5cgnsfiles.cpp \
           h5cgnsfileseparatesolutionutil.cpp \
           h5cgnsfilesolutionreader.cpp \
           h5cgnsfilesolutionwriter.cpp \
           h5cgnsflowsolution.cpp \
           h5cgnsgeographicdatagroup.cpp \
           h5cgnsgeographicdatatop.cpp \
           h5cgnsgridattributes.cpp \
           h5cgnsgridcomplexconditiongroup.cpp \
           h5cgnsgridcomplexconditiontop.cpp \
           h5cgnsgridcoordinates.cpp \
           h5cgnsifaceflowsolution.cpp \
           h5cgnsjfaceflowsolution.cpp \
           h5cgnskfaceflowsolution.cpp \
           h5cgnsnodeflowsolution.cpp \
           h5cgnsparticlegroupsolution.cpp \
           h5cgnsparticlesolution.cpp \
           h5cgnspolydatasolution.cpp \
           h5cgnssolverinformation.cpp \
           h5cgnszone.cpp \
           h5cgnszonebc.cpp \
           h5datasetcloser.cpp \
           h5dataspacecloser.cpp \
           h5datatypecloser.cpp \
           h5groupcloser.cpp \
           h5objectcloser.cpp \
           h5util.cpp \
           intarraycontainer.cpp \
           iriclib_bc.cpp \
           iriclib_bstream.cpp \
           iriclib_cc.cpp \
           iriclib_combine.cpp \
           iriclib_complex.cpp \
           iriclib_ftoc.cpp \
           iriclib_geo.cpp \
           iriclib_geoutil.cpp \
           iriclib_grid.cpp \
           iriclib_gui_coorp.cpp \
           iriclib_init.cpp \
           iriclib_not_mul.cpp \
           iriclib_not_withbaseid.cpp \
           iriclib_not_withgridid.cpp \
           iriclib_pointmap.cpp \
           iriclib_polygon.cpp \
           iriclib_polyline.cpp \
           iriclib_riversurvey.cpp \
           iriclib_sol_cell.cpp \
           iriclib_sol_gridcoord.cpp \
           iriclib_sol_iface.cpp \
           iriclib_sol_jface.cpp \
           iriclib_sol_kface.cpp \
           iriclib_sol_node.cpp \
           iriclib_sol_particle.cpp \
           iriclib_sol_particlegroup.cpp \
           iriclib_sol_polydata.cpp \
           iriclib_solution.cpp \
           iriclib_wrapper.cpp \
           iricsolver_ftoc.c \
           iricsolverlib.cpp \
           iricsolverlib_cell2d.cpp \
           iricsolverlib_grid2d.cpp \
           iricsolverlib_quadcell.cpp \
           iricsolverlib_rect2d.cpp \
           iricsolverlib_tricell.cpp \
           realarraycontainer.cpp \
           internal/iric_h5cgnsfiles.cpp \
           internal/iric_logger.cpp \
           internal/iric_outputerror.cpp \
           internal/iric_util.cpp \
           private/h5cgnsbase_impl.cpp \
           private/h5cgnsbaseiterativedata_impl.cpp \
           private/h5cgnsbc_impl.cpp \
           private/h5cgnsconditiongroup_impl.cpp \
           private/h5cgnsfile_impl.cpp \
           private/h5cgnsfilesolutionreader_impl.cpp \
           private/h5cgnsfilesolutionwriter_impl.cpp \
           private/h5cgnsgeographicdatagroup_impl.cpp \
           private/h5cgnsgeographicdatatop_impl.cpp \
           private/h5cgnsgridattributes_impl.cpp \
           private/h5cgnsgridcomplexconditiongroup_impl.cpp \
           private/h5cgnsgridcomplexconditiontop_impl.cpp \
           private/h5cgnsgridcoordinates_impl.cpp \
           private/h5cgnsparticlegroupsolution_impl.cpp \
           private/h5cgnspolydatasolution_impl.cpp \
           private/h5cgnssolverinformation_impl.cpp \
           private/h5cgnszone_impl.cpp \
           private/h5cgnszonebc_impl.cpp \
           public/h5cgnsparticlegroupsolution_groupreader.cpp \
           public/h5cgnspolydatasolution_groupreader.cpp
