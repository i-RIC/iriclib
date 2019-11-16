#ifndef IRICLIB_CC_H
#define IRICLIB_CC_H

#include "iriclib_global.h"

#ifdef __cplusplus
extern "C" {
#endif

int IRICLIBDLL cg_iRIC_Read_Integer_Mul(int fid, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_Real_Mul(int fid, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_RealSingle_Mul(int fid, const char* name, float* value);
int IRICLIBDLL cg_iRIC_Read_StringLen_Mul(int fid, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_String_Mul(int fid, const char* name, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_FunctionalSize_Mul(int fid, const char* name, int* size);
int IRICLIBDLL cg_iRIC_Read_Functional_Mul(int fid, const char* name, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, double* v_arr);
int IRICLIBDLL cg_iRIC_Read_Functional_RealSingle_Mul(int fid, const char* name, float* x_arr, float* y_arr);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_RealSingle_Mul(int fid, const char* name, const char* paramname, float* v_arr);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_String_Mul(int fid, const char* name, const char* paramname, char* strvalue);
int IRICLIBDLL cg_iRIC_Read_FunctionalWithName_StringLen_Mul(int fid, const char* name, const char* paramname, int* length);

int IRICLIBDLL cg_iRIC_Write_Integer_Mul(int fid, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Real_Mul(int fid, const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_String_Mul(int fid, const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_Functional_Mul(int fid, const char* name, int length, double* x_arr, double* y_arr);
int IRICLIBDLL cg_iRIC_Write_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, int length, double* v_arr);
int IRICLIBDLL cg_iRIC_Write_FunctionalWithName_String_Mul(int fid, const char* name, const char* paramname, const char* value);

#ifdef __cplusplus
}
#endif

#endif // IRICLIB_CC_H
