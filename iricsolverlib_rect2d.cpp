#include "iricsolverlib_point2d.h"
#include "iricsolverlib_rect2d.h"

#include <algorithm>

using namespace std;

namespace iRICSolverLib {

Rect2D::Rect2D() :
	m_xMin (0),
	m_xMax (0),
	m_yMin (0),
	m_yMax (0)
{}

Rect2D::Rect2D(double xmin, double xmax, double ymin, double ymax) :
	m_xMin (xmin),
	m_xMax (xmax),
	m_yMin (ymin),
	m_yMax (ymax)
{}

Rect2D::Rect2D(const Rect2D& rect) :
	m_xMin (rect.xMin()),
	m_xMax (rect.xMax()),
	m_yMin (rect.yMin()),
	m_yMax (rect.yMax())
{}

Rect2D& Rect2D::operator=(const Rect2D& rect)
{
	m_xMin = rect.xMin();
	m_xMax = rect.xMax();
	m_yMin = rect.yMin();
	m_yMax = rect.yMax();

	return *this;
}

double Rect2D::xMin() const
{
	return m_xMin;
}

double Rect2D::xMax() const
{
	return m_xMax;
}

double Rect2D::yMin() const
{
	return m_yMin;
}

double Rect2D::yMax() const
{
	return m_yMax;
}

double Rect2D::xWidth() const
{
	return m_xMax - m_xMin;
}

double Rect2D::yWidth() const
{
	return m_yMax - m_yMin;
}

bool Rect2D::contains(double x, double y) const
{
	return (m_xMin <= x && m_xMax >= x && m_yMin <= y && m_yMax >= y);
}

bool Rect2D::contains(const Point2D& point) const
{
	return contains(point.x(), point.y());
}

bool Rect2D::intersects(const Rect2D& rect) const
{
	if (m_xMin > rect.xMax()) {return false;}
	if (m_xMax < rect.xMin()) {return false;}
	if (m_yMin > rect.yMax()) {return false;}
	if (m_yMax < rect.yMin()) {return false;}

	return true;
}

void Rect2D::setXMin(double xmin)
{
	m_xMin = xmin;
}

void Rect2D::setXMax(double xmax)
{
	m_xMax = xmax;
}

void Rect2D::setYMin(double ymin)
{
	m_yMin = ymin;
}

void Rect2D::setYMax(double ymax)
{
	m_yMax = ymax;
}

Rect2D operator+(const Rect2D& rect1, const Rect2D& rect2)
{
	return Rect2D(
			min(rect1.xMin(), rect2.xMin()),
			max(rect1.xMax(), rect2.xMax()),
			min(rect1.yMin(), rect2.yMin()),
			max(rect1.yMax(), rect2.yMax()));
}

} // namespace iRICSolverLib
