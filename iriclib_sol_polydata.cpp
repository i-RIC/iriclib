#include "error_macros.h"
#include "h5cgnspolydatasolution.h"
#include "h5cgnszone.h"
#include "iriclib_errorcodes.h"
#include "iriclib_sol_polydata.h"
#include "vectorutil.h"

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

int cg_iRIC_Read_Sol_PolyData_DataCount_WithGridId_Mul(int fid, int gid, int step, const char* groupname, int* count)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_DataCount_Mul");
	RETURN_IF_ERR;

	ier = solution->dataCount(groupname, count);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_CoordinateCount_WithGridId_Mul(int fid, int gid, int step, const char* groupname, int* count)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_CoordinateCount_Mul");
	RETURN_IF_ERR;

	ier = solution->coordinatesCount(groupname, count);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, double* x_arr, double* y_arr)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_Pos2d_Mul");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec;
	ier = solution->readCoordinatesX(groupname, &xvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesY(groupname, &yvec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_Type_WithGridId_Mul(int fid, int gid, int step, const char* groupname, int* v_arr)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_Type_Mul");
	RETURN_IF_ERR;

	std::vector<int> buffer;
	ier = solution->readTypes(groupname, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_Real_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, double* v_arr)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_Real_Mul");
	RETURN_IF_ERR;

	std::vector<double> buffer;
	ier = solution->readValue(groupname, name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_PolyData_Integer_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, int* v_arr)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_PolyData_WithGridId_Integer_Mul");
	RETURN_IF_ERR;

	std::vector<int> buffer;
	ier = solution->readValue(groupname, name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_GroupBegin_WithGridId_Mul(int fid, int gid, const char* name)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_GroupBegin_Mul");
	RETURN_IF_ERR;

	solution->writeBegin(name);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_GroupEnd_WithGridId_Mul(int fid, int gid)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_GroupEnd_Mul");
	RETURN_IF_ERR;

	ier = solution->writeEnd();
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId_Mul(int fid, int gid, int numPoints, double* x_arr, double* y_arr)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_Polygon_Mul");
	RETURN_IF_ERR;

	std::vector<double> xvec(numPoints), yvec(numPoints);

	_pointerToVectorT(x_arr, &xvec);
	_pointerToVectorT(y_arr, &yvec);

	solution->writePolygon(xvec, yvec);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId_Mul(int fid, int gid, int numPoints, double* x_arr, double* y_arr)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_Polyline_Mul");
	RETURN_IF_ERR;

	std::vector<double> xvec(numPoints), yvec(numPoints);

	_pointerToVectorT(x_arr, &xvec);
	_pointerToVectorT(y_arr, &yvec);

	solution->writePolyline(xvec, yvec);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_Integer_WithGridId_Mul(int fid, int gid, const char* name, int value)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_Integer_Mul");
	RETURN_IF_ERR;

	solution->writeValue(name, value);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_PolyData_Real_WithGridId_Mul(int fid, int gid, const char* name, double value)
{
	H5CgnsPolyDataSolution* solution = nullptr;
	int ier = getPolyDataSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_PolyData_Real_Mul");
	RETURN_IF_ERR;

	solution->writeValue(name, value);

	return IRIC_NO_ERROR;
}
