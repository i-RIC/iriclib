// APIs used from Python wrapper is defined

#ifndef IRICLIB_WRAPPER_H
#define IRICLIB_WRAPPER_H

#include "iriclib_global.h"
#include "intarraycontainer.h"
#include "realarraycontainer.h"
// from iriclib_bc.h
int IRICLIBDLL cg_iRIC_Read_BC_Indices_WithGridId_Mul(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_WithGridId_Mul(int fid, int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_WithGridId_Mul(int fid, int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices_WithGridId_Mul(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices2_WithGridId_Mul(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Functional_WithGridId_Mul(int fid, int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_WithGridId_Mul(int fid, int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);

// from iriclib_cc.h
int IRICLIBDLL cg_iRIC_Read_Functional_Mul(int fid, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Functional_Mul(int fid, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& v_arr);

// from iriclib_complex.h
int IRICLIBDLL cg_iRIC_Read_Complex_Functional_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node_WithGridId_Mul(int fid, int gid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell_WithGridId_Mul(int fid, int gid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_Functional_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node_WithGridId_Mul(int fid, int gid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell_WithGridId_Mul(int fid, int gid, const char* groupname, IntArrayContainer& v_arr);

// from iriclib_geo.h
int IRICLIBDLL iRIC_Geo_Polygon_Read_Points(int id, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL iRIC_Geo_Polygon_Read_HolePoints(int id, int holeid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL iRIC_Geo_RiverSurvey_Read_Altitudes(int id, int pointid, RealArrayContainer& position_arr, RealArrayContainer& height_arr, IntArrayContainer& active_arr);

// from iriclib_geoutil.h

// from iriclib_grid.h
int IRICLIBDLL cg_iRIC_Read_Grid2d_Coords_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_GetGridCoord3d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_GetTriangleElements_WithGridId_Mul(int fid, int gid, IntArrayContainer& id_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId_Mul(int fid, int gid, const char* name, const char* dimname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId_Mul(int fid, int gid, const char* name, const char* dimname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& time_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId_Mul(int fid, int gid, const char* name, int dimid, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId_Mul(int fid, int gid, const char* name, int dimid, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId_Mul(int fid, int gid, const char* name, int dimid, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId_Mul(int fid, int gid, const char* name, int dimid, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_WriteGridCoord1d_WithGridId_Mul(int fid, int isize, RealArrayContainer& x_arr, int* gid);
int IRICLIBDLL cg_iRIC_WriteGridCoord2d_WithGridId_Mul(int fid, int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, int* gid);
int IRICLIBDLL cg_iRIC_WriteGridCoord3d_WithGridId_Mul(int fid, int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr, int* gid);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);

// from iriclib_not_mul.h
int IRICLIBDLL cg_iRIC_Read_BC_Indices_WithGridId(int gid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_WithGridId(int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices_WithGridId(int gid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices2_WithGridId(int gid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Functional_WithGridId(int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Functional(const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Functional(const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional_WithBaseId(int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node_WithGridId(int gid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell_WithGridId(int gid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_Functional_WithBaseId(int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node_WithGridId(int gid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell_WithGridId(int gid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid2d_Coords_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_GetGridCoord3d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_GetTriangleElements_WithGridId(int gid, IntArrayContainer& id_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId(int gid, const char* name, const char* dimname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId(int gid, const char* name, const char* dimname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime_WithGridId(int gid, const char* name, RealArrayContainer& time_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId(int gid, const char* name, int dimid, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId(int gid, const char* name, int dimid, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId(int gid, const char* name, int dimid, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId(int gid, const char* name, int dimid, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_WriteGridCoord1d_WithGridId(int isize, RealArrayContainer& x_arr, int* gid);
int IRICLIBDLL cg_iRIC_WriteGridCoord2d_WithGridId(int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, int* gid);
int IRICLIBDLL cg_iRIC_WriteGridCoord3d_WithGridId(int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr, int* gid);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Indices(const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices(const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices2(const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node(const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell(const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node(const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell(const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid2d_Coords(RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_GetGridCoord3d(RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_GetTriangleElements(IntArrayContainer& id_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer(const char* name, const char* dimname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real(const char* name, const char* dimname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime(const char* name, RealArrayContainer& time_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node(const char* name, int dimid, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node(const char* name, int dimid, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell(const char* name, int dimid, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell(const char* name, int dimid, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_WriteGridCoord1d(int isize, RealArrayContainer& x_arr);
int IRICLIBDLL cg_iRIC_WriteGridCoord2d(int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_WriteGridCoord3d(int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer(int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real(int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord2d(int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord3d(int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d(RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d(RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer(int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real(int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer(int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real(int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Integer(int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Real(int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Integer(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Real(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Integer(int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Real(int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Integer(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Real(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos2d(int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos3d(int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Real(int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Integer(int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d(RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d(RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real(const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer(const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos2d(int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos3d(int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Real(int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Integer(int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Pos2d(int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Type(int step, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Real(int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Integer(int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon(int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline(int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord2d_WithGridId(int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord3d_WithGridId(int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId(int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId(int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId(int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId(int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Type_WithGridId(int gid, int step, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Real_WithGridId(int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);

// from iriclib_not_withbaseid.h
int IRICLIBDLL cg_iRIC_Read_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);

// from iriclib_not_withgridid.h
int IRICLIBDLL cg_iRIC_Read_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices2_Mul(int fid, const char* type, int num, IntArrayContainer& idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell_Mul(int fid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell_Mul(int fid, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid2d_Coords_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_GetGridCoord3d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_GetTriangleElements_Mul(int fid, IntArrayContainer& id_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(int fid, const char* name, const char* dimname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(int fid, const char* name, const char* dimname, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime_Mul(int fid, const char* name, RealArrayContainer& time_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(int fid, const char* name, int dimid, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node_Mul(int fid, const char* name, int dimid, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(int fid, const char* name, int dimid, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(int fid, const char* name, int dimid, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_WriteGridCoord1d_Mul(int fid, int isize, RealArrayContainer& x_arr);
int IRICLIBDLL cg_iRIC_WriteGridCoord2d_Mul(int fid, int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_WriteGridCoord3d_Mul(int fid, int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord2d_Mul(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord3d_Mul(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos2d_Mul(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos3d_Mul(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos2d_Mul(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos3d_Mul(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Real_Mul(int fid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Integer_Mul(int fid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Pos2d_Mul(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Type_Mul(int fid, int step, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Real_Mul(int fid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Integer_Mul(int fid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon_Mul(int fid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline_Mul(int fid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);

// from iriclib_sol_cell.h
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);

// from iriclib_sol_gridcoord.h
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord2d_WithGridId_Mul(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_GridCoord3d_WithGridId_Mul(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);

// from iriclib_sol_iface.h
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);

// from iriclib_sol_jface.h
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);

// from iriclib_sol_kface.h
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);

// from iriclib_sol_node.h
int IRICLIBDLL cg_iRIC_Read_Sol_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);

// from iriclib_sol_particle.h
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId_Mul(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId_Mul(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr);

// from iriclib_sol_particlegroup.h
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);

// from iriclib_sol_polydata.h
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Type_WithGridId_Mul(int fid, int gid, int step, const char* groupname, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Real_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Integer_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId_Mul(int fid, int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId_Mul(int fid, int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr);

// from iriclib_solution.h

#endif // IRICLIB_WRAPPER_H
