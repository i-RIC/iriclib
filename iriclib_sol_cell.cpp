#include "error_macros.h"
#include "h5cgnsflowsolution.h"
#include "h5cgnszone.h"
#include "iriclib_errorcodes.h"
#include "iriclib_sol_cell.h"
#include "vectorutil.h"

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

	ier = zone->cellSolution()->readValue(name, &buffer);
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

	std::vector<V> buffer(zone->cellCount());

	_pointerToVectorT(v_arr, &buffer);

	ier = zone->cellSolution()->writeValue(name, buffer);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Sol_Cell_Integer_WithGridId_Mul(int fid, int gid, int step, const char* name, int* v_arr)
{
	return readSolutionT(fid, gid, step, name, v_arr, "cg_iRIC_Read_Sol_Integer_WithGridId_Mul");
}

int cg_iRIC_Read_Sol_Cell_Real_WithGridId_Mul(int fid, int gid, int step, const char* name, double* v_arr)
{
	return readSolutionT(fid, gid, step, name, v_arr, "cg_iRIC_Read_Sol_Real_WithGridId_Mul");
}

int cg_iRIC_Write_Sol_Cell_Integer_WithGridId_Mul(int fid, int gid, const char* name, int* v_arr)
{
	return writeSolutionT(fid, gid, name, v_arr, "cg_iRIC_Write_Sol_Integer_WithGridId_Mul");
}

int cg_iRIC_Write_Sol_Cell_Real_WithGridId_Mul(int fid, int gid, const char* name, double* v_arr)
{
	return writeSolutionT(fid, gid, name, v_arr, "cg_iRIC_Write_Sol_Real_WithGridId_Mul");
}
