#include "error_macros.h"
#include "iriclib_errorcodes.h"
#include "iriclib.h"
#include "h5cgnsbase.h"
#include "h5cgnsbaseiterativedata.h"
#include "h5cgnsfile.h"

#include "internal/iric_h5cgnsfiles.h"
#include "internal/iric_logger.h"
#include "internal/iric_outputerror.h"

#include <algorithm>
#include <sstream>

using namespace iRICLib;

#define GET_F \
	H5CgnsFile* file = nullptr;\
	int ier = _iric_h5cgnsfiles_get(fid, &file);\
	RETURN_IF_ERR;

int cg_iRIC_Read_Sol_Count_Mul(int fid, int* count)
{
	GET_F;

	std::vector<double> times;
	std::vector<int> iterations;
	ier = file->ccBase()->biterData()->readTime(&times);
	RETURN_IF_ERR;
	ier = file->ccBase()->biterData()->readIteration(&iterations);
	RETURN_IF_ERR;

	*count = static_cast<int> (std::max(times.size(), iterations.size()));

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Time_Mul(int fid, int step, double* time)
{
	GET_F;

	ier = file->ccBase()->biterData()->readTime(step, time);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Iteration_Mul(int fid, int step, int* index)
{
	GET_F;

	ier = file->ccBase()->biterData()->readIteration(step, index);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_BaseIterative_Integer_Mul(int fid, int step, const char* name, int* value)
{
	GET_F;

	ier = file->ccBase()->biterData()->readValue(step, name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_BaseIterative_Real_Mul(int fid, int step, const char* name, double* value)
{
	GET_F;

	ier = file->ccBase()->biterData()->readValue(step, name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_BaseIterative_StringLen_Mul(int fid, int step, const char* name, int* length)
{
	GET_F;

	std::string value;
	ier = file->ccBase()->biterData()->readValue(step, name, &value);
	RETURN_IF_ERR;

	*length = static_cast<int> (value.length());

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_BaseIterative_String_Mul(int fid, int step, const char* name, char* strvalue)
{
	GET_F;

	std::string value;
	ier = file->ccBase()->biterData()->readValue(step, name, &value);
	RETURN_IF_ERR;

	for (size_t i = 0; i < value.length(); ++i) {
		*(strvalue + i) = *(value.data() + i);
	}
	*(strvalue + value.length()) = '\0';

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Time_Mul(int fid, double time)
{
	GET_F;

	ier = file->solutionWriter()->writeTime(time);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Iteration_Mul(int fid, int index)
{
	GET_F;

	ier = file->solutionWriter()->writeIteration(index);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(int fid, const char* name, int value)
{
	GET_F;

	ier = file->ccBase()->biterData()->writeData(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_BaseIterative_Real_Mul(int fid, const char* name, double value)
{
	GET_F;

	ier = file->ccBase()->biterData()->writeData(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_BaseIterative_String_Mul(int fid, const char* name, const char* value)
{
	GET_F;

	ier = file->ccBase()->biterData()->writeData(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_ErrorCode_Mul(int fid, int errorcode)
{
	GET_F;

	ier = file->ccBase()->writeErrorCode(errorcode);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
