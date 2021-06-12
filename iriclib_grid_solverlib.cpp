#include "error_macros.h"
#include "iriclib_errorcodes.h"
#include "iriclib_grid_solverlib.h"

#include "iricsolverlib_cell2d.h"
#include "iricsolverlib_grid2d.h"
#include "iricsolverlib_point2d.h"
#include "iricsolverlib_rect2d.h"

#include "internal/iric_logger.h"
#include "internal/iric_outputerror.h"

#include <sstream>
#include <vector>

static std::vector<iRICSolverLib::Grid2D*> grid2ds;

using namespace iRICLib;
using namespace iRICSolverLib;

namespace {

int _getGrid(int grid_handle, Grid2D** grid, const std::string& funcName)
{
	std::ostringstream ss;
	ss << "In " << funcName << ", wrong grid handle passed.";

	*grid = nullptr;

	if (static_cast<size_t> (grid_handle) > grid2ds.size()) {
		std::ostringstream ss;
		ss << "In " << funcName << ", wrong grid handle passed.";
		_iric_logger_error(ss.str());
		return IRIC_WRONG_POINTER;
	}

	*grid = grid2ds.at(grid_handle - 1);
	if (*grid == nullptr) {
		std::ostringstream ss;
		ss << "In " << funcName << ", wrong grid handle passed.";
		_iric_logger_error(ss.str());
		return IRIC_WRONG_POINTER;
	}

	return IRIC_NO_ERROR;
}

int _getGridCell(Grid2D* grid, int cellId, Cell2D** cell, const std::string& funcName)
{
	*cell = nullptr;

	int cellCount = grid->cellCount();
	if (cellId < 1) {
		std::ostringstream ss;
		ss << "In " << funcName << ", wrong cellId passed. cellId should be positive value.";
		_iric_logger_error(ss.str());
	}
	if (cellId > cellCount) {
		std::ostringstream ss;
		ss << "In " << funcName << ", wrong cellId passed. cellId should be no more than " << cellCount << ".";
		_iric_logger_error(ss.str());
	}

	*cell = grid->cell(cellId);

	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Grid2d_Open_WithGridId(int fid, int gid, int* grid_handle)
{
	auto grid = new Grid2D();
	grid->load(fid, gid);
	grid2ds.push_back(grid);

	*grid_handle = static_cast<int> (grid2ds.size());

	return 0;
}

int cg_iRIC_Read_Sol_Grid2d_Open_WithGridId(int fid, int gid, int solid, int* grid_handle)
{
	auto grid = new Grid2D();
	grid->load(fid, gid, solid);
	grid2ds.push_back(grid);

	*grid_handle = static_cast<int> (grid2ds.size());

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Grid2d_Close(int grid_handle)
{
	if (static_cast<size_t> (grid_handle) > grid2ds.size()) {
		_iric_logger_error("In cg_iRIC_Read_Grid2d_Close, wrong grid_handle passed");
		return IRIC_WRONG_POINTER;
	}

	delete grid2ds[grid_handle - 1];
	grid2ds[grid_handle - 1] = nullptr;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Grid2d_CellArea(int grid_handle, int cellId, double* area)
{
	Grid2D* grid;
	int ier = _getGrid(grid_handle, &grid, "cg_iRIC_Read_Grid2d_CellArea");
	RETURN_IF_ERR;

	Cell2D* cell;
	ier = _getGridCell(grid, cellId, &cell, "cg_iRIC_Read_Grid2d_CellArea");
	RETURN_IF_ERR;

	*area = cell->area();

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Grid2d_FindCell(int grid_handle, double x, double y, int* cellId)
{
	Grid2D* grid;
	int ier = _getGrid(grid_handle, &grid, "cg_iRIC_Read_Grid2d_CellArea");
	RETURN_IF_ERR;

	bool success = grid->findCell(Point2D(x, y), cellId);
	if (! success) {
		return IRIC_DATA_NOT_FOUND;
	}

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Grid2d_CellNodeCount(int grid_handle, int cellId, int* count)
{
	Grid2D* grid;
	int ier = _getGrid(grid_handle, &grid, "cg_iRIC_Read_Grid2d_Interpolate");
	RETURN_IF_ERR;

	Cell2D* cell;
	ier = _getGridCell(grid, cellId, &cell, "cg_iRIC_Read_Grid2d_CellArea");
	RETURN_IF_ERR;

	*count = cell->nodeCount();

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Grid2d_Interpolate(int grid_handle, double x, double y, int* ok, int* count, int* nodeids_arr, double* weights_arr)
{
	Grid2D* grid;
	int ier = _getGrid(grid_handle, &grid, "cg_iRIC_Read_Grid2d_Interpolate");
	RETURN_IF_ERR;

	*ok = 0;
	bool success = grid->interpolate(Point2D(x, y), count, nodeids_arr, weights_arr);
	if (success) {
		*ok = 1;
	}
	return 0;
}

int cg_iRIC_Read_Grid2d_InterpolateWithCell(int grid_handle, double x, double y, int cellId, int* nodeids_arr, double* weights_arr)
{
	Grid2D* grid;
	int ier = _getGrid(grid_handle, &grid, "cg_iRIC_Read_Grid2d_InterpolateWithCell");
	RETURN_IF_ERR;

	Cell2D* cell;
	ier = _getGridCell(grid, cellId, &cell, "cg_iRIC_Read_Grid2d_InterpolateWithCell");
	RETURN_IF_ERR;

	for (int i = 0; i < cell->nodeCount(); ++i) {
		*(nodeids_arr + i) = static_cast<int> (cell->nodeId(i + 1));
	}

	bool success = cell->interpolate(Point2D(x, y), weights_arr);
	if (! success) {return IRIC_DATA_NOT_FOUND;}

	return IRIC_NO_ERROR;
}
