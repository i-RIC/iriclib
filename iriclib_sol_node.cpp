#include "error_macros.h"
#include "h5cgnsflowsolution.h"
#include "h5cgnszone.h"
#include "iriclib_errorcodes.h"
#include "iriclib_sol_node.h"
#include "vectorutil.h"

#include "internal/iric_logger.h"
#include "internal/iric_util.h"

using namespace iRICLib;

namespace {

template <typename V>
int readSolutionT(int fid, int gid, int step, const std::string& name, V* v_arr, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solread(fid, gid, step, &zone, f_name);
	RETURN_IF_ERR;

	std::vector<V> buffer;

	ier = zone->nodeSolution()->readValue(name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	return IRIC_NO_ERROR;
}

template <typename V>
int writeSolutionT(int fid, int gid, const std::string& name, V* v_arr, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solwrite(fid, gid, &zone, f_name);
	RETURN_IF_ERR;

	std::vector<V> buffer(zone->nodeCount());

	_pointerToVectorT(v_arr, &buffer);

	ier = zone->nodeSolution()->writeValue(name, buffer);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Sol_Node_Integer_WithGridId(int fid, int gid, int step, const char* name, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();
	int ier = readSolutionT(fid, gid, step, name, v_arr, "cg_iRIC_Read_Sol_Node_Integer_WithGridId");
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Node_Real_WithGridId(int fid, int gid, int step, const char* name, double* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();
	int ier = readSolutionT(fid, gid, step, name, v_arr, "cg_iRIC_Read_Sol_Node_Real_WithGridId");
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Node_Integer_WithGridId(int fid, int gid, const char* name, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();
	int ier = writeSolutionT(fid, gid, name, v_arr, "cg_iRIC_Write_Sol_Node_Integer_WithGridId");
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Node_Real_WithGridId(int fid, int gid, const char* name, double* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();
	int ier = writeSolutionT(fid, gid, name, v_arr, "cg_iRIC_Write_Sol_Node_Real_WithGridId");
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}
