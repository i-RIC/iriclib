#ifndef IRICSOLVERLIB_GRID2D_IMPL_H
#define IRICSOLVERLIB_GRID2D_IMPL_H

#include "../iricsolverlib_grid2d.h"

#include <vector>

namespace iRICSolverLib {

class Grid2D::Impl
{
public:
	Impl(Grid2D* grid);
	~Impl();
	void loadStructuredGrid(int fn, int baseId, int zoneId, int gridId);
	void loadUnstructuredGrid(int fn, int baseId, int zoneId, int gridId);
	void setupBackGrid();

	size_t structuredIndex(size_t i, size_t j, int* size) const;

private:
	void insertTriangleCells(int fn, int baseId, int zoneId, int secId);
	void insertQuadCells(int fn, int baseId, int zoneId, int secId);

public:
	Grid2D* m_grid;
	std::vector<Point2D> m_nodes;
	std::vector<Cell2D*> m_cells;

	std::vector<double> m_backGridX;
	std::vector<double> m_backGridY;

	std::vector< std::vector<Cell2D*> > m_backGridCells;
};

} // iRICSolverLib

#endif // IRICSOLVERLIB_GRID2D_IMPL_H
