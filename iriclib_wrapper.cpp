#include "iriclib.h"
#include "iriclib_wrapper.h"

#include "intarraycontainer.h"
#include "realarraycontainer.h"

// from iriclib_bc.h
int cg_iRIC_Read_BC_Indices_WithGridId_Mul(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Read_BC_Indices_WithGridId_Mul(fid, gid, type, num, idx_arr.pointer());
}

int cg_iRIC_Read_BC_Functional_WithGridId_Mul(int fid, int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_BC_Functional_WithGridId_Mul(fid, gid, type, num, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_BC_FunctionalWithName_WithGridId_Mul(int fid, int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_BC_FunctionalWithName_WithGridId_Mul(fid, gid, type, num, name, paramname, v_arr.pointer());
}

int cg_iRIC_Write_BC_Indices_WithGridId_Mul(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Write_BC_Indices2_WithGridId_Mul(fid, gid, type, num, idx_arr.size(), idx_arr.pointer());
}

int cg_iRIC_Write_BC_Indices2_WithGridId_Mul(int fid, int gid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Write_BC_Indices2_WithGridId_Mul(fid, gid, type, num, idx_arr.size(), idx_arr.pointer());
}

int cg_iRIC_Write_BC_Functional_WithGridId_Mul(int fid, int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_BC_Functional_WithGridId_Mul(fid, gid, type, num, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_BC_FunctionalWithName_WithGridId_Mul(int fid, int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_BC_FunctionalWithName_WithGridId_Mul(fid, gid, type, num, name, paramname, v_arr.size(), v_arr.pointer());
}


// from iriclib_cc.h
int cg_iRIC_Read_Functional_Mul(int fid, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Functional_Mul(fid, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_FunctionalWithName_Mul(fid, name, paramname, v_arr.pointer());
}

int cg_iRIC_Write_Functional_Mul(int fid, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Functional_Mul(fid, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_FunctionalWithName_Mul(fid, name, paramname, v_arr.size(), v_arr.pointer());
}


// from iriclib_complex.h
int cg_iRIC_Read_Complex_Functional_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Complex_Functional_WithBaseId_Mul(fid, bid, groupname, num, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId_Mul(fid, bid, groupname, num, name, paramname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Complex_Node_WithGridId_Mul(int fid, int gid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Complex_Node_WithGridId_Mul(fid, gid, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Complex_Cell_WithGridId_Mul(int fid, int gid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Complex_Cell_WithGridId_Mul(fid, gid, groupname, v_arr.pointer());
}

int cg_iRIC_Write_Complex_Functional_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Complex_Functional_WithBaseId_Mul(fid, bid, groupname, num, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId_Mul(fid, bid, groupname, num, name, paramname, v_arr.size(), v_arr.pointer());
}

int cg_iRIC_Write_Grid_Complex_Node_WithGridId_Mul(int fid, int gid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Complex_Node_WithGridId_Mul(fid, gid, groupname, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Complex_Cell_WithGridId_Mul(int fid, int gid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Complex_Cell_WithGridId_Mul(fid, gid, groupname, v_arr.pointer());
}


// from iriclib_geo.h
int iRIC_Geo_Polygon_Read_Points(int id, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return iRIC_Geo_Polygon_Read_Points(id, x_arr.pointer(), y_arr.pointer());
}

int iRIC_Geo_Polygon_Read_HolePoints(int id, int holeid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return iRIC_Geo_Polygon_Read_HolePoints(id, holeid, x_arr.pointer(), y_arr.pointer());
}

int iRIC_Geo_RiverSurvey_Read_Altitudes(int id, int pointid, RealArrayContainer& position_arr, RealArrayContainer& height_arr, IntArrayContainer& active_arr)
{
	return iRIC_Geo_RiverSurvey_Read_Altitudes(id, pointid, position_arr.pointer(), height_arr.pointer(), active_arr.pointer());
}


// from iriclib_geoutil.h

// from iriclib_grid.h
int cg_iRIC_Read_Grid2d_Coords_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Grid2d_Coords_WithGridId_Mul(fid, gid, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Grid3d_Coords_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Grid3d_Coords_WithGridId_Mul(fid, gid, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_GetTriangleElements_WithGridId_Mul(int fid, int gid, IntArrayContainer& id_arr)
{
	return cg_iRIC_GetTriangleElements_WithGridId_Mul(fid, gid, id_arr.pointer());
}

int cg_iRIC_Read_Grid_Real_Node_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Real_Node_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Integer_Node_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Integer_Node_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Real_Cell_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Real_Cell_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Integer_Cell_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Integer_Cell_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId_Mul(int fid, int gid, const char* name, const char* dimname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId_Mul(fid, gid, name, dimname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId_Mul(int fid, int gid, const char* name, const char* dimname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId_Mul(fid, gid, name, dimname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalTime_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& time_arr)
{
	return cg_iRIC_Read_Grid_FunctionalTime_WithGridId_Mul(fid, gid, name, time_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId_Mul(int fid, int gid, const char* name, int dimid, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId_Mul(fid, gid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId_Mul(int fid, int gid, const char* name, int dimid, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId_Mul(fid, gid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId_Mul(int fid, int gid, const char* name, int dimid, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId_Mul(fid, gid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId_Mul(int fid, int gid, const char* name, int dimid, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId_Mul(fid, gid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Write_Grid1d_Coords_WithGridId_Mul(int fid, int isize, RealArrayContainer& x_arr, int* gid)
{
	return cg_iRIC_Write_Grid1d_Coords_WithGridId_Mul(fid, isize, x_arr.pointer(), gid);
}

int cg_iRIC_Write_Grid2d_Coords_WithGridId_Mul(int fid, int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, int* gid)
{
	return cg_iRIC_Write_Grid2d_Coords_WithGridId_Mul(fid, isize, jsize, x_arr.pointer(), y_arr.pointer(), gid);
}

int cg_iRIC_Write_Grid3d_Coords_WithGridId_Mul(int fid, int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr, int* gid)
{
	return cg_iRIC_Write_Grid3d_Coords_WithGridId_Mul(fid, isize, jsize, ksize, x_arr.pointer(), y_arr.pointer(), z_arr.pointer(), gid);
}

int cg_iRIC_Write_Grid_Real_Node_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Real_Node_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Integer_Node_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Integer_Node_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Real_Cell_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Real_Cell_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Integer_Cell_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Integer_Cell_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}


// from iriclib_not_mul.h
int cg_iRIC_Read_BC_Indices_WithGridId(int gid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Read_BC_Indices_WithGridId(gid, type, num, idx_arr.pointer());
}

int cg_iRIC_Read_BC_Functional_WithGridId(int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_BC_Functional_WithGridId(gid, type, num, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_BC_FunctionalWithName_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_BC_FunctionalWithName_WithGridId(gid, type, num, name, paramname, v_arr.pointer());
}

int cg_iRIC_Write_BC_Indices_WithGridId(int gid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Write_BC_Indices2_WithGridId(gid, type, num, idx_arr.size(), idx_arr.pointer());
}

int cg_iRIC_Write_BC_Indices2_WithGridId(int gid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Write_BC_Indices2_WithGridId(gid, type, num, idx_arr.size(), idx_arr.pointer());
}

int cg_iRIC_Write_BC_Functional_WithGridId(int gid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_BC_Functional_WithGridId(gid, type, num, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_BC_FunctionalWithName_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_BC_FunctionalWithName_WithGridId(gid, type, num, name, paramname, v_arr.size(), v_arr.pointer());
}

int cg_iRIC_Read_Functional(const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Functional(name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_FunctionalWithName(name, paramname, v_arr.pointer());
}

int cg_iRIC_Write_Functional(const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Functional(name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_FunctionalWithName(const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_FunctionalWithName(name, paramname, v_arr.size(), v_arr.pointer());
}

int cg_iRIC_Read_Complex_Functional_WithBaseId(int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Complex_Functional_WithBaseId(bid, groupname, num, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId(bid, groupname, num, name, paramname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Complex_Node_WithGridId(int gid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Complex_Node_WithGridId(gid, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Complex_Cell_WithGridId(int gid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Complex_Cell_WithGridId(gid, groupname, v_arr.pointer());
}

int cg_iRIC_Write_Complex_Functional_WithBaseId(int bid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Complex_Functional_WithBaseId(bid, groupname, num, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId(bid, groupname, num, name, paramname, v_arr.size(), v_arr.pointer());
}

int cg_iRIC_Write_Grid_Complex_Node_WithGridId(int gid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Complex_Node_WithGridId(gid, groupname, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Complex_Cell_WithGridId(int gid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Complex_Cell_WithGridId(gid, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Grid2d_Coords_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Grid2d_Coords_WithGridId(gid, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Grid3d_Coords_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Grid3d_Coords_WithGridId(gid, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_GetTriangleElements_WithGridId(int gid, IntArrayContainer& id_arr)
{
	return cg_iRIC_GetTriangleElements_WithGridId(gid, id_arr.pointer());
}

int cg_iRIC_Read_Grid_Real_Node_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Real_Node_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Integer_Node_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Integer_Node_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Real_Cell_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Real_Cell_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Integer_Cell_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Integer_Cell_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId(int gid, const char* name, const char* dimname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId(gid, name, dimname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId(int gid, const char* name, const char* dimname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId(gid, name, dimname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalTime_WithGridId(int gid, const char* name, RealArrayContainer& time_arr)
{
	return cg_iRIC_Read_Grid_FunctionalTime_WithGridId(gid, name, time_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId(int gid, const char* name, int dimid, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId(gid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId(int gid, const char* name, int dimid, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId(gid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId(int gid, const char* name, int dimid, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId(gid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId(int gid, const char* name, int dimid, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId(gid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Write_Grid1d_Coords_WithGridId(int isize, RealArrayContainer& x_arr, int* gid)
{
	return cg_iRIC_Write_Grid1d_Coords_WithGridId(isize, x_arr.pointer(), gid);
}

int cg_iRIC_Write_Grid2d_Coords_WithGridId(int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, int* gid)
{
	return cg_iRIC_Write_Grid2d_Coords_WithGridId(isize, jsize, x_arr.pointer(), y_arr.pointer(), gid);
}

int cg_iRIC_Write_Grid3d_Coords_WithGridId(int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr, int* gid)
{
	return cg_iRIC_Write_Grid3d_Coords_WithGridId(isize, jsize, ksize, x_arr.pointer(), y_arr.pointer(), z_arr.pointer(), gid);
}

int cg_iRIC_Write_Grid_Real_Node_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Real_Node_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Integer_Node_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Integer_Node_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Real_Cell_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Real_Cell_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Integer_Cell_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Integer_Cell_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Complex_Functional(groupname, num, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Complex_FunctionalWithName(groupname, num, name, paramname, v_arr.pointer());
}

int cg_iRIC_Write_Complex_Functional(const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Complex_Functional(groupname, num, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Complex_FunctionalWithName(groupname, num, name, paramname, v_arr.size(), v_arr.pointer());
}

int cg_iRIC_Read_BC_Indices(const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Read_BC_Indices(type, num, idx_arr.pointer());
}

int cg_iRIC_Read_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_BC_Functional(type, num, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_BC_FunctionalWithName(type, num, name, paramname, v_arr.pointer());
}

int cg_iRIC_Write_BC_Indices(const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Write_BC_Indices2(type, num, idx_arr.size(), idx_arr.pointer());
}

int cg_iRIC_Write_BC_Indices2(const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Write_BC_Indices2(type, num, idx_arr.size(), idx_arr.pointer());
}

int cg_iRIC_Write_BC_Functional(const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_BC_Functional(type, num, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_BC_FunctionalWithName(type, num, name, paramname, v_arr.size(), v_arr.pointer());
}

int cg_iRIC_Read_Grid_Complex_Node(const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Complex_Node(groupname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Complex_Cell(const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Complex_Cell(groupname, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Complex_Node(const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Complex_Node(groupname, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Complex_Cell(const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Complex_Cell(groupname, v_arr.pointer());
}

int cg_iRIC_Read_Grid2d_Coords(RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Grid2d_Coords(x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Grid3d_Coords(RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Grid3d_Coords(x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_GetTriangleElements(IntArrayContainer& id_arr)
{
	return cg_iRIC_GetTriangleElements(id_arr.pointer());
}

int cg_iRIC_Read_Grid_Real_Node(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Real_Node(name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Integer_Node(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Integer_Node(name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Real_Cell(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Real_Cell(name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Integer_Cell(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Integer_Cell(name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Integer(const char* name, const char* dimname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Integer(name, dimname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Real(const char* name, const char* dimname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Real(name, dimname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalTime(const char* name, RealArrayContainer& time_arr)
{
	return cg_iRIC_Read_Grid_FunctionalTime(name, time_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Node(const char* name, int dimid, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Node(name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Node(const char* name, int dimid, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Real_Node(name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Cell(const char* name, int dimid, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Cell(name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Cell(const char* name, int dimid, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Real_Cell(name, dimid, v_arr.pointer());
}

int cg_iRIC_Write_Grid1d_Coords(int isize, RealArrayContainer& x_arr)
{
	return cg_iRIC_Write_Grid1d_Coords(isize, x_arr.pointer());
}

int cg_iRIC_Write_Grid2d_Coords(int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Grid2d_Coords(isize, jsize, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Grid3d_Coords(int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Grid3d_Coords(isize, jsize, ksize, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Grid_Real_Node(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Real_Node(name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Integer_Node(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Integer_Node(name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Real_Cell(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Real_Cell(name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Integer_Cell(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Integer_Cell(name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Cell_Integer(int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Cell_Integer(step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Cell_Real(int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Cell_Real(step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Cell_Integer(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Cell_Integer(name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Cell_Real(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Cell_Real(name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_GridCoord2d(int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_GridCoord2d(step, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_GridCoord3d(int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_GridCoord3d(step, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Sol_GridCoord2d(RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_GridCoord2d(x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_GridCoord3d(RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Sol_GridCoord3d(x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_IFace_Integer(int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_IFace_Integer(step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_IFace_Real(int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_IFace_Real(step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_IFace_Integer(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_IFace_Integer(name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_IFace_Real(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_IFace_Real(name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_JFace_Integer(int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_JFace_Integer(step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_JFace_Real(int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_JFace_Real(step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_JFace_Integer(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_JFace_Integer(name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_JFace_Real(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_JFace_Real(name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_KFace_Integer(int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_KFace_Integer(step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_KFace_Real(int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_KFace_Real(step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_KFace_Integer(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_KFace_Integer(name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_KFace_Real(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_KFace_Real(name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Integer(int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Integer(step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Real(int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Real(step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Integer(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Integer(name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Real(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Real(name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Pos2d(int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_Particle_Pos2d(step, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Pos3d(int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_Particle_Pos3d(step, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Real(int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Particle_Real(step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Integer(int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Particle_Integer(step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos2d(RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_Particle_Pos2d(x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos3d(RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Sol_Particle_Pos3d(x_arr.size(), x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Real(const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Particle_Real(name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Integer(const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Particle_Integer(name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos2d(int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Pos2d(step, groupname, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos3d(int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Pos3d(step, groupname, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Real(int step, const char* groupname, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Real(step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Integer(int step, const char* groupname, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Integer(step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Pos2d(int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Pos2d(step, groupname, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Type(int step, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Type(step, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Real(int step, const char* groupname, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Real(step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Integer(int step, const char* groupname, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Integer(step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polygon(int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_PolyData_Polygon(numPoints, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polyline(int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_PolyData_Polyline(numPoints, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_Cell_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Cell_Integer_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Cell_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Cell_Real_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Cell_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Cell_Integer_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Cell_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Cell_Real_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_GridCoord2d_WithGridId(int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_GridCoord2d_WithGridId(gid, step, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_GridCoord3d_WithGridId(int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_GridCoord3d_WithGridId(gid, step, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Sol_GridCoord2d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_GridCoord2d_WithGridId(gid, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_GridCoord3d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Sol_GridCoord3d_WithGridId(gid, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_IFace_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_IFace_Integer_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_IFace_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_IFace_Real_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_IFace_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_IFace_Integer_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_IFace_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_IFace_Real_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_JFace_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_JFace_Integer_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_JFace_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_JFace_Real_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_JFace_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_JFace_Integer_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_JFace_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_JFace_Real_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_KFace_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_KFace_Integer_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_KFace_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_KFace_Real_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_KFace_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_KFace_Integer_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_KFace_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_KFace_Real_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Integer_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Real_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Integer_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Real_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(gid, step, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(gid, step, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Real_WithGridId(int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Particle_Real_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Integer_WithGridId(int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Particle_Integer_WithGridId(gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(gid, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(gid, x_arr.size(), x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Real_WithGridId(int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Particle_Real_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Integer_WithGridId(int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Particle_Integer_WithGridId(gid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId(int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId(gid, step, groupname, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId(int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId(gid, step, groupname, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId(int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId(gid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId(int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId(gid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(gid, step, groupname, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Type_WithGridId(int gid, int step, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Type_WithGridId(gid, step, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Real_WithGridId(int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Real_WithGridId(gid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(gid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(gid, numPoints, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(gid, numPoints, x_arr.pointer(), y_arr.pointer());
}


// from iriclib_not_withbaseid.h
int cg_iRIC_Read_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Complex_Functional_Mul(fid, groupname, num, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Complex_FunctionalWithName_Mul(fid, groupname, num, name, paramname, v_arr.pointer());
}

int cg_iRIC_Write_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Complex_Functional_Mul(fid, groupname, num, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Complex_FunctionalWithName_Mul(fid, groupname, num, name, paramname, v_arr.size(), v_arr.pointer());
}


// from iriclib_not_withgridid.h
int cg_iRIC_Read_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Read_BC_Indices_Mul(fid, type, num, idx_arr.pointer());
}

int cg_iRIC_Read_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_BC_Functional_Mul(fid, type, num, name, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_BC_FunctionalWithName_Mul(fid, type, num, name, paramname, v_arr.pointer());
}

int cg_iRIC_Write_BC_Indices_Mul(int fid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Write_BC_Indices2_Mul(fid, type, num, idx_arr.size(), idx_arr.pointer());
}

int cg_iRIC_Write_BC_Indices2_Mul(int fid, const char* type, int num, IntArrayContainer& idx_arr)
{
	return cg_iRIC_Write_BC_Indices2_Mul(fid, type, num, idx_arr.size(), idx_arr.pointer());
}

int cg_iRIC_Write_BC_Functional_Mul(int fid, const char* type, int num, const char* name, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_BC_Functional_Mul(fid, type, num, name, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_BC_FunctionalWithName_Mul(fid, type, num, name, paramname, v_arr.size(), v_arr.pointer());
}

int cg_iRIC_Read_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Complex_Node_Mul(fid, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Complex_Cell_Mul(int fid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Complex_Cell_Mul(fid, groupname, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Complex_Node_Mul(int fid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Complex_Node_Mul(fid, groupname, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Complex_Cell_Mul(int fid, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Complex_Cell_Mul(fid, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Grid2d_Coords_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Grid2d_Coords_Mul(fid, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Grid3d_Coords_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Grid3d_Coords_Mul(fid, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_GetTriangleElements_Mul(int fid, IntArrayContainer& id_arr)
{
	return cg_iRIC_GetTriangleElements_Mul(fid, id_arr.pointer());
}

int cg_iRIC_Read_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Real_Node_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Integer_Node_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Real_Cell_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Real_Cell_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Integer_Cell_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Integer_Cell_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(int fid, const char* name, const char* dimname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(fid, name, dimname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(int fid, const char* name, const char* dimname, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(fid, name, dimname, v_arr.pointer());
}

int cg_iRIC_Read_Grid_FunctionalTime_Mul(int fid, const char* name, RealArrayContainer& time_arr)
{
	return cg_iRIC_Read_Grid_FunctionalTime_Mul(fid, name, time_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(int fid, const char* name, int dimid, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(fid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Node_Mul(int fid, const char* name, int dimid, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Real_Node_Mul(fid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(int fid, const char* name, int dimid, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(fid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(int fid, const char* name, int dimid, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(fid, name, dimid, v_arr.pointer());
}

int cg_iRIC_Write_Grid1d_Coords_Mul(int fid, int isize, RealArrayContainer& x_arr)
{
	return cg_iRIC_Write_Grid1d_Coords_Mul(fid, isize, x_arr.pointer());
}

int cg_iRIC_Write_Grid2d_Coords_Mul(int fid, int isize, int jsize, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Grid2d_Coords_Mul(fid, isize, jsize, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Grid3d_Coords_Mul(int fid, int isize, int jsize, int ksize, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Grid3d_Coords_Mul(fid, isize, jsize, ksize, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Grid_Real_Node_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Real_Node_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Integer_Node_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Integer_Node_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Real_Cell_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Real_Cell_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Grid_Integer_Cell_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Grid_Integer_Cell_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Cell_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Cell_Integer_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Cell_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Cell_Real_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Cell_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Cell_Integer_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Cell_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Cell_Real_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_GridCoord2d_Mul(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_GridCoord2d_Mul(fid, step, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_GridCoord3d_Mul(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_GridCoord3d_Mul(fid, step, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Sol_GridCoord2d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_GridCoord2d_Mul(fid, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_GridCoord3d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Sol_GridCoord3d_Mul(fid, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_IFace_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_IFace_Integer_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_IFace_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_IFace_Real_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_IFace_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_IFace_Integer_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_IFace_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_IFace_Real_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_JFace_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_JFace_Integer_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_JFace_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_JFace_Real_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_JFace_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_JFace_Integer_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_JFace_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_JFace_Real_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_KFace_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_KFace_Integer_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_KFace_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_KFace_Real_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_KFace_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_KFace_Integer_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_KFace_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_KFace_Real_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Integer_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Real_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Integer_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Real_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Pos2d_Mul(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_Particle_Pos2d_Mul(fid, step, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Pos3d_Mul(int fid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_Particle_Pos3d_Mul(fid, step, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Real_Mul(int fid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Particle_Real_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Integer_Mul(int fid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Particle_Integer_Mul(fid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos2d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_Particle_Pos2d_Mul(fid, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos3d_Mul(int fid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Sol_Particle_Pos3d_Mul(fid, x_arr.size(), x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Real_Mul(int fid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Particle_Real_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Integer_Mul(int fid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Particle_Integer_Mul(fid, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos2d_Mul(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Pos2d_Mul(fid, step, groupname, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos3d_Mul(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Pos3d_Mul(fid, step, groupname, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Real_Mul(int fid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Real_Mul(fid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Integer_Mul(int fid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Integer_Mul(fid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Pos2d_Mul(int fid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Pos2d_Mul(fid, step, groupname, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Type_Mul(int fid, int step, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Type_Mul(fid, step, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Real_Mul(int fid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Real_Mul(fid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Integer_Mul(int fid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Integer_Mul(fid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polygon_Mul(int fid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_PolyData_Polygon_Mul(fid, numPoints, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polyline_Mul(int fid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_PolyData_Polyline_Mul(fid, numPoints, x_arr.pointer(), y_arr.pointer());
}


// from iriclib_sol_cell.h
int cg_iRIC_Read_Sol_Cell_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Cell_Integer_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Cell_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Cell_Real_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Cell_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Cell_Integer_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Cell_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Cell_Real_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}


// from iriclib_sol_gridcoord.h
int cg_iRIC_Read_Sol_GridCoord2d_WithGridId_Mul(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_GridCoord2d_WithGridId_Mul(fid, gid, step, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_GridCoord3d_WithGridId_Mul(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_GridCoord3d_WithGridId_Mul(fid, gid, step, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Sol_GridCoord2d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_GridCoord2d_WithGridId_Mul(fid, gid, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_GridCoord3d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Sol_GridCoord3d_WithGridId_Mul(fid, gid, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}


// from iriclib_sol_iface.h
int cg_iRIC_Read_Sol_IFace_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_IFace_Integer_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_IFace_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_IFace_Real_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_IFace_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_IFace_Integer_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_IFace_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_IFace_Real_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}


// from iriclib_sol_jface.h
int cg_iRIC_Read_Sol_JFace_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_JFace_Integer_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_JFace_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_JFace_Real_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_JFace_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_JFace_Integer_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_JFace_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_JFace_Real_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}


// from iriclib_sol_kface.h
int cg_iRIC_Read_Sol_KFace_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_KFace_Integer_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_KFace_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_KFace_Real_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_KFace_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_KFace_Integer_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_KFace_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_KFace_Real_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}


// from iriclib_sol_node.h
int cg_iRIC_Read_Sol_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Integer_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Real_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Integer_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Real_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}


// from iriclib_sol_particle.h
int cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId_Mul(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId_Mul(fid, gid, step, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId_Mul(int fid, int gid, int step, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId_Mul(fid, gid, step, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Particle_Real_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_Particle_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_Particle_Integer_WithGridId_Mul(fid, gid, step, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId_Mul(fid, gid, x_arr.size(), x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId_Mul(int fid, int gid, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId_Mul(fid, gid, x_arr.size(), x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Real_WithGridId_Mul(int fid, int gid, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Particle_Real_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_Particle_Integer_WithGridId_Mul(int fid, int gid, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Write_Sol_Particle_Integer_WithGridId_Mul(fid, gid, name, v_arr.pointer());
}


// from iriclib_sol_particlegroup.h
int cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId_Mul(fid, gid, step, groupname, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr, RealArrayContainer& z_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId_Mul(fid, gid, step, groupname, x_arr.pointer(), y_arr.pointer(), z_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId_Mul(fid, gid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId_Mul(fid, gid, step, groupname, name, v_arr.pointer());
}


// from iriclib_sol_polydata.h
int cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId_Mul(fid, gid, step, groupname, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Type_WithGridId_Mul(int fid, int gid, int step, const char* groupname, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Type_WithGridId_Mul(fid, gid, step, groupname, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Real_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, RealArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Real_WithGridId_Mul(fid, gid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Read_Sol_PolyData_Integer_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, IntArrayContainer& v_arr)
{
	return cg_iRIC_Read_Sol_PolyData_Integer_WithGridId_Mul(fid, gid, step, groupname, name, v_arr.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId_Mul(int fid, int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId_Mul(fid, gid, numPoints, x_arr.pointer(), y_arr.pointer());
}

int cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId_Mul(int fid, int gid, int numPoints, RealArrayContainer& x_arr, RealArrayContainer& y_arr)
{
	return cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId_Mul(fid, gid, numPoints, x_arr.pointer(), y_arr.pointer());
}


// from iriclib_solution.h

