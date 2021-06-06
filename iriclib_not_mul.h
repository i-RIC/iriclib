#ifndef IRICLIB_NOT_MUL_H
#define IRICLIB_NOT_MUL_H

#include "iriclib_global.h"

#ifdef __cplusplus
extern "C" {
#endif

// from iriclib_bc.h
void IRICLIBDLL cg_iRIC_Read_BC_Count_WithGridId(int gid, const char* type, int* num);
int IRICLIBDLL cg_iRIC_Read_BC_IndicesSize_WithGridId(int gid, const char* type, int num, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_IndicesSize2_WithGridId(int gid, const char* type, int num, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_Indices_WithGridId(int gid, const char* type, int num, int* idx_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Integer_WithGridId(int gid, const char* type, int num, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_BC_Real_WithGridId(int gid, const char* type, int num, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_BC_RealSingle_WithGridId(int gid, const char* type, int num, const char* name, float* value);
int IRICLIBDLL cg_iRIC_Read_BC_StringLen_WithGridId(int gid, const char* type, int num, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_BC_String_WithGridId(int gid, const char* type, int num, const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalSize_WithGridId(int gid, const char* type, int num, const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_WithGridId(int gid, const char* type, int num, const char* name, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_RealSingle_WithGridId(int gid, const char* type, int num, const char* name, float* x_arr, float* y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_RealSingle_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, float* v_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_StringLen_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, int* length);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_String_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, char* strvalue);
int IRICLIBDLL cg_iRIC_Clear_BC_WithGridId(int gid);
int IRICLIBDLL cg_iRIC_Write_BC_Indices_WithGridId(int gid, const char* type, int num, int length, int* idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices2_WithGridId(int gid, const char* type, int num, int length, int* idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Integer_WithGridId(int gid, const char* type, int num, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_BC_Real_WithGridId(int gid, const char* type, int num, const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_BC_String_WithGridId(int gid, const char* type, int num, const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_BC_Functional_WithGridId(int gid, const char* type, int num, const char* name, int length, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, int length, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_String_WithGridId(int gid, const char* type, int num, const char* name, const char* paramname, const char* value);

// from iriclib_cc.h
int IRICLIBDLL cg_iRIC_Read_Integer(const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_Real(const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_RealSingle(const char* name, float* value);
int IRICLIBDLL cg_iRIC_Read_StringLen(const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_String(const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_FunctionalSize(const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_Functional(const char* name, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName(const char* name, const char* paramname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Functional_RealSingle(const char* name, float* x_arr, float* y_arr);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_RealSingle(const char* name, const char* paramname, float* v_arr);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_String(const char* name, const char* paramname, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_StringLen(const char* name, const char* paramname, int* length);
int IRICLIBDLL cg_iRIC_Write_Integer(const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Real(const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_String(const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_Functional(const char* name, int length, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_FunctionalWithName(const char* name, const char* paramname, int length, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_FunctionalWithName_String(const char* name, const char* paramname, const char* value);

// from iriclib_complex.h
int IRICLIBDLL cg_iRIC_Read_Complex_Count_WithBaseId(int bid, const char* groupname, int* num);
int IRICLIBDLL cg_iRIC_Read_Complex_Integer_WithBaseId(int bid, const char* groupname, int num, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_Complex_Real_WithBaseId(int bid, const char* groupname, int num, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_Complex_RealSingle_WithBaseId(int bid, const char* groupname, int num, const char* name, float* value);
int IRICLIBDLL cg_iRIC_Read_Complex_StringLen_WithBaseId(int bid, const char* groupname, int num, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_Complex_String_WithBaseId(int bid, const char* groupname, int num, const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalSize_WithBaseId(int bid, const char* groupname, int num, const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional_WithBaseId(int bid, const char* groupname, int num, const char* name, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional_RealSingle_WithBaseId(int bid, const char* groupname, int num, const char* name, float* x_arr, float* y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, float* v_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_StringLen_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, int* length);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_String_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node_WithGridId(int gid, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell_WithGridId(int gid, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Clear_Complex_WithBaseId(int bid);
int IRICLIBDLL cg_iRIC_Write_Complex_Integer_WithBaseId(int bid, const char* groupname, int num, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Complex_Real_WithBaseId(int bid, const char* groupname, int num, const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_Complex_String_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_Complex_Functional_WithBaseId(int bid, const char* groupname, int num, const char* name, int length, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, int length, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_String_WithBaseId(int bid, const char* groupname, int num, const char* name, const char* paramname, const char* value);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node_WithGridId(int gid, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell_WithGridId(int gid, const char* groupname, int* v_arr);

// from iriclib_geoutil.h
int IRICLIBDLL cg_iRIC_Read_Geo_Count(const char* name, int* count);
int IRICLIBDLL cg_iRIC_Read_Geo_Filename(const char* name, int geoid, char* strvalue, int* type);

// from iriclib_grid.h
int IRICLIBDLL cg_iRIC_Read_Grid2d_Str_Size_WithGridId(int gid, int* isize, int* jsize);
int IRICLIBDLL cg_iRIC_Read_Grid2d_Coords_WithGridId(int gid, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Grid3d_Str_Size_WithGridId(int gid, int* isize, int* jsize, int* ksize);
int IRICLIBDLL cg_iRIC_Read_Grid3d_Coords_WithGridId(int gid, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_GetTriangleElementsSize_WithGridId(int gid, int* size);
int IRICLIBDLL cg_iRIC_GetTriangleElementsSize2_WithGridId(int gid, int* size);
int IRICLIBDLL cg_iRIC_GetTriangleElements_WithGridId(int gid, int* id_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_NodeCount_WithGridId(int gid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_CellCount_WithGridId(int gid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_IFaceCount_WithGridId(int gid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_JFaceCount_WithGridId(int gid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_KFaceCount_WithGridId(int gid, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node_WithGridId(int gid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node_WithGridId(int gid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell_WithGridId(int gid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell_WithGridId(int gid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimensionSize_WithGridId(int gid, const char* name, const char* dimname, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId(int gid, const char* name, const char* dimname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId(int gid, const char* name, const char* dimname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTimeSize_WithGridId(int gid, const char* name, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime_WithGridId(int gid, const char* name, double* time_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId(int gid, const char* name, int dimid, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId(int gid, const char* name, int dimid, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId(int gid, const char* name, int dimid, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId(int gid, const char* name, int dimid, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid1d_Coords_WithGridId(int isize, double* x_arr, int* gid);
int IRICLIBDLL cg_iRIC_Write_Grid2d_Coords_WithGridId(int isize, int jsize, double* x_arr, double* y_arr, int* gid);
int IRICLIBDLL cg_iRIC_Write_Grid3d_Coords_WithGridId(int isize, int jsize, int ksize, double* x_arr, double* y_arr, double* z_arr, int* gid);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node_WithGridId(int gid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node_WithGridId(int gid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell_WithGridId(int gid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell_WithGridId(int gid, const char* name, int* v_arr);

// from iriclib_not_withbaseid.h
int IRICLIBDLL cg_iRIC_Read_Complex_Count(const char* groupname, int* num);
int IRICLIBDLL cg_iRIC_Read_Complex_Integer(const char* groupname, int num, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_Complex_Real(const char* groupname, int num, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_Complex_RealSingle(const char* groupname, int num, const char* name, float* value);
int IRICLIBDLL cg_iRIC_Read_Complex_StringLen(const char* groupname, int num, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_Complex_String(const char* groupname, int num, const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalSize(const char* groupname, int num, const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional(const char* groupname, int num, const char* name, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional_RealSingle(const char* groupname, int num, const char* name, float* x_arr, float* y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_RealSingle(const char* groupname, int num, const char* name, const char* paramname, float* v_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_StringLen(const char* groupname, int num, const char* name, const char* paramname, int* length);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_String(const char* groupname, int num, const char* name, const char* paramname, char* strvalue);
int IRICLIBDLL cg_iRIC_Clear_Complex();
int IRICLIBDLL cg_iRIC_Write_Complex_Integer(const char* groupname, int num, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Complex_Real(const char* groupname, int num, const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_Complex_String(const char* groupname, int num, const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_Complex_Functional(const char* groupname, int num, const char* name, int length, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName(const char* groupname, int num, const char* name, const char* paramname, int length, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_String(const char* groupname, int num, const char* name, const char* paramname, const char* value);

// from iriclib_not_withgridid.h
void IRICLIBDLL cg_iRIC_Read_BC_Count(const char* type, int* num);
int IRICLIBDLL cg_iRIC_Read_BC_IndicesSize(const char* type, int num, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_IndicesSize2(const char* type, int num, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_Indices(const char* type, int num, int* idx_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Integer(const char* type, int num, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_BC_Real(const char* type, int num, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_BC_RealSingle(const char* type, int num, const char* name, float* value);
int IRICLIBDLL cg_iRIC_Read_BC_StringLen(const char* type, int num, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_BC_String(const char* type, int num, const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalSize(const char* type, int num, const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_BC_Functional(const char* type, int num, const char* name, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_BC_Functional_RealSingle(const char* type, int num, const char* name, float* x_arr, float* y_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_RealSingle(const char* type, int num, const char* name, const char* paramname, float* v_arr);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_StringLen(const char* type, int num, const char* name, const char* paramname, int* length);
int IRICLIBDLL cg_iRIC_Read_BC_FunctionalWithName_String(const char* type, int num, const char* name, const char* paramname, char* strvalue);
int IRICLIBDLL cg_iRIC_Clear_BC();
int IRICLIBDLL cg_iRIC_Write_BC_Indices(const char* type, int num, int length, int* idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Indices2(const char* type, int num, int length, int* idx_arr);
int IRICLIBDLL cg_iRIC_Write_BC_Integer(const char* type, int num, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_BC_Real(const char* type, int num, const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_BC_String(const char* type, int num, const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_BC_Functional(const char* type, int num, const char* name, int length, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName(const char* type, int num, const char* name, const char* paramname, int length, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_BC_FunctionalWithName_String(const char* type, int num, const char* name, const char* paramname, const char* value);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Node(const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Complex_Cell(const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Node(const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Complex_Cell(const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid2d_Str_Size(int* isize, int* jsize);
int IRICLIBDLL cg_iRIC_Read_Grid2d_Coords(double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Grid3d_Str_Size(int* isize, int* jsize, int* ksize);
int IRICLIBDLL cg_iRIC_Read_Grid3d_Coords(double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_GetTriangleElementsSize(int* size);
int IRICLIBDLL cg_iRIC_GetTriangleElementsSize2(int* size);
int IRICLIBDLL cg_iRIC_GetTriangleElements(int* id_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_NodeCount(int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_CellCount(int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_IFaceCount(int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_JFaceCount(int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_KFaceCount(int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Node(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Node(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Real_Cell(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Integer_Cell(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimensionSize(const char* name, const char* dimname, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Integer(const char* name, const char* dimname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalDimension_Real(const char* name, const char* dimname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTimeSize(const char* name, int* count);
int IRICLIBDLL cg_iRIC_Read_Grid_FunctionalTime(const char* name, double* time_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Node(const char* name, int dimid, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Node(const char* name, int dimid, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Integer_Cell(const char* name, int dimid, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Grid_Functional_Real_Cell(const char* name, int dimid, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid1d_Coords(int isize, double* x_arr);
int IRICLIBDLL cg_iRIC_Write_Grid2d_Coords(int isize, int jsize, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Grid3d_Coords(int isize, int jsize, int ksize, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Node(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Node(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Real_Cell(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Grid_Integer_Cell(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer(int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real(int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Grid2d_Coords(int step, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Grid3d_Coords(int step, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d(double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d(double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer(int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real(int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer(int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real(int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Integer(int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Real(int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Integer(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Real(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Integer(int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Real(int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Integer(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Real(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Count(int step, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos2d(int step, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos3d(int step, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Real(int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Integer(int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d(int count, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d(int count, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real(const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer(const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Count(int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos2d(int step, const char* groupname, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos3d(int step, const char* groupname, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Real(int step, const char* groupname, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Integer(int step, const char* groupname, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_GroupBegin(const char* name);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_GroupEnd();
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Pos2d(double x, double y);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Pos3d(double x, double y, double z);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Integer(const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Real(const char* name, double value);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_DataCount(int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_CoordinateCount(int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Pos2d(int step, const char* groupname, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Type(int step, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Real(int step, const char* groupname, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Integer(int step, const char* groupname, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_GroupBegin(const char* name);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_GroupEnd();
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon(int numPoints, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline(int numPoints, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Integer(const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Real(const char* name, double value);

// from iriclib_sol_cell.h
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Integer_WithGridId(int gid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Cell_Real_WithGridId(int gid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Integer_WithGridId(int gid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Cell_Real_WithGridId(int gid, const char* name, double* v_arr);

// from iriclib_sol_gridcoord.h
int IRICLIBDLL cg_iRIC_Read_Sol_Grid2d_Coords_WithGridId(int gid, int step, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Grid3d_Coords_WithGridId(int gid, int step, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord2d_WithGridId(int gid, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_GridCoord3d_WithGridId(int gid, double* x_arr, double* y_arr, double* z_arr);

// from iriclib_sol_iface.h
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Integer_WithGridId(int gid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_IFace_Real_WithGridId(int gid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Integer_WithGridId(int gid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_IFace_Real_WithGridId(int gid, const char* name, double* v_arr);

// from iriclib_sol_jface.h
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Integer_WithGridId(int gid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_JFace_Real_WithGridId(int gid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Integer_WithGridId(int gid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_JFace_Real_WithGridId(int gid, const char* name, double* v_arr);

// from iriclib_sol_kface.h
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Integer_WithGridId(int gid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_KFace_Real_WithGridId(int gid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Integer_WithGridId(int gid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_KFace_Real_WithGridId(int gid, const char* name, double* v_arr);

// from iriclib_sol_node.h
int IRICLIBDLL cg_iRIC_Read_Sol_Integer_WithGridId(int gid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Real_WithGridId(int gid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Integer_WithGridId(int gid, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Real_WithGridId(int gid, const char* name, double* v_arr);

// from iriclib_sol_particle.h
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Count_WithGridId(int gid, int step, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(int gid, int step, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(int gid, int step, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Real_WithGridId(int gid, int step, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_Particle_Integer_WithGridId(int gid, int step, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(int gid, int count, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(int gid, int count, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Real_WithGridId(int gid, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_Particle_Integer_WithGridId(int gid, const char* name, int* v_arr);

// from iriclib_sol_particlegroup.h
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Count_WithGridId(int gid, int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId(int gid, int step, const char* groupname, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId(int gid, int step, const char* groupname, double* x_arr, double* y_arr, double* z_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId(int gid, int step, const char* groupname, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId(int gid, int step, const char* groupname, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_WithGridId(int gid, const char* name);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_WithGridId(int gid);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Pos2d_WithGridId(int gid, double x, double y);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Pos3d_WithGridId(int gid, double x, double y, double z);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Integer_WithGridId(int gid, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Sol_ParticleGroup_Real_WithGridId(int gid, const char* name, double value);

// from iriclib_sol_polydata.h
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_DataCount_WithGridId(int gid, int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_CoordinateCount_WithGridId(int gid, int step, const char* groupname, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(int gid, int step, const char* groupname, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Type_WithGridId(int gid, int step, const char* groupname, int* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Real_WithGridId(int gid, int step, const char* groupname, const char* name, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(int gid, int step, const char* groupname, const char* name, int* v_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_GroupBegin_WithGridId(int gid, const char* name);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_GroupEnd_WithGridId(int gid);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(int gid, int numPoints, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(int gid, int numPoints, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Integer_WithGridId(int gid, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Sol_PolyData_Real_WithGridId(int gid, const char* name, double value);

// from iriclib_solution.h
int IRICLIBDLL cg_iRIC_Read_Sol_Count(int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_Time(int step, double* time);
int IRICLIBDLL cg_iRIC_Read_Sol_Iteration(int step, int* index);
int IRICLIBDLL cg_iRIC_Read_Sol_BaseIterative_Integer(int step, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_Sol_BaseIterative_Real(int step, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_Sol_BaseIterative_StringLen(int step, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_Sol_BaseIterative_String(int step, const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Write_Sol_Time(double time);
int IRICLIBDLL cg_iRIC_Write_Sol_Iteration(int index);
int IRICLIBDLL cg_iRIC_Write_Sol_BaseIterative_Integer(const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Sol_BaseIterative_Real(const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_Sol_BaseIterative_String(const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_ErrorCode(int errorcode);

#ifdef __cplusplus
}
#endif

#endif // IRICLIB_NOT_MUL_H
