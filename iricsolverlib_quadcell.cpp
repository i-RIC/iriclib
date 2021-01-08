#include "iricsolverlib_point2d.h"
#include "iricsolverlib_quadcell.h"
#include "iricsolverlib_rect2d.h"
#include "iricsolverlib_tricell.h"

#include <vector>

using namespace iRICSolverLib;

namespace {

const double INSIDE_DELTA = 1.0E-8;

bool interpolateTri(const QuadCell& cell, const Point2D& point, int id1, int id2, int id3, double* weights)
{
	double s, t, u;
	TriCell::calcSTU(point, cell.node(id1), cell.node(id2), cell.node(id3), &s, &t, &u);

	if (s < - INSIDE_DELTA || t < - INSIDE_DELTA || u < - INSIDE_DELTA) {
		return false;
	}

	*(weights)     = s;
	*(weights + 1) = t;
	*(weights + 2) = u;
	return true;
}

} // namespace

QuadCell::QuadCell(size_t id1, size_t id2, size_t id3, size_t id4, Grid2D* const grid) :
	Cell2D(grid)
{
	addNode(id1);
	addNode(id2);
	addNode(id3);
	addNode(id4);
}

QuadCell::~QuadCell()
{}

bool QuadCell::interpolate(const Point2D& point, double* weight) const
{
	if (! boundingRect().contains(point)) {return false;}

	double tmpWeights[3];
	bool ok;
	// try triangle with, 0, 1, 2
	ok = interpolateTri(*this, point, 1, 2, 3, &(tmpWeights[0]));
	if (ok) {
		* (weight    ) = tmpWeights[0];
		* (weight + 1) = tmpWeights[1];
		* (weight + 2) = tmpWeights[2];
		* (weight + 3) = 0;
		return true;
	}

	// try triangle with 0, 2, 3
	ok = interpolateTri(*this, point, 1, 3, 4, &(tmpWeights[0]));
	if (ok) {
		* (weight    ) = tmpWeights[0];
		* (weight + 1) = 0;
		* (weight + 2) = tmpWeights[1];
		* (weight + 3) = tmpWeights[2];
		return true;
	}
	return false;
}

double QuadCell::area() const
{
	return TriCell::calcArea(node(1), node(2), node(3)) +
			TriCell::calcArea(node(1), node(3), node(4));
}
