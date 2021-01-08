#include <vector>
#include "iricsolverlib_cell2d.h"
#include "iricsolverlib_grid2d.h"
#include "iricsolverlib_point2d.h"
#include "iricsolverlib_rect2d.h"

static std::vector<iRICSolverLib::Grid2D*> grid2ds;

using namespace iRICSolverLib;

extern "C" {

int iRIC_Solver_Grid2D_Open(int fin, int baseId, int zoneId, int gridId, int* handle)
{
	Grid2D* grid = new Grid2D();
	grid->load(fin, baseId, zoneId, gridId);
	grid2ds.push_back(grid);
	*handle = static_cast<int> (grid2ds.size());

	return 0;
}

int iRIC_Solver_Grid2D_Read_CellCount(int gridHandle, int* cellCount)
{
	if (static_cast<size_t> (gridHandle) > grid2ds.size()) {return -1;}

	Grid2D* grid = grid2ds.at(gridHandle - 1);
	if (grid == 0) {return -2;}

	*cellCount = grid->cellCount();

	return 0;
}

int iRIC_Solver_Grid2D_Read_CellNodeCount(int gridHandle, int cellId, int* nodeCount)
{
	if (static_cast<size_t> (gridHandle) > grid2ds.size()) {return -1;}

	Grid2D* grid = grid2ds.at(gridHandle - 1);
	if (grid == 0) {return -2;}

	if (cellId < 1) {return -3;}
	if (cellId > grid->cellCount()) {return -3;}

	Cell2D* cell = grid->cell(static_cast<size_t> (cellId));
	*nodeCount = cell->nodeCount();

	return 0;
}

int iRIC_Solver_Grid2D_Read_CellNodeIds(int gridHandle, int cellId, int* nodeIds)
{
	if (static_cast<size_t> (gridHandle) > grid2ds.size()) {return -1;}

	Grid2D* grid = grid2ds.at(gridHandle - 1);
	if (grid == 0) {return -2;}

	if (cellId < 1) {return -3;}
	if (cellId > grid->cellCount()) {return -3;}

	Cell2D* cell = grid->cell(static_cast<size_t> (cellId));
	for (int i = 0; i < cell->nodeCount(); ++i) {
		*(nodeIds + i) = static_cast<int> (cell->nodeId(i + 1));
	}

	return 0;
}

int iRIC_Solver_Grid2D_Read_CellArea(int gridHandle, int cellId, double* area)
{
	if (static_cast<size_t> (gridHandle) > grid2ds.size()) {return -1;}

	Grid2D* grid = grid2ds.at(gridHandle - 1);
	if (grid == 0) {return -2;}

	if (cellId < 1) {return -3;}
	if (cellId > grid->cellCount()) {return -3;}

	Cell2D* cell = grid->cell(static_cast<size_t> (cellId));
	*area = cell->area();

	return 0;
}

int iRIC_Solver_Grid2D_GetRegion(int gridHandle, double* xmin, double* xmax, double* ymin, double* ymax)
{
	if (static_cast<size_t> (gridHandle) > grid2ds.size()) {return -1;}

	Grid2D* grid = grid2ds.at(gridHandle - 1);
	if (grid == 0) {return -2;}

	Rect2D rect = grid->boundingRect();
	*xmin = rect.xMin();
	*xmax = rect.xMax();
	*ymin = rect.yMin();
	*ymax = rect.yMax();

	return 0;
}

int iRIC_Solver_Grid2D_Interpolate(int gridHandle, double x, double y, int* ok, int* count, size_t* nodeids, double* weights)
{
	if (static_cast<size_t> (gridHandle) > grid2ds.size()) {return -1;}

	Grid2D* grid = grid2ds.at(gridHandle - 1);
	if (grid == 0) {return -2;}

	*ok = 0;
	bool success = grid->interpolate(Point2D(x, y), count, nodeids, weights);
	if (success) {
		*ok = 1;
	}
	return 0;
}

int iRIC_Solver_Grid2D_Close(int gridHandle)
{
	if (static_cast<size_t> (gridHandle) > grid2ds.size()) {return -1;}

	delete grid2ds[gridHandle - 1];
	grid2ds[gridHandle - 1] = 0;
	return 0;
}

} // extern "C"
