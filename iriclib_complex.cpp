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

int cg_iRIC_Read_Complex_Count_WithBaseId(int fid, int bid, const char* groupname, int* num)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	*num = gccGroup->itemCount();

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_Integer_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, int* value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readIntegerValue(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_Real_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, double* value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readRealValueAsDouble(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_RealSingle_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, float* value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readRealValueAsFloat(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_StringLen_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, int* length)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readStringLen(name, length);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_String_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, char* strvalue)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readString(name, strvalue);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_FunctionalSize_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, int* size)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readFunctionalSize(name, size);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_Functional_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, double* x_arr, double* y_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readFunctional(name, x_arr, y_arr);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, double* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readFunctionalWithName(name, paramname, v_arr);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_Functional_RealSingle_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, float* x_arr, float* y_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readFunctional(name, x_arr, y_arr);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, float* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readFunctionalWithName(name, paramname, v_arr);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_FunctionalWithName_StringLen_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, int* length)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readFunctionalWithNameStringLen(name, paramname, length);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Complex_FunctionalWithName_String_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->readFunctionalWithNameString(name, paramname, strvalue);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Grid_Complex_Node_WithGridId(int fid, int gid, const char* groupname, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridAttributes* atts = nullptr;
	int ier = getGridAttributes(fid, gid, &atts, __func__);
	RETURN_IF_ERR;

	std::vector<int> buffer;

	ier = atts->readValue(groupname, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Grid_Complex_Cell_WithGridId(int fid, int gid, const char* groupname, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridAttributes* atts = nullptr;
	int ier = getGridAttributes(fid, gid, &atts, __func__);
	RETURN_IF_ERR;

	std::vector<int> buffer;

	ier = atts->readValue(groupname, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Clear_Complex_WithBaseId(int fid, int bid)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsFile* file = nullptr;

	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	auto b = file->baseById(bid);
	auto gccTop = b->gccTop();

	ier = gccTop->clear();
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Complex_Integer_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, int value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->writeIntegerValue(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Complex_Real_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, double value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->writeRealValue(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Complex_String_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->writeString(name, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Complex_Functional_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, int length, double* x_arr, double* y_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->writeFunctional(name, length, x_arr, y_arr);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, int length, double* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->writeFunctionalWithName(name, paramname, length, v_arr);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Complex_FunctionalWithName_String_WithBaseId(int fid, int bid, const char* groupname, int num, const char* name, const char* paramname, const char* value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridComplexConditionGroup* gccGroup = nullptr;
	int ier = getGccGroup(fid, bid, groupname, &gccGroup, __func__, true);
	RETURN_IF_ERR;

	ier = gccGroup->item(num)->writeFunctionalWithNameString(name, paramname, value);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Grid_Complex_Node_WithGridId(int fid, int gid, const char* groupname, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridAttributes* atts = nullptr;
	int ier = getGridAttributes(fid, gid, &atts, __func__);
	RETURN_IF_ERR;

	int nodeCount = atts->zone()->nodeCount();
	std::vector<int> buffer(nodeCount);

	_pointerToVectorT(v_arr, &buffer);

	ier = atts->writeValue(groupname, buffer);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Grid_Complex_Cell_WithGridId(int fid, int gid, const char *groupname, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGridAttributes* atts = nullptr;
	int ier = getGridAttributes(fid, gid, &atts, __func__);
	RETURN_IF_ERR;

	int cellCount = atts->zone()->cellCount();
	std::vector<int> buffer(cellCount);

	_pointerToVectorT(v_arr, &buffer);

	ier = atts->writeValue(groupname, buffer);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}
