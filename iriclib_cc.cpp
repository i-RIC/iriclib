#include "error_macros.h"
#include "iriclib_cc.h"
#include "iriclib_errorcodes.h"
#include "h5cgnsbase.h"
#include "h5cgnsconditiongroup.h"
#include "h5cgnsfile.h"

#include "internal/iric_h5cgnsfiles.h"

using namespace iRICLib;

int cg_iRIC_Read_Integer_Mul(int fid, const char* name, int* value)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->readIntegerValue(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Real_Mul(int fid, const char* name, double* value)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->readRealValueAsDouble(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_RealSingle_Mul(int fid, const char* name, float* value)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->readRealValueAsFloat(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_StringLen_Mul(int fid, const char* name, int* length)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->readStringLen(name, length);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_String_Mul(int fid, const char* name, char* strvalue)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;
	ier = file->ccBase()->ccGroup()->readString(name, strvalue);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_FunctionalSize_Mul(int fid, const char* name, int* size)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->readFunctionalSize(name, size);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Functional_Mul(int fid, const char* name, double* x_arr, double* y_arr)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->readFunctional(name, x_arr, y_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, double* v_arr)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->readFunctionalWithName(name, paramname, v_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Functional_RealSingle_Mul(int fid, const char* name, float* x_arr, float* y_arr)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;
	ier = file->ccBase()->ccGroup()->readFunctional(name, x_arr, y_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_FunctionalWithName_RealSingle_Mul(int fid, const char* name, const char* paramname, float* v_arr)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;
	ier = file->ccBase()->ccGroup()->readFunctionalWithName(name, paramname, v_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_FunctionalWithName_String_Mul(int fid, const char* name, const char* paramname, char* strvalue)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;
	ier = file->ccBase()->ccGroup()->readFunctionalWithNameString(name, paramname, strvalue);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_FunctionalWithName_StringLen_Mul(int fid, const char* name, const char* paramname, int* length)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->readFunctionalWithNameStringLen(name, paramname, length);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Integer_Mul(int fid, const char* name, int value)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->writeIntegerValue(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Real_Mul(int fid, const char* name, double value)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->writeRealValue(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_String_Mul(int fid, const char* name, const char* value)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->writeString(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Functional_Mul(int fid, const char* name, int length, double* x_arr, double* y_arr)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->writeFunctional(name, length, x_arr, y_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, int length, double* v_arr)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->writeFunctionalWithName(name, paramname, length, v_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_FunctionalWithName_String_Mul(int fid, const char* name, const char* paramname, const char* value)
{
	H5CgnsFile* file;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	ier = file->ccBase()->ccGroup()->writeFunctionalWithNameString(name, paramname, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
