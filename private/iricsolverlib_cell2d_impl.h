#ifndef IRICSOLVERLIB_CELL2D_IMPL_H
#define IRICSOLVERLIB_CELL2D_IMPL_H

#include "../iricsolverlib_cell2d.h"

#include <vector>

namespace iRICSolverLib {

class Cell2D::Impl
{
public:
	Impl(Grid2D* const grid);

	Grid2D* const m_grid;
	std::vector<size_t> m_nodeIds;
};

} // iRICSolverLib

#endif // IRICSOLVERLIB_CELL2D_IMPL_H

