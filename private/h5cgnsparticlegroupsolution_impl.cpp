#include "h5cgnsparticlegroupsolution_impl.h"

using namespace iRICLib;

H5CgnsParticleGroupSolution::Impl::Impl()
{}

void H5CgnsParticleGroupSolution::Impl::clear()
{
	m_coordinateX.clear();
	m_coordinateY.clear();
	m_coordinateZ.clear();
	m_intValues.clear();
	m_realValues.clear();
}
