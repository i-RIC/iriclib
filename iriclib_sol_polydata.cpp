#include "error_macros.h"
#include "h5cgnspolydatasolution.h"
#include "h5cgnszone.h"
#include "iriclib_errorcodes.h"
#include "iriclib_sol_polydata.h"
#include "vectorutil.h"

#include "internal/iric_logger.h"
#include "internal/iric_util.h"

using namespace iRICLib;

namespace {

int getPolyDataSolutionForRead(int fid, int gid, int step, H5CgnsPolyDataSolution** solution, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solread(fid, gid, step, &zone, f_name);
	RETURN_IF_ERR;

	*solution = zone->polyDataSolution();
	return IRIC_NO_ERROR;
}

int getPolyDataSolutionForWrite(int fid, int gid, H5CgnsPolyDataSolution** solution, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solwrite(fid, gid, &zone, f_name);
	RETURN_IF_ERR;

	*solution = zone->polyDataSolution();
	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Sol_PolyData_DataCount_WithGridId(int fid, int gid, int step, const char* groupname, int* count)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_DataCount");
	RETURN_IF_ERR;

	ier = solution->dataCount(groupname, count);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_CoordinateCount_WithGridId(int fid, int gid, int step, const char* groupname, int* count)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_CoordinateCount");
	RETURN_IF_ERR;

	ier = solution->coordinatesCount(groupname, count);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(int fid, int gid, int step, const char* groupname, double* x_arr, double* y_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_Pos2d");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec;
	ier = solution->readCoordinatesX(groupname, &xvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesY(groupname, &yvec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_Type_WithGridId(int fid, int gid, int step, const char* groupname, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_Type");
	RETURN_IF_ERR;

	std::vector<int> buffer;
	ier = solution->readTypes(groupname, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_Real_WithGridId(int fid, int gid, int step, const char* groupname, const char* name, double* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_Real");
	RETURN_IF_ERR;

	std::vector<double> buffer;
	ier = solution->readValue(groupname, name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(int fid, int gid, int step, const char* groupname, const char* name, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_Integer");
	RETURN_IF_ERR;

	std::vector<int> buffer;
	ier = solution->readValue(groupname, name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_GroupBegin_WithGridId(int fid, int gid, const char* name)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_GroupBegin");
	RETURN_IF_ERR;

	solution->writeBegin(name);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_GroupEnd_WithGridId(int fid, int gid)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_GroupEnd");
	RETURN_IF_ERR;

	ier = solution->writeEnd();
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(int fid, int gid, int numPoints, double* x_arr, double* y_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_Polygon");
	RETURN_IF_ERR;

	std::vector<double> xvec(numPoints), yvec(numPoints);

	_pointerToVectorT(x_arr, &xvec);
	_pointerToVectorT(y_arr, &yvec);

	solution->writePolygon(xvec, yvec);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(int fid, int gid, int numPoints, double* x_arr, double* y_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_Polyline");
	RETURN_IF_ERR;

	std::vector<double> xvec(numPoints), yvec(numPoints);

	_pointerToVectorT(x_arr, &xvec);
	_pointerToVectorT(y_arr, &yvec);

	solution->writePolyline(xvec, yvec);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_Integer_WithGridId(int fid, int gid, const char* name, int value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_Integer");
	RETURN_IF_ERR;

	solution->writeValue(name, value);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_Real_WithGridId(int fid, int gid, const char* name, double value)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_Real");
	RETURN_IF_ERR;

	solution->writeValue(name, value);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}
