#include "error_macros.h"
#include "iriclib_errorcodes.h"
#include "iriclib.h"
#include "h5cgnsbase.h"
#include "h5cgnsconditiongroup.h"
#include "h5cgnsgridattributes.h"
#include "h5cgnsgridcomplexconditiongroup.h"
#include "h5cgnsgridcomplexconditiontop.h"
#include "h5cgnsfile.h"
#include "vectorutil.h"

#include "internal/iric_h5cgnsfiles.h"
#include "internal/iric_logger.h"
#include "internal/iric_outputerror.h"
#include "internal/iric_util.h"

#include <sstream>

using namespace iRICLib;

namespace {

void outputGroupNotExistsError(const std::string& groupName, const std::string& fname)
{
	std::ostringstream ss;
	ss << "In " << fname << "(), complex grid attribute with groupName " << groupName << " does not exists";
	_iric_logger_error(ss.str());
}

int getGccGroup(int fid, int bid, const char* groupname, H5CgnsGridComplexConditionGroup** group, const std::string& f_name, bool create = false)
{
	H5CgnsFile* file = nullptr;

	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	auto b = file->baseById(bid);
	auto gccTop = b->gccTop();

	if (! gccTop->groupExists(groupname) && ! create) {
		outputGroupNotExistsError(groupname, f_name);
		return IRIC_INVALID_GROUPNAME;
	}
	*group = gccTop->group(groupname);

	return IRIC_NO_ERROR;
}

int getGridAttributes(int fid, int gid, H5CgnsGridAttributes** atts, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;

	int ier = _iric_get_zone(fid, gid, &zone, f_name);
	RETURN_IF_ERR;

	*atts = zone->gridAttributes();

	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Complex_Count_WithBaseId_Mul(int fid, int bid, const char* groupname, int* num)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	*num = gccGroup->itemCount();

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_Integer_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, int* value)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readIntegerValue(name, value);
}

int cg_iRIC_Read_Complex_Real_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, double* value)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readRealValueAsDouble(name, value);
}

int cg_iRIC_Read_Complex_RealSingle_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, float* value)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readRealValueAsFloat(name, value);
}

int cg_iRIC_Read_Complex_StringLen_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, int* length)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readStringLen(name, length);
}

int cg_iRIC_Read_Complex_String_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, char* strvalue)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readString(name, strvalue);
}

int cg_iRIC_Read_Complex_FunctionalSize_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, int* size)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readFunctionalSize(name, size);
}

int cg_iRIC_Read_Complex_Functional_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, double* x_arr, double* y_arr)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readFunctional(name, x_arr, y_arr);
}

int cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, double* v_arr)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readFunctionalWithName(name, paramname, v_arr);
}

int cg_iRIC_Read_Complex_Functional_RealSingle_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, float* x_arr, float* y_arr)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readFunctional(name, x_arr, y_arr);
}

int cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, float* v_arr)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readFunctionalWithName(name, paramname, v_arr);
}

int cg_iRIC_Read_Complex_FunctionalWithName_StringLen_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, int* length)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readFunctionalWithNameStringLen(name, paramname, length);
}

int cg_iRIC_Read_Complex_FunctionalWithName_String_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	return gccGroup->item(num)->readFunctionalWithNameString(name, paramname, strvalue);
}

int cg_iRIC_Read_Grid_Complex_Node_WithGridId_Mul(int fid, int gid, const char* groupname, int* v_arr)
{
	H5CgnsGridAttributes* atts = nullptr;
	int ier = getGridAttributes(fid, gid, &atts, __func__);
	RETURN_IF_ERR;

	std::vector<int> buffer;

	ier = atts->readValue(groupname, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Grid_Complex_Cell_WithGridId_Mul(int fid, int gid, const char* groupname, int* v_arr)
{
	H5CgnsGridAttributes* atts = nullptr;
	int ier = getGridAttributes(fid, gid, &atts, __func__);
	RETURN_IF_ERR;

	std::vector<int> buffer;

	ier = atts->readValue(groupname, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Clear_Complex_WithBaseId_Mul(int fid, int bid)
{
	H5CgnsFile* file = nullptr;

	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	auto b = file->baseById(bid);
	auto gccTop = b->gccTop();

	ier = gccTop->clear();
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Complex_Integer_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, int value)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	return gccGroup->item(num)->writeIntegerValue(name, value);
}

int cg_iRIC_Write_Complex_Real_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, double value)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	return gccGroup->item(num)->writeRealValue(name, value);
}

int cg_iRIC_Write_Complex_String_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* value)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	return gccGroup->item(num)->writeString(name, value);
}

int cg_iRIC_Write_Complex_Functional_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, int length, double* x_arr, double* y_arr)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	return gccGroup->item(num)->writeFunctional(name, length, x_arr, y_arr);
}

int cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, int length, double* v_arr)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	return gccGroup->item(num)->writeFunctionalWithName(name, paramname, length, v_arr);
}

int cg_iRIC_Write_Complex_FunctionalWithName_String_WithBaseId_Mul(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, const char* value)
{
	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	return gccGroup->item(num)->writeFunctionalWithNameString(name, paramname, value);
}

int cg_iRIC_Write_Grid_Complex_Node_WithGridId_Mul(int fid, int gid, const char* groupname, int* v_arr)
{
	H5CgnsGridAttributes* atts = nullptr;
	int ier = getGridAttributes(fid, gid, &atts, __func__);
	RETURN_IF_ERR;

	int nodeCount = atts->zone()->nodeCount();
	std::vector<int> buffer(nodeCount);

	_pointerToVectorT(v_arr, &buffer);

	ier = atts->writeValue(groupname, buffer);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Grid_Complex_Cell_WithGridId_Mul(int fid, int gid, const char *groupname, int* v_arr)
{
	H5CgnsGridAttributes* atts = nullptr;
	int ier = getGridAttributes(fid, gid, &atts, __func__);
	RETURN_IF_ERR;

	int cellCount = atts->zone()->cellCount();
	std::vector<int> buffer(cellCount);

	_pointerToVectorT(v_arr, &buffer);

	ier = atts->writeValue(groupname, buffer);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
