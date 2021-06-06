#ifndef IRICLIB_NOT_WITHGRIDID_H
#define IRICLIB_NOT_WITHGRIDID_H

#include "iriclib_global.h"

#ifdef __cplusplus
extern "C" {
#endif

// from iriclib_bc.h
void IRICLIBDLL cg_iRIC_Read_BC_Count_Mul(int fid, const char* type, int* num);
int IRICLIBDLL cg_iRIC_Read_BC_IndicesSize_Mul(int fid, const char* type, int num, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_IndicesSize2_Mul(int fid, const char* type, int num, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_Indices_Mul(int fid, const char* type, int num, int* idx_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Integer_Mul(int fid, const char* type, int num, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_BC_Real_Mul(int fid, const char* type, int num, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_BC_RealSingle_Mul(int fid, const char* type, int num, const char* name, float* value);
int IRICLIBDLL cg_iRIC_Read_BC_StringLen_Mul(int fid, const char* type, int num, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_BC_String_Mul(int fid, const char* type, int num, const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalSize_Mul(int fid, const char* type, int num, const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_Mul(int fid, const char* type, int num, const char* name, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_RealSingle_Mul(int fid, const char* type, int num, const char* name, float* x_arr, float* y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_RealSingle_Mul(int fid, const char* type, int num, const char* name, const char* paramname, float* v_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_StringLen_Mul(int fid, const char* type, int num, const char* name, const char* paramname, int* length);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_String_Mul(int fid, const char* type, int num, const char* name, const char* paramname, char* strvalue);
int IRICLIBDLL cg_iRIC_Clear_BC_Mul(int fid);
int IRICLIBDLL cg_iRIC_Write_BC_Indices_Mul(int fid, const char* type, int num, int length, int* idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices2_Mul(int fid, const char* type, int num, int length, int* idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Integer_Mul(int fid, const char* type, int num, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_BC_Real_Mul(int fid, const char* type, int num, const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_BC_String_Mul(int fid, const char* type, int num, const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_BC_Functional_Mul(int fid, const char* type, int num, const char* name, int length, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, int length, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_String_Mul(int fid, const char* type, int num, const char* name, const char* paramname, const char* value);

// from iriclib_complex.h
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node_Mul(int fid, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell_Mul(int fid, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node_Mul(int fid, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell_Mul(int fid, const char* groupname, int* v_arr);

// from iriclib_grid.h
int IRICLIBDLL cg_iRIC_Read_Grid2d_Str_Size_Mul(int fid, int* isize, int* jsize);
int IRICLIBDLL cg_iRIC_Read_Grid2d_Coords_Mul(int fid, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Grid3d_Str_Size_Mul(int fid, int* isize, int* jsize, int* ksize);
int IRICLIBDLL cg_iRIC_Read_Grid3d_Coords_Mul(int fid, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_GetTriangleElementsSize_Mul(int fid, int* size);
int IRICLIBDLL cg_iRIC_GetTriangleElementsSize2_Mul(int fid, int* size);
int IRICLIBDLL cg_iRIC_GetTriangleElements_Mul(int fid, int* id_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_NodeCount_Mul(int fid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_CellCount_Mul(int fid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_IFaceCount_Mul(int fid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_JFaceCount_Mul(int fid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_KFaceCount_Mul(int fid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node_Mul(int fid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node_Mul(int fid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell_Mul(int fid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell_Mul(int fid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimensionSize_Mul(int fid, const char* name, const char* dimname, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(int fid, const char* name, const char* dimname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(int fid, const char* name, const char* dimname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTimeSize_Mul(int fid, const char* name, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime_Mul(int fid, const char* name, double* time_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(int fid, const char* name, int dimid, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node_Mul(int fid, const char* name, int dimid, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(int fid, const char* name, int dimid, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(int fid, const char* name, int dimid, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid1d_Coords_Mul(int fid, int isize, double* x_arr);
int IRICLIBDLL cg_iRIC_Write_Grid2d_Coords_Mul(int fid, int isize, int jsize, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Grid3d_Coords_Mul(int fid, int isize, int jsize, int ksize, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node_Mul(int fid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node_Mul(int fid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell_Mul(int fid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell_Mul(int fid, const char* name, int* v_arr);

// from iriclib_sol_cell.h
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer_Mul(int fid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real_Mul(int fid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer_Mul(int fid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real_Mul(int fid, const char* name, double* v_arr);

// from iriclib_sol_gridcoord.h
int IRICLIBDLL cg_iRIC_Read_Sol_Grid2d_Coords_Mul(int fid, int step, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Grid3d_Coords_Mul(int fid, int step, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Grid2d_Coords_Mul(int fid, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Grid3d_Coords_Mul(int fid, double* x_arr, double* y_arr, double* z_arr);

// from iriclib_sol_iface.h
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer_Mul(int fid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real_Mul(int fid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer_Mul(int fid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real_Mul(int fid, const char* name, double* v_arr);

// from iriclib_sol_jface.h
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer_Mul(int fid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real_Mul(int fid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer_Mul(int fid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real_Mul(int fid, const char* name, double* v_arr);

// from iriclib_sol_kface.h
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Integer_Mul(int fid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Real_Mul(int fid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Integer_Mul(int fid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Real_Mul(int fid, const char* name, double* v_arr);

// from iriclib_sol_node.h
int IRICLIBDLL cg_iRIC_Read_Sol_Node_Integer_Mul(int fid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Node_Real_Mul(int fid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Node_Integer_Mul(int fid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Real_Mul(int fid, const char* name, double* v_arr);

// from iriclib_sol_particle.h
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Count_Mul(int fid, int step, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos2d_Mul(int fid, int step, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos3d_Mul(int fid, int step, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Real_Mul(int fid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Integer_Mul(int fid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d_Mul(int fid, int count, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d_Mul(int fid, int count, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real_Mul(int fid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer_Mul(int fid, const char* name, int* v_arr);

// from iriclib_sol_particlegroup.h
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Count_Mul(int fid, int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos2d_Mul(int fid, int step, const char* groupname, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos3d_Mul(int fid, int step, const char* groupname, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Real_Mul(int fid, int step, const char* groupname, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Integer_Mul(int fid, int step, const char* groupname, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(int fid, const char* name);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(int fid);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul(int fid, double x, double y);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul(int fid, double x, double y, double z);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(int fid, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(int fid, const char* name, double value);

// from iriclib_sol_polydata.h
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_DataCount_Mul(int fid, int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_CoordinateCount_Mul(int fid, int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Pos2d_Mul(int fid, int step, const char* groupname, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Type_Mul(int fid, int step, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Real_Mul(int fid, int step, const char* groupname, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Integer_Mul(int fid, int step, const char* groupname, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_GroupBegin_Mul(int fid, const char* name);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_GroupEnd_Mul(int fid);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon_Mul(int fid, int numPoints, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline_Mul(int fid, int numPoints, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Integer_Mul(int fid, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Real_Mul(int fid, const char* name, double value);

#ifdef __cplusplus
}
#endif

#endif // IRICLIB_NOT_WITHGRIDID_H
