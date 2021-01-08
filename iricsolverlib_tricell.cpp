#include "iricsolverlib_tricell.h"
#include "iricsolverlib_point2d.h"
#include "iricsolverlib_rect2d.h"

#include <cmath>
#include <vector>

using namespace iRICSolverLib;

namespace {

const double INSIDE_DELTA = 1.0E-8;

} // namespace

TriCell::TriCell(size_t id1, size_t id2, size_t id3, Grid2D* const grid) :
	Cell2D(grid)
{
	addNode(id1);
	addNode(id2);
	addNode(id3);
}

TriCell::~TriCell()
{}

bool TriCell::interpolate(const Point2D& point, double* weight) const
{
	if (! boundingRect().contains(point)) {return false;}

	double s, t, u;
	calcSTU(point, node(1), node(2), node(3), &s, &t, &u);

	if (s < - INSIDE_DELTA || t < - INSIDE_DELTA || u < - INSIDE_DELTA) {
		return false;
	}

	*(weight)     = s;
	*(weight + 1) = t;
	*(weight + 2) = u;
	return true;
}

double TriCell::area() const
{
	return calcArea(node(1), node(2), node(3));
}

void TriCell::calcSTU(const Point2D& point, const Point2D& node0, const Point2D& node1,const Point2D& node2, double* s, double* t, double* u)
{
	Point2D p = point - node0;
	Point2D p1 = node1 - node0;
	Point2D p2 = node2 - node0;

	double m = p1.x() * p2.y() - p1.y() * p2.x();
	*t = (p.x() * p2.y() - p.y() * p2.x()) / m;
	*u = - (p.x() * p1.y() - p.y() * p1.x()) / m;
	*s = (1 - *t - *u);
}

double TriCell::calcArea(const Point2D& p1, const Point2D& p2, const Point2D& p3)
{
	return 0.5 * std::fabs((p2.x() - p1.x()) * (p3.y() - p1.y()) - (p2.y() - p1.y()) * (p3.x() - p1.x()));
}
