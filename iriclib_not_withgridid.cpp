#include "error_macros.h"
#include "h5cgnsfile.h"
#include "iriclib.h"
#include "iriclib_errorcodes.h"
#include "internal/iric_h5cgnsfiles.h"

using namespace iRICLib;

namespace {

int getlastGridId(int fid, int *gid)
{
	H5CgnsFile* file = nullptr;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->lastGridId(gid);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

} // namespace

// from iriclib_bc.h
void cg_iRIC_Read_BC_Count(int fid, const char* type, int* num)
{
  int gid;
  getlastGridId(fid, &gid);

  cg_iRIC_Read_BC_Count_WithGridId(fid, gid, type, num);
}

int cg_iRIC_Read_BC_IndicesSize(int fid, const char* type, int num, int* size)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_IndicesSize_WithGridId(fid, gid, type, num, size);
}

int cg_iRIC_Read_BC_IndicesSize2(int fid, const char* type, int num, int* size)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_IndicesSize2_WithGridId(fid, gid, type, num, size);
}

int cg_iRIC_Read_BC_Indices(int fid, const char* type, int num, int* idx_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_Indices_WithGridId(fid, gid, type, num, idx_arr);
}

int cg_iRIC_Read_BC_Integer(int fid, const char* type, int num, const char* name, int* value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_Integer_WithGridId(fid, gid, type, num, name, value);
}

int cg_iRIC_Read_BC_Real(int fid, const char* type, int num, const char* name, double* value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_Real_WithGridId(fid, gid, type, num, name, value);
}

int cg_iRIC_Read_BC_RealSingle(int fid, const char* type, int num, const char* name, float* value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_RealSingle_WithGridId(fid, gid, type, num, name, value);
}

int cg_iRIC_Read_BC_StringLen(int fid, const char* type, int num, const char* name, int* length)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_StringLen_WithGridId(fid, gid, type, num, name, length);
}

int cg_iRIC_Read_BC_String(int fid, const char* type, int num, const char* name, char* strvalue)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_String_WithGridId(fid, gid, type, num, name, strvalue);
}

int cg_iRIC_Read_BC_FunctionalSize(int fid, const char* type, int num, const char* name, int* size)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_FunctionalSize_WithGridId(fid, gid, type, num, name, size);
}

int cg_iRIC_Read_BC_Functional(int fid, const char* type, int num, const char* name, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_Functional_WithGridId(fid, gid, type, num, name, x_arr, y_arr);
}

int cg_iRIC_Read_BC_FunctionalWithName(int fid, const char* type, int num, const char* name, const char* paramname, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_FunctionalWithName_WithGridId(fid, gid, type, num, name, paramname, v_arr);
}

int cg_iRIC_Read_BC_Functional_RealSingle(int fid, const char* type, int num, const char* name, float* x_arr, float* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_Functional_RealSingle_WithGridId(fid, gid, type, num, name, x_arr, y_arr);
}

int cg_iRIC_Read_BC_FunctionalWithName_RealSingle(int fid, const char* type, int num, const char* name, const char* paramname, float* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_FunctionalWithName_RealSingle_WithGridId(fid, gid, type, num, name, paramname, v_arr);
}

int cg_iRIC_Read_BC_FunctionalWithName_StringLen(int fid, const char* type, int num, const char* name, const char* paramname, int* length)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_FunctionalWithName_StringLen_WithGridId(fid, gid, type, num, name, paramname, length);
}

int cg_iRIC_Read_BC_FunctionalWithName_String(int fid, const char* type, int num, const char* name, const char* paramname, char* strvalue)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_BC_FunctionalWithName_String_WithGridId(fid, gid, type, num, name, paramname, strvalue);
}

int cg_iRIC_Clear_BC(int fid)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Clear_BC_WithGridId(fid, gid);
}

int cg_iRIC_Write_BC_Indices(int fid, const char* type, int num, int length, int* idx_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_BC_Indices_WithGridId(fid, gid, type, num, length, idx_arr);
}

int cg_iRIC_Write_BC_Indices2(int fid, const char* type, int num, int length, int* idx_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_BC_Indices2_WithGridId(fid, gid, type, num, length, idx_arr);
}

int cg_iRIC_Write_BC_Integer(int fid, const char* type, int num, const char* name, int value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_BC_Integer_WithGridId(fid, gid, type, num, name, value);
}

int cg_iRIC_Write_BC_Real(int fid, const char* type, int num, const char* name, double value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_BC_Real_WithGridId(fid, gid, type, num, name, value);
}

int cg_iRIC_Write_BC_String(int fid, const char* type, int num, const char* name, const char* value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_BC_String_WithGridId(fid, gid, type, num, name, value);
}

int cg_iRIC_Write_BC_Functional(int fid, const char* type, int num, const char* name, int length, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_BC_Functional_WithGridId(fid, gid, type, num, name, length, x_arr, y_arr);
}

int cg_iRIC_Write_BC_FunctionalWithName(int fid, const char* type, int num, const char* name, const char* paramname, int length, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_BC_FunctionalWithName_WithGridId(fid, gid, type, num, name, paramname, length, v_arr);
}

int cg_iRIC_Write_BC_FunctionalWithName_String(int fid, const char* type, int num, const char* name, const char* paramname, const char* value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_BC_FunctionalWithName_String_WithGridId(fid, gid, type, num, name, paramname, value);
}


// from iriclib_complex.h
int cg_iRIC_Read_Grid_Complex_Node(int fid, const char* groupname, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Complex_Node_WithGridId(fid, gid, groupname, v_arr);
}

int cg_iRIC_Read_Grid_Complex_Cell(int fid, const char* groupname, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Complex_Cell_WithGridId(fid, gid, groupname, v_arr);
}

int cg_iRIC_Write_Grid_Complex_Node(int fid, const char* groupname, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Grid_Complex_Node_WithGridId(fid, gid, groupname, v_arr);
}

int cg_iRIC_Write_Grid_Complex_Cell(int fid, const char* groupname, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Grid_Complex_Cell_WithGridId(fid, gid, groupname, v_arr);
}


// from iriclib_grid.h
int cg_iRIC_Read_Grid2d_Str_Size(int fid, int* isize, int* jsize)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid2d_Str_Size_WithGridId(fid, gid, isize, jsize);
}

int cg_iRIC_Read_Grid2d_Coords(int fid, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid2d_Coords_WithGridId(fid, gid, x_arr, y_arr);
}

int cg_iRIC_Read_Grid3d_Str_Size(int fid, int* isize, int* jsize, int* ksize)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid3d_Str_Size_WithGridId(fid, gid, isize, jsize, ksize);
}

int cg_iRIC_Read_Grid3d_Coords(int fid, double* x_arr, double* y_arr, double* z_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid3d_Coords_WithGridId(fid, gid, x_arr, y_arr, z_arr);
}

int cg_iRIC_Read_Grid_TriangleElementsSize(int fid, int* size)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_TriangleElementsSize_WithGridId(fid, gid, size);
}

int cg_iRIC_Read_Grid_TriangleElementsSize2(int fid, int* size)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_TriangleElementsSize2_WithGridId(fid, gid, size);
}

int cg_iRIC_Read_Grid_TriangleElements(int fid, int* id_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_TriangleElements_WithGridId(fid, gid, id_arr);
}

int cg_iRIC_Read_Grid_NodeCount(int fid, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_NodeCount_WithGridId(fid, gid, count);
}

int cg_iRIC_Read_Grid_CellCount(int fid, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_CellCount_WithGridId(fid, gid, count);
}

int cg_iRIC_Read_Grid_IFaceCount(int fid, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_IFaceCount_WithGridId(fid, gid, count);
}

int cg_iRIC_Read_Grid_JFaceCount(int fid, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_JFaceCount_WithGridId(fid, gid, count);
}

int cg_iRIC_Read_Grid_KFaceCount(int fid, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_KFaceCount_WithGridId(fid, gid, count);
}

int cg_iRIC_Read_Grid_Real_Node(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Real_Node_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Read_Grid_Integer_Node(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Integer_Node_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Read_Grid_Real_Cell(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Real_Cell_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Read_Grid_Integer_Cell(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Integer_Cell_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Read_Grid_FunctionalDimensionSize(int fid, const char* name, const char* dimname, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_FunctionalDimensionSize_WithGridId(fid, gid, name, dimname, count);
}

int cg_iRIC_Read_Grid_FunctionalDimension_Integer(int fid, const char* name, const char* dimname, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId(fid, gid, name, dimname, v_arr);
}

int cg_iRIC_Read_Grid_FunctionalDimension_Real(int fid, const char* name, const char* dimname, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId(fid, gid, name, dimname, v_arr);
}

int cg_iRIC_Read_Grid_FunctionalTimeSize(int fid, const char* name, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_FunctionalTimeSize_WithGridId(fid, gid, name, count);
}

int cg_iRIC_Read_Grid_FunctionalTime(int fid, const char* name, double* time_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_FunctionalTime_WithGridId(fid, gid, name, time_arr);
}

int cg_iRIC_Read_Grid_Functional_Integer_Node(int fid, const char* name, int dimid, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId(fid, gid, name, dimid, v_arr);
}

int cg_iRIC_Read_Grid_Functional_Real_Node(int fid, const char* name, int dimid, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId(fid, gid, name, dimid, v_arr);
}

int cg_iRIC_Read_Grid_Functional_Integer_Cell(int fid, const char* name, int dimid, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId(fid, gid, name, dimid, v_arr);
}

int cg_iRIC_Read_Grid_Functional_Real_Cell(int fid, const char* name, int dimid, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId(fid, gid, name, dimid, v_arr);
}

int cg_iRIC_Write_Grid1d_Coords(int fid, int isize, double* x_arr)
{
  int gid;

  return cg_iRIC_Write_Grid1d_Coords_WithGridId(fid, isize, x_arr, &gid);
}

int cg_iRIC_Write_Grid2d_Coords(int fid, int isize, int jsize, double* x_arr, double* y_arr)
{
  int gid;

  return cg_iRIC_Write_Grid2d_Coords_WithGridId(fid, isize, jsize, x_arr, y_arr, &gid);
}

int cg_iRIC_Write_Grid3d_Coords(int fid, int isize, int jsize, int ksize, double* x_arr, double* y_arr, double* z_arr)
{
  int gid;

  return cg_iRIC_Write_Grid3d_Coords_WithGridId(fid, isize, jsize, ksize, x_arr, y_arr, z_arr, &gid);
}

int cg_iRIC_Write_Grid_Real_Node(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Grid_Real_Node_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Grid_Integer_Node(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Grid_Integer_Node_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Grid_Real_Cell(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Grid_Real_Cell_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Grid_Integer_Cell(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Grid_Integer_Cell_WithGridId(fid, gid, name, v_arr);
}


// from iriclib_sol_cell.h
int cg_iRIC_Read_Sol_Cell_Integer(int fid, int step, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Cell_Integer_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Read_Sol_Cell_Real(int fid, int step, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Cell_Real_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Write_Sol_Cell_Integer(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Cell_Integer_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Sol_Cell_Real(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Cell_Real_WithGridId(fid, gid, name, v_arr);
}


// from iriclib_sol_gridcoord.h
int cg_iRIC_Read_Sol_Grid2d_Coords(int fid, int step, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Grid2d_Coords_WithGridId(fid, gid, step, x_arr, y_arr);
}

int cg_iRIC_Read_Sol_Grid3d_Coords(int fid, int step, double* x_arr, double* y_arr, double* z_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Grid3d_Coords_WithGridId(fid, gid, step, x_arr, y_arr, z_arr);
}

int cg_iRIC_Write_Sol_Grid2d_Coords(int fid, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Grid2d_Coords_WithGridId(fid, gid, x_arr, y_arr);
}

int cg_iRIC_Write_Sol_Grid3d_Coords(int fid, double* x_arr, double* y_arr, double* z_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Grid3d_Coords_WithGridId(fid, gid, x_arr, y_arr, z_arr);
}


// from iriclib_sol_iface.h
int cg_iRIC_Read_Sol_IFace_Integer(int fid, int step, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_IFace_Integer_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Read_Sol_IFace_Real(int fid, int step, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_IFace_Real_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Write_Sol_IFace_Integer(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_IFace_Integer_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Sol_IFace_Real(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_IFace_Real_WithGridId(fid, gid, name, v_arr);
}


// from iriclib_sol_jface.h
int cg_iRIC_Read_Sol_JFace_Integer(int fid, int step, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_JFace_Integer_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Read_Sol_JFace_Real(int fid, int step, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_JFace_Real_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Write_Sol_JFace_Integer(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_JFace_Integer_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Sol_JFace_Real(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_JFace_Real_WithGridId(fid, gid, name, v_arr);
}


// from iriclib_sol_kface.h
int cg_iRIC_Read_Sol_KFace_Integer(int fid, int step, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_KFace_Integer_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Read_Sol_KFace_Real(int fid, int step, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_KFace_Real_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Write_Sol_KFace_Integer(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_KFace_Integer_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Sol_KFace_Real(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_KFace_Real_WithGridId(fid, gid, name, v_arr);
}


// from iriclib_sol_node.h
int cg_iRIC_Read_Sol_Node_Integer(int fid, int step, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Node_Integer_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Read_Sol_Node_Real(int fid, int step, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Node_Real_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Write_Sol_Node_Integer(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Node_Integer_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Sol_Node_Real(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Node_Real_WithGridId(fid, gid, name, v_arr);
}


// from iriclib_sol_particle.h
int cg_iRIC_Read_Sol_Particle_Count(int fid, int step, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Particle_Count_WithGridId(fid, gid, step, count);
}

int cg_iRIC_Read_Sol_Particle_Pos2d(int fid, int step, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(fid, gid, step, x_arr, y_arr);
}

int cg_iRIC_Read_Sol_Particle_Pos3d(int fid, int step, double* x_arr, double* y_arr, double* z_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(fid, gid, step, x_arr, y_arr, z_arr);
}

int cg_iRIC_Read_Sol_Particle_Real(int fid, int step, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Particle_Real_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Read_Sol_Particle_Integer(int fid, int step, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_Particle_Integer_WithGridId(fid, gid, step, name, v_arr);
}

int cg_iRIC_Write_Sol_Particle_Pos2d(int fid, int count, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(fid, gid, count, x_arr, y_arr);
}

int cg_iRIC_Write_Sol_Particle_Pos3d(int fid, int count, double* x_arr, double* y_arr, double* z_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(fid, gid, count, x_arr, y_arr, z_arr);
}

int cg_iRIC_Write_Sol_Particle_Real(int fid, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Particle_Real_WithGridId(fid, gid, name, v_arr);
}

int cg_iRIC_Write_Sol_Particle_Integer(int fid, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_Particle_Integer_WithGridId(fid, gid, name, v_arr);
}


// from iriclib_sol_particlegroup.h
int cg_iRIC_Read_Sol_ParticleGroup_Count(int fid, int step, const char* groupname, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_ParticleGroup_Count_WithGridId(fid, gid, step, groupname, count);
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos2d(int fid, int step, const char* groupname, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId(fid, gid, step, groupname, x_arr, y_arr);
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos3d(int fid, int step, const char* groupname, double* x_arr, double* y_arr, double* z_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId(fid, gid, step, groupname, x_arr, y_arr, z_arr);
}

int cg_iRIC_Read_Sol_ParticleGroup_Real(int fid, int step, const char* groupname, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId(fid, gid, step, groupname, name, v_arr);
}

int cg_iRIC_Read_Sol_ParticleGroup_Integer(int fid, int step, const char* groupname, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId(fid, gid, step, groupname, name, v_arr);
}

int cg_iRIC_Write_Sol_ParticleGroup_GroupBegin(int fid, const char* name)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_WithGridId(fid, gid, name);
}

int cg_iRIC_Write_Sol_ParticleGroup_GroupEnd(int fid)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_WithGridId(fid, gid);
}

int cg_iRIC_Write_Sol_ParticleGroup_Pos2d(int fid, double x, double y)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_ParticleGroup_Pos2d_WithGridId(fid, gid, x, y);
}

int cg_iRIC_Write_Sol_ParticleGroup_Pos3d(int fid, double x, double y, double z)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_ParticleGroup_Pos3d_WithGridId(fid, gid, x, y, z);
}

int cg_iRIC_Write_Sol_ParticleGroup_Integer(int fid, const char* name, int value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_ParticleGroup_Integer_WithGridId(fid, gid, name, value);
}

int cg_iRIC_Write_Sol_ParticleGroup_Real(int fid, const char* name, double value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_ParticleGroup_Real_WithGridId(fid, gid, name, value);
}


// from iriclib_sol_polydata.h
int cg_iRIC_Read_Sol_PolyData_DataCount(int fid, int step, const char* groupname, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_PolyData_DataCount_WithGridId(fid, gid, step, groupname, count);
}

int cg_iRIC_Read_Sol_PolyData_CoordinateCount(int fid, int step, const char* groupname, int* count)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_PolyData_CoordinateCount_WithGridId(fid, gid, step, groupname, count);
}

int cg_iRIC_Read_Sol_PolyData_Pos2d(int fid, int step, const char* groupname, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(fid, gid, step, groupname, x_arr, y_arr);
}

int cg_iRIC_Read_Sol_PolyData_Type(int fid, int step, const char* groupname, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_PolyData_Type_WithGridId(fid, gid, step, groupname, v_arr);
}

int cg_iRIC_Read_Sol_PolyData_Real(int fid, int step, const char* groupname, const char* name, double* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_PolyData_Real_WithGridId(fid, gid, step, groupname, name, v_arr);
}

int cg_iRIC_Read_Sol_PolyData_Integer(int fid, int step, const char* groupname, const char* name, int* v_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(fid, gid, step, groupname, name, v_arr);
}

int cg_iRIC_Write_Sol_PolyData_GroupBegin(int fid, const char* name)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_PolyData_GroupBegin_WithGridId(fid, gid, name);
}

int cg_iRIC_Write_Sol_PolyData_GroupEnd(int fid)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_PolyData_GroupEnd_WithGridId(fid, gid);
}

int cg_iRIC_Write_Sol_PolyData_Polygon(int fid, int numPoints, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(fid, gid, numPoints, x_arr, y_arr);
}

int cg_iRIC_Write_Sol_PolyData_Polyline(int fid, int numPoints, double* x_arr, double* y_arr)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(fid, gid, numPoints, x_arr, y_arr);
}

int cg_iRIC_Write_Sol_PolyData_Integer(int fid, const char* name, int value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_PolyData_Integer_WithGridId(fid, gid, name, value);
}

int cg_iRIC_Write_Sol_PolyData_Real(int fid, const char* name, double value)
{
  int gid;
  int ier = getlastGridId(fid, &gid);
  RETURN_IF_ERR;

  return cg_iRIC_Write_Sol_PolyData_Real_WithGridId(fid, gid, name, value);
}


