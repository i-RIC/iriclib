#ifndef IRICLIB_SOLUTION_H
#define IRICLIB_SOLUTION_H

#include "iriclib_global.h"

#ifdef __cplusplus
extern "C" {
#endif

int IRICLIBDLL cg_iRIC_Read_Sol_Count_Mul(int fid, int* count);
int IRICLIBDLL cg_iRIC_Read_Sol_Time_Mul(int fid, int step, double* time);
int IRICLIBDLL cg_iRIC_Read_Sol_Iteration_Mul(int fid, int step, int* index);
int IRICLIBDLL cg_iRIC_Read_Sol_BaseIterative_Integer_Mul(int fid, int step, const char* name, int* value);
int IRICLIBDLL cg_iRIC_Read_Sol_BaseIterative_Real_Mul(int fid, int step, const char* name, double* value);
int IRICLIBDLL cg_iRIC_Read_Sol_BaseIterative_StringLen_Mul(int fid, int step, const char* name, int* length);
int IRICLIBDLL cg_iRIC_Read_Sol_BaseIterative_String_Mul(int fid, int step, const char* name, char* strvalue);

int IRICLIBDLL cg_iRIC_Write_Sol_Time_Mul(int fid, double time);
int IRICLIBDLL cg_iRIC_Write_Sol_Iteration_Mul(int fid, int index);
int IRICLIBDLL cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(int fid, const char* name, int value);
int IRICLIBDLL cg_iRIC_Write_Sol_BaseIterative_Real_Mul(int fid, const char* name, double value);
int IRICLIBDLL cg_iRIC_Write_Sol_BaseIterative_String_Mul(int fid, const char* name, const char* value);
int IRICLIBDLL cg_iRIC_Write_ErrorCode_Mul(int fid, int errorcode);

#ifdef __cplusplus
}
#endif

#endif // IRICLIB_SOLUTION_H
