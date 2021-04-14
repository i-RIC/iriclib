#ifndef IRICSOLVERLIB_QUADCELL_H
#define IRICSOLVERLIB_QUADCELL_H

#include "iricsolverlib_api.h"
#include "iricsolverlib_cell2d.h"

namespace iRICSolverLib {

class IRICSOLVERLIB_API QuadCell : public Cell2D
{
public:
	QuadCell(size_t id1, size_t id2, size_t id3, size_t id4, Grid2D* const grid);
	~QuadCell();

	bool interpolate(const Point2D& point, double* weight) const;
	double area() const;
};

} // iRICSolverLib

#endif // IRICSOLVERLIB_QUADCELL_H
