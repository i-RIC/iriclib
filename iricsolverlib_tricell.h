#ifndef IRICSOLVERLIB_TRICELL_H
#define IRICSOLVERLIB_TRICELL_H

#include "iricsolverlib_api.h"
#include "iricsolverlib_cell2d.h"

namespace iRICSolverLib {

class IRICSOLVERLIB_API TriCell : public Cell2D
{
public:
	TriCell(size_t id1, size_t id2, size_t id3, Grid2D* const grid);
	~TriCell();

	bool interpolate(const Point2D& point, double* weight) const;
	double area() const;

	static void calcSTU(const Point2D& point, const Point2D& p1, const Point2D& p2,const Point2D& p3, double* s, double* t, double* u);
	static double calcArea(const Point2D& p1, const Point2D& p2, const Point2D& p3);
};

} // iRICSolverLib

#endif // IRICSOLVERLIB_TRICELL_H
