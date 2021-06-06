#include "error_macros.h"
#include "h5cgnsgridcoordinates.h"
#include "h5cgnszone.h"
#include "iriclib_errorcodes.h"
#include "iriclib_sol_gridcoord.h"
#include "vectorutil.h"

#include "internal/iric_util.h"

using namespace iRICLib;

int cg_iRIC_Read_Sol_Grid2d_Coords_WithGridId_Mul(int fid, int gid, int step, double* x_arr, double* y_arr)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solread(fid, gid, step, &zone, "cg_iRIC_Read_Sol_Grid2d_Coords_WithGridId_Mul");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec;

	ier = zone->gridCoordinatesForSolution()->readCoordinatesX(&xvec);
	RETURN_IF_ERR;
	ier = zone->gridCoordinatesForSolution()->readCoordinatesY(&yvec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Grid3d_Coords_WithGridId_Mul(int fid, int gid, int step, double* x_arr, double* y_arr, double* z_arr)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solread(fid, gid, step, &zone, "cg_iRIC_Read_Sol_Grid3d_Coords_WithGridId_Mul");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec, zvec;

	ier = zone->gridCoordinatesForSolution()->readCoordinatesX(&xvec);
	RETURN_IF_ERR;
	ier = zone->gridCoordinatesForSolution()->readCoordinatesY(&yvec);
	RETURN_IF_ERR;
	ier = zone->gridCoordinatesForSolution()->readCoordinatesZ(&zvec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);
	_vectorToPointerT(zvec, z_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Grid2d_Coords_WithGridId_Mul(int fid, int gid, double *x_arr, double *y_arr)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solwrite(fid, gid, &zone, "cg_iRIC_Write_Sol_Grid2d_Coords_WithGridId_Mul");
	RETURN_IF_ERR;

	int count = zone->nodeCount();
	std::vector<double> xvec(count), yvec(count);

	_pointerToVectorT(x_arr, &xvec);
	_pointerToVectorT(y_arr, &yvec);

	ier = zone->gridCoordinatesForSolution()->writeCoordinatesX(xvec);
	RETURN_IF_ERR;
	ier = zone->gridCoordinatesForSolution()->writeCoordinatesY(yvec);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_GridCoord3d_WithGridId_Mul(int fid, int gid, double *x_arr, double *y_arr, double *z_arr)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solwrite(fid, gid, &zone, "cg_iRIC_Write_Sol_GridCoord3d_WithGridId_Mul");
	RETURN_IF_ERR;

	int count = zone->nodeCount();
	std::vector<double> xvec(count), yvec(count), zvec(count);

	_pointerToVectorT(x_arr, &xvec);
	_pointerToVectorT(y_arr, &yvec);
	_pointerToVectorT(z_arr, &zvec);

	ier = zone->gridCoordinatesForSolution()->writeCoordinatesX(xvec);
	RETURN_IF_ERR;
	ier = zone->gridCoordinatesForSolution()->writeCoordinatesY(yvec);
	RETURN_IF_ERR;
	ier = zone->gridCoordinatesForSolution()->writeCoordinatesZ(zvec);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
