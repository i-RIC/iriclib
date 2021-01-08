#include "iricsolverlib_cell2d.h"
#include "iricsolverlib_grid2d.h"
#include "iricsolverlib_point2d.h"
#include "iricsolverlib_rect2d.h"
#include "private/iricsolverlib_cell2d_impl.h"

using namespace iRICSolverLib;

Cell2D::Impl::Impl(Grid2D* const grid) :
	m_grid (grid)
{}

// public interfaces

Cell2D::Cell2D(Grid2D* const grid) :
	impl (new Impl(grid))
{}

Cell2D::~Cell2D()
{
	delete impl;
}

int Cell2D::nodeCount() const
{
	return static_cast<int> (impl->m_nodeIds.size());
}

size_t Cell2D::nodeId(int id) const
{
	return impl->m_nodeIds.at(id - 1) + 1;
}

Point2D Cell2D::node(int id) const
{
	return impl->m_grid->node(nodeId(id));
}

Rect2D Cell2D::boundingRect() const
{
	double xmin, xmax, ymin, ymax;
	for (size_t i = 0; i < nodeCount(); ++i) {
		Point2D p = node(i + 1);
		if (i == 0 || xmin > p.x()) {xmin = p.x();}
		if (i == 0 || xmax < p.x()) {xmax = p.x();}
		if (i == 0 || ymin > p.y()) {ymin = p.y();}
		if (i == 0 || ymax < p.y()) {ymax = p.y();}
	}
	return Rect2D(xmin, xmax, ymin, ymax);
}

void Cell2D::addNode(size_t id)
{
	impl->m_nodeIds.push_back(id - 1);
}
