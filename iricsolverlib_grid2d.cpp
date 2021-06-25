#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsfile.h"
#include "h5cgnsfilesolutionreader.h"
#include "h5cgnsgridcoordinates.h"
#include "h5cgnszone.h"

#include "iricsolverlib_cell2d.h"
#include "iricsolverlib_grid2d.h"
#include "iricsolverlib_point2d.h"
#include "iricsolverlib_quadcell.h"
#include "iricsolverlib_rect2d.h"
#include "iricsolverlib_tricell.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_util.h"

#include "private/iricsolverlib_grid2d_impl.h"

#include <algorithm>
#include <cmath>
#include <vector>

using namespace iRICLib;
using namespace iRICSolverLib;

namespace {

} // namespace

Grid2D::Impl::Impl(Grid2D* grid) :
	m_grid (grid)
{}

Grid2D::Impl::~Impl()
{
	for (size_t i = 0; i < m_cells.size(); ++i) {
		delete m_cells.at(i);
	}
}

int Grid2D::Impl::loadNodes(iRICLib::H5CgnsGridCoordinates* coords)
{
	std::vector<double> xvec, yvec;
	int ier = 0;
	ier = coords->readCoordinatesX(&xvec);
	RETURN_IF_ERR;

	ier = coords->readCoordinatesY(&yvec);
	RETURN_IF_ERR;

	m_nodes.clear();
	m_nodes.reserve(xvec.size());

	for (size_t i = 0; i < xvec.size(); ++i) {
		double x = xvec.at(i);
		double y = yvec.at(i);

		m_nodes.push_back(Point2D(x, y));
	}
	return IRIC_NO_ERROR;
}

int Grid2D::Impl::loadCells(const iRICLib::H5CgnsZone& zone)
{
	if (zone.type() == iRICLib::H5CgnsZone::Type::Structured) {
		return loadStructuredGrid(zone);
	} else if (zone.type() == iRICLib::H5CgnsZone::Type::Unstructured) {
		return loadUnstructuredGrid(zone);
	}
}

int Grid2D::Impl::loadStructuredGrid(const iRICLib::H5CgnsZone& zone)
{
	std::vector<int> size = zone.size();

	for (int i = 0; i < size[0] - 1; ++i) {
		for (int j = 0; j < size[1] - 1; ++j) {
			int id0 = structuredIndex(i    , j    , size.data());
			int id1 = structuredIndex(i + 1, j    , size.data());
			int id2 = structuredIndex(i + 1, j + 1, size.data());
			int id3 = structuredIndex(i    , j + 1, size.data());
			auto cell = new QuadCell(id0 + 1, id1 + 1, id2 + 1, id3 + 1, m_grid);
			cell->setId(static_cast<int> (m_cells.size()) + 1);
			m_cells.push_back(cell);
		}
	}

	return IRIC_NO_ERROR;
}

int Grid2D::Impl::loadUnstructuredGrid(const iRICLib::H5CgnsZone& zone)
{
	std::vector<int> indices;
	int ier = zone.readTriangleElements(&indices);
	RETURN_IF_ERR;

	for (int i = 0; i < static_cast<int> (indices.size()) / 3; ++i) {
		int id1 = indices.at(i * 3 + 0);
		int id2 = indices.at(i * 3 + 1);
		int id3 = indices.at(i * 3 + 2);

		auto cell = new TriCell(id1, id2, id3, m_grid);
		cell->setId(static_cast<int> (m_cells.size()) + 1);
		m_cells.push_back(cell);
	}

	return IRIC_NO_ERROR;
}

void Grid2D::Impl::setupBackGrid()
{
	m_backGridX.clear();
	m_backGridY.clear();
	m_backGridCells.clear();

	Rect2D rect = m_grid->boundingRect();
	size_t numCells = m_grid->cellCount();
	int divNum = static_cast<int> (std::sqrt(static_cast<double>(numCells) / 4));
	if (divNum == 0) {divNum = 1;}

	double xDelta = (rect.xMax() - rect.xMin()) / divNum;
	double yDelta = (rect.yMax() - rect.yMin()) / divNum;
	for (int i = 0; i < divNum; ++i) {
		m_backGridX.push_back(rect.xMin() + i * xDelta);
		m_backGridY.push_back(rect.yMin() + i * yDelta);
	}
	m_backGridX.push_back(rect.xMax());
	m_backGridY.push_back(rect.yMax());

	std::vector<Cell2D*> emptyVec;
	for (int i = 0; i < divNum; ++i) {
		for (int j = 0; j < divNum; ++j) {
			m_backGridCells.push_back(emptyVec);
		}
	}

	for (size_t i = 0; i < m_cells.size(); ++i) {
		Cell2D* cell = m_cells.at(i);
		Rect2D rect = cell->boundingRect();

		std::vector<double>::const_iterator x_lb = std::lower_bound(m_backGridX.begin(), m_backGridX.end(), rect.xMin());
		if (*x_lb != rect.xMin() && x_lb != m_backGridX.begin()) {--x_lb;}

		std::vector<double>::const_iterator x_ub = std::lower_bound(m_backGridX.begin(), m_backGridX.end(), rect.xMax());

		std::vector<double>::const_iterator y_lb = std::lower_bound(m_backGridY.begin(), m_backGridY.end(), rect.yMin());
		if (*y_lb != rect.yMin() && y_lb != m_backGridY.begin()) {--y_lb;}

		std::vector<double>::const_iterator y_ub = std::lower_bound(m_backGridY.begin(), m_backGridY.end(), rect.yMax());

		for (std::vector<double>::const_iterator xit = x_lb; xit != x_ub; ++xit) {
			size_t x_idx = xit - m_backGridX.begin();
			for (std::vector<double>::const_iterator yit = y_lb; yit != y_ub; ++yit) {
				size_t y_idx = yit - m_backGridY.begin();

				size_t idx = x_idx + y_idx * (m_backGridX.size() - 1);
				m_backGridCells[idx].push_back(cell);
			}
		}
	}
}

int Grid2D::Impl::structuredIndex(int i, int j, int* size) const
{
	return i + j * (*size);
}

// -----------------------------------------------------------
// public interfaces
// -----------------------------------------------------------

Grid2D::Grid2D()
{
	impl = new Impl(this);
}

Grid2D::~Grid2D()
{
	delete impl;
}

int Grid2D::load(int fid, int gid)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone(fid, gid, &zone, "Grid2D::load");
	RETURN_IF_ERR;

	auto coords = zone->gridCoordinates();
	ier = impl->loadNodes(coords);
	RETURN_IF_ERR;

	ier = impl->loadCells(*zone);
	RETURN_IF_ERR;

	impl->setupBackGrid();

	return IRIC_NO_ERROR;
}

int Grid2D::load(int fid, int gid, int solid)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone(fid, gid, &zone, "Grid2D::load");
	RETURN_IF_ERR;

	zone->setSolutionId(solid);
	auto coords = zone->gridCoordinatesForSolution();
	impl->loadNodes(coords);
	ier = impl->loadNodes(coords);
	RETURN_IF_ERR;

	ier = impl->loadCells(*zone);
	RETURN_IF_ERR;

	impl->setupBackGrid();

	return IRIC_NO_ERROR;
}

int Grid2D::nodeCount() const
{
	return static_cast<int> (impl->m_nodes.size());
}

Point2D Grid2D::node(int nodeId) const
{
	return impl->m_nodes.at(nodeId - 1);
}

int Grid2D::cellCount() const
{
	return static_cast<int> (impl->m_cells.size());
}

Cell2D* Grid2D::cell(int cellId) const
{
	return impl->m_cells.at(cellId - 1);
}

Rect2D Grid2D::boundingRect() const
{
	Rect2D ret;
	for (int i = 0; i < static_cast<int> (impl->m_cells.size()); ++i) {
		Rect2D cellRect = impl->m_cells.at(i)->boundingRect();
		if (i == 0) {
			ret = cellRect;
		} else {
			ret = ret + cellRect;
		}
	}
	return ret;
}

bool Grid2D::findCell(const Point2D& point, int* cellId) const
{
	std::vector<double>::iterator lb_x = std::lower_bound(impl->m_backGridX.begin(), impl->m_backGridX.end(), point.x());
	if (lb_x == impl->m_backGridX.end()) {return false;}
	if (*lb_x != point.x() && lb_x != impl->m_backGridX.begin()) {-- lb_x;}

	std::vector<double>::iterator lb_y = std::lower_bound(impl->m_backGridY.begin(), impl->m_backGridY.end(), point.y());
	if (lb_y == impl->m_backGridY.end()) {return false;}
	if (*lb_y != point.y() && lb_y != impl->m_backGridY.begin()) {--lb_y;}

	size_t bgCellIdx = (lb_x - impl->m_backGridX.begin()) +
			(lb_y - impl->m_backGridY.begin()) * (impl->m_backGridX.size() - 1);

	const std::vector<Cell2D*>& cells = impl->m_backGridCells.at(bgCellIdx);
	for (int i = 0; i < static_cast<int> (cells.size()); ++i) {
		Cell2D* cell = cells.at(i);
		int nodeCount = cell->nodeCount();
		std::vector<double> weights(nodeCount, 0);
		bool ok = cell->interpolate(point, weights.data());
		if (ok) {
			*cellId = cell->id();
			return true;
		}
	}
	return false;
}

bool Grid2D::interpolate(const Point2D& point, int *count, int* nodeIds, double* weight) const
{
	std::vector<double>::iterator lb_x = std::lower_bound(impl->m_backGridX.begin(), impl->m_backGridX.end(), point.x());
	if (lb_x == impl->m_backGridX.end()) {return false;}
	if (*lb_x != point.x() && lb_x != impl->m_backGridX.begin()) {-- lb_x;}

	std::vector<double>::iterator lb_y = std::lower_bound(impl->m_backGridY.begin(), impl->m_backGridY.end(), point.y());
	if (lb_y == impl->m_backGridY.end()) {return false;}
	if (*lb_y != point.y() && lb_y != impl->m_backGridY.begin()) {--lb_y;}

	size_t bgCellIdx = (lb_x - impl->m_backGridX.begin()) +
			(lb_y - impl->m_backGridY.begin()) * (impl->m_backGridX.size() - 1);

	const std::vector<Cell2D*>& cells = impl->m_backGridCells.at(bgCellIdx);
	for (int i = 0; i < static_cast<int> (cells.size()); ++i) {
		Cell2D* cell = cells.at(i);
		*count = cell->nodeCount();
		bool ok = cell->interpolate(point, weight);
		if (ok) {
			for (int j = 0; j < cell->nodeCount(); ++j) {
				*(nodeIds + j) = cell->nodeId(j + 1);
			}
			return true;
		}
	}
	return false;
}

void Grid2D::addNode(const Point2D& p)
{
	impl->m_nodes.push_back(p);
}

void Grid2D::addNode(double x, double y)
{
	addNode(Point2D(x, y));
}

void Grid2D::addTriCell(int id1, int id2, int id3)
{
	impl->m_cells.push_back(new TriCell(id1, id2, id3, this));
}

void Grid2D::addQuadCell(int id1, int id2, int id3, int id4)
{
	impl->m_cells.push_back(new QuadCell(id1, id2, id3, id4, this));
}

void Grid2D::setupBackGrid()
{
	impl->setupBackGrid();
}
