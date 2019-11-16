#include "error_macros.h"
#include "iriclib.h"
#include "iriclib_errorcodes.h"

// from iriclib_complex.h
int cg_iRIC_Read_Complex_Count_Mul(int fid, const char* groupname, int* num)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_Count_WithBaseId_Mul(fid, bid, groupname, num);
}

int cg_iRIC_Read_Complex_Integer_Mul(int fid, const char* groupname, int num, const char* name, int* value)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_Integer_WithBaseId_Mul(fid, bid, groupname, num, name, value);
}

int cg_iRIC_Read_Complex_Real_Mul(int fid, const char* groupname, int num, const char* name, double* value)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_Real_WithBaseId_Mul(fid, bid, groupname, num, name, value);
}

int cg_iRIC_Read_Complex_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, float* value)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_RealSingle_WithBaseId_Mul(fid, bid, groupname, num, name, value);
}

int cg_iRIC_Read_Complex_StringLen_Mul(int fid, const char* groupname, int num, const char* name, int* length)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_StringLen_WithBaseId_Mul(fid, bid, groupname, num, name, length);
}

int cg_iRIC_Read_Complex_String_Mul(int fid, const char* groupname, int num, const char* name, char* strvalue)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_String_WithBaseId_Mul(fid, bid, groupname, num, name, strvalue);
}

int cg_iRIC_Read_Complex_FunctionalSize_Mul(int fid, const char* groupname, int num, const char* name, int* size)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_FunctionalSize_WithBaseId_Mul(fid, bid, groupname, num, name, size);
}

int cg_iRIC_Read_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, double* x_arr, double* y_arr)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_Functional_WithBaseId_Mul(fid, bid, groupname, num, name, x_arr, y_arr);
}

int cg_iRIC_Read_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, double* v_arr)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId_Mul(fid, bid, groupname, num, name, paramname, v_arr);
}

int cg_iRIC_Read_Complex_Functional_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, float* x_arr, float* y_arr)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_Functional_RealSingle_WithBaseId_Mul(fid, bid, groupname, num, name, x_arr, y_arr);
}

int cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, float* v_arr)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_WithBaseId_Mul(fid, bid, groupname, num, name, paramname, v_arr);
}

int cg_iRIC_Read_Complex_FunctionalWithName_StringLen_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, int* length)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_FunctionalWithName_StringLen_WithBaseId_Mul(fid, bid, groupname, num, name, paramname, length);
}

int cg_iRIC_Read_Complex_FunctionalWithName_String_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue)
{
  int bid = 1;

  return cg_iRIC_Read_Complex_FunctionalWithName_String_WithBaseId_Mul(fid, bid, groupname, num, name, paramname, strvalue);
}

int cg_iRIC_Clear_Complex_Mul(int fid)
{
  int bid = 1;

  return cg_iRIC_Clear_Complex_WithBaseId_Mul(fid, bid);
}

int cg_iRIC_Write_Complex_Integer_Mul(int fid, const char* groupname, int num, const char* name, int value)
{
  int bid = 1;

  return cg_iRIC_Write_Complex_Integer_WithBaseId_Mul(fid, bid, groupname, num, name, value);
}

int cg_iRIC_Write_Complex_Real_Mul(int fid, const char* groupname, int num, const char* name, double value)
{
  int bid = 1;

  return cg_iRIC_Write_Complex_Real_WithBaseId_Mul(fid, bid, groupname, num, name, value);
}

int cg_iRIC_Write_Complex_String_Mul(int fid, const char* groupname, int num, const char* name, const char* value)
{
  int bid = 1;

  return cg_iRIC_Write_Complex_String_WithBaseId_Mul(fid, bid, groupname, num, name, value);
}

int cg_iRIC_Write_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, int length, double* x_arr, double* y_arr)
{
  int bid = 1;

  return cg_iRIC_Write_Complex_Functional_WithBaseId_Mul(fid, bid, groupname, num, name, length, x_arr, y_arr);
}

int cg_iRIC_Write_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, int length, double* v_arr)
{
  int bid = 1;

  return cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId_Mul(fid, bid, groupname, num, name, paramname, length, v_arr);
}

int cg_iRIC_Write_Complex_FunctionalWithName_String_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, const char* value)
{
  int bid = 1;

  return cg_iRIC_Write_Complex_FunctionalWithName_String_WithBaseId_Mul(fid, bid, groupname, num, name, paramname, value);
}


