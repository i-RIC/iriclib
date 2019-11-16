#include "h5cgnspolydatasolution_impl.h"

using namespace iRICLib;

H5CgnsPolyDataSolution::Impl::Impl()
{}

void H5CgnsPolyDataSolution::Impl::clear()
{
	m_coordinateX.clear();
	m_coordinateY.clear();
	m_types.clear();
	m_sizes.clear();
	m_intValues.clear();
	m_realValues.clear();
}
