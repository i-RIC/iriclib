#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsbc.h"
#include "h5cgnsconditiongroup.h"
#include "h5cgnsfile.h"
#include "h5cgnszone.h"
#include "h5cgnszonebc.h"
#include "iriclib_errorcodes.h"
#include "iriclib_bc.h"
#include "vectorutil.h"

#include "internal/iric_h5cgnsfiles.h"
#include "internal/iric_logger.h"
#include "internal/iric_outputerror.h"
#include "internal/iric_util.h"

#include <sstream>

using namespace iRICLib;

namespace {

int getZoneBC(int fid, int gid, H5CgnsZoneBc** zoneBc, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone(fid, gid, &zone, f_name);
	RETURN_IF_ERR;

	*zoneBc = zone->zoneBc();
	return IRIC_NO_ERROR;
}

int getBcForRead(int fid, int gid, const std::string& typeName, int num, H5CgnsBc** bc, const std::string& f_name)
{
	H5CgnsZoneBc* zoneBc;
	int ier = getZoneBC(fid, gid, &zoneBc, f_name);
	RETURN_IF_ERR;

	bool exists = zoneBc->bcExists(typeName, num);

	if (! exists) {
		std::ostringstream ss;
		ss << "In getBcForRead(), boundary condition with typeName " << typeName << ", num " << num << " does not exists";
		_iric_logger_error(ss.str());
		return IRIC_BC_NOT_FOUND;
	}

	*bc = zoneBc->bc(typeName, num);
	return IRIC_NO_ERROR;
}

} // namespace

void cg_iRIC_Read_BC_Count_WithGridId(int fid, int gid, const char* type, int* num)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	if (ier != IRIC_NO_ERROR) {return;}

	*num = zoneBc->bcCount(type);
}

int cg_iRIC_Read_BC_IndicesSize_WithGridId(int fid, int gid, const char* type, int num, int* size)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readIndicesSize(size);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_IndicesSize2_WithGridId(int fid, int gid, const char* type, int num, int* size)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readIndicesValueCount(size);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_Indices_WithGridId(int fid, int gid, const char* type, int num, int* idx_arr)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	std::vector<int> buffer;
	ier = bc->readIndices(&buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, idx_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_Integer_WithGridId(int fid, int gid, const char* type, int num, const char* name, int* value)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readIntegerValue(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_Real_WithGridId(int fid, int gid, const char* type, int num, const char* name, double* value)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readRealValueAsDouble(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_RealSingle_WithGridId(int fid, int gid, const char* type, int num, const char* name, float* value)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readRealValueAsFloat(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_StringLen_WithGridId(int fid, int gid, const char* type, int num, const char* name, int* length)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readStringLen(name, length);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_String_WithGridId(int fid, int gid, const char* type, int num, const char* name, char* strvalue)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readString(name, strvalue);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_FunctionalSize_WithGridId(int fid, int gid, const char* type, int num, const char* name, int* size)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readFunctionalSize(name, size);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_Functional_WithGridId(int fid, int gid, const char* type, int num, const char* name, double* x_arr, double* y_arr)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readFunctional(name, x_arr, y_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_FunctionalWithName_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, double* v_arr)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readFunctionalWithName(name, paramname, v_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_Functional_RealSingle_WithGridId(int fid, int gid, const char* type, int num, const char* name, float* x_arr, float* y_arr)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readFunctional(name, x_arr, y_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_FunctionalWithName_RealSingle_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, float* v_arr)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readFunctionalWithName(name, paramname, v_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_FunctionalWithName_StringLen_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, int* length)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readFunctionalWithNameStringLen(name, paramname, length);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_BC_FunctionalWithName_String_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, char* strvalue)
{
	H5CgnsBc* bc = nullptr;
	int ier = getBcForRead(fid, gid, type, num, &bc, __func__);
	RETURN_IF_ERR;

	ier = bc->readFunctionalWithNameString(name, paramname, strvalue);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Clear_BC_WithGridId(int fid, int gid)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	RETURN_IF_ERR;

	ier = zoneBc->clear();
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_BC_Indices_WithGridId(int fid, int gid, const char* type, int num, int length, int* idx_arr)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone(fid, gid, &zone, __func__);
	RETURN_IF_ERR;

	int length2 = length;
	if (zone->type() == H5CgnsZone::Type::Structured) {
		length2 = length * zone->base()->dimension();
	}

	return cg_iRIC_Write_BC_Indices2_WithGridId(fid, gid, type, num, length2, idx_arr);
}

int cg_iRIC_Write_BC_Indices2_WithGridId(int fid, int gid, const char* type, int num, int length, int* idx_arr)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	RETURN_IF_ERR;

	std::vector<int> buffer(length);

	_pointerToVectorT(idx_arr, &buffer);

	H5CgnsBc* bc = zoneBc->bc(type, num);
	ier = bc->writeIndices(buffer);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_BC_Integer_WithGridId(int fid, int gid, const char* type, int num, const char* name, int value)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	RETURN_IF_ERR;

	H5CgnsBc* bc = zoneBc->bc(type, num);
	ier = bc->writeIntegerValue(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_BC_Real_WithGridId(int fid, int gid, const char* type, int num, const char* name, double value)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	RETURN_IF_ERR;

	H5CgnsBc* bc = zoneBc->bc(type, num);
	ier = bc->writeRealValue(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_BC_String_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* value)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	RETURN_IF_ERR;

	H5CgnsBc* bc = zoneBc->bc(type, num);
	ier = bc->writeString(name, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_BC_Functional_WithGridId(int fid, int gid, const char* type, int num, const char* name, int length, double* x_arr, double* y_arr)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	RETURN_IF_ERR;

	H5CgnsBc* bc = zoneBc->bc(type, num);
	ier = bc->writeFunctional(name, length, x_arr, y_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_BC_FunctionalWithName_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, int length, double* v_arr)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	RETURN_IF_ERR;

	H5CgnsBc* bc = zoneBc->bc(type, num);
	ier = bc->writeFunctionalWithName(name, paramname, length, v_arr);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_BC_FunctionalWithName_String_WithGridId(int fid, int gid, const char* type, int num, const char* name, const char* paramname, const char* value)
{
	H5CgnsZoneBc* zoneBc = nullptr;
	int ier = getZoneBC(fid, gid, &zoneBc, __func__);
	RETURN_IF_ERR;

	H5CgnsBc* bc = zoneBc->bc(type, num);
	ier = bc->writeFunctionalWithNameString(name, paramname, value);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
