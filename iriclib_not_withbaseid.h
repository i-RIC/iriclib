#ifndef IRICLIB_NOT_WITHBASEID_H
#define IRICLIB_NOT_WITHBASEID_H

#include "iriclib_global.h"

#ifdef __cplusplus
extern "C" {
#endif

// from iriclib_complex.h
int IRICLIBDLL cg_iRIC_Read_Complex_Count_Mul(int fid, const char* groupname, int* num);
int IRICLIBDLL cg_iRIC_Read_Complex_Integer_Mul(int fid, const char* groupname, int num, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_Complex_Real_Mul(int fid, const char* groupname, int num, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_Complex_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, float* value);
int IRICLIBDLL cg_iRIC_Read_Complex_StringLen_Mul(int fid, const char* groupname, int num, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_Complex_String_Mul(int fid, const char* groupname, int num, const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalSize_Mul(int fid, const char* groupname, int num, const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_Functional_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, float* x_arr, float* y_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, float* v_arr);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_StringLen_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, int* length);
int IRICLIBDLL cg_iRIC_Read_Complex_FunctionalWithName_String_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue);
int IRICLIBDLL cg_iRIC_Clear_Complex_Mul(int fid);
int IRICLIBDLL cg_iRIC_Write_Complex_Integer_Mul(int fid, const char* groupname, int num, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Complex_Real_Mul(int fid, const char* groupname, int num, const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_Complex_String_Mul(int fid, const char* groupname, int num, const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, int length, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, int length, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_Complex_FunctionalWithName_String_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, const char* value);

#ifdef __cplusplus
}
#endif

#endif // IRICLIB_NOT_WITHBASEID_H
