#ifndef IRICSOLVERLIB_GRID2D_H
#define IRICSOLVERLIB_GRID2D_H

#include "iricsolverlib_api.h"

#include <stdlib.h>

namespace iRICSolverLib {

class Cell2D;
class Point2D;
class Rect2D;

class IRICSOLVERLIB_API Grid2D
{
public:
	Grid2D();
	~Grid2D();

	void load(int cgnsIn, int baseId, int zoneId, int gridId);

	size_t nodeCount() const;
	Point2D node(size_t nodeId) const;

	size_t cellCount() const;
	Cell2D* cell(size_t cellId) const;

	Rect2D boundingRect() const;

	bool interpolate(const Point2D& point, int *count, size_t* nodeIds, double* weight) const;

	void addNode(const Point2D& p);
	void addNode(double x, double y);

	void addTriCell(size_t id1, size_t id2, size_t id3);
	void addQuadCell(size_t id1, size_t id2, size_t id3, size_t id4);

	void setupBackGrid();

private:
	class Impl;
	Impl* impl;
};

} // iRICSolverLib

#ifdef _DEBUG
	#include "private/iricsolverlib_grid2d_impl.h"
#endif // _DEBUG

#endif // IRICSOLVERLIB_GRID2D_H
