#include "h5cgnsparticlegroupsolution_groupreader.h"

using namespace iRICLib;

H5CgnsParticleGroupSolution::GroupReader::GroupReader(const std::string& groupName, H5CgnsParticleGroupSolution* sol) :
	m_groupName (groupName),
	m_solution {sol}
{}

int H5CgnsParticleGroupSolution::GroupReader::readValueNames(std::vector<std::string>* names) const
{
	return m_solution->readValueNames(m_groupName, names);
}

int H5CgnsParticleGroupSolution::GroupReader::readValueNames(std::set<std::string>* names) const
{
	return m_solution->readValueNames(m_groupName, names);
}

int H5CgnsParticleGroupSolution::GroupReader::readValueType(const std::string& name, H5Util::DataArrayValueType *type) const
{
	return m_solution->readValueType(m_groupName, name, type);
}

int H5CgnsParticleGroupSolution::GroupReader::readValue(const std::string& name, std::vector<int>* values) const
{
	return m_solution->readValue(m_groupName, name, values);
}

int H5CgnsParticleGroupSolution::GroupReader::readValue(const std::string& name, std::vector<double>* values) const
{
	return m_solution->readValue(m_groupName, name, values);
}

int H5CgnsParticleGroupSolution::GroupReader::readValueAsDouble(const std::string& name, std::vector<double>* values) const
{
	return m_solution->readValueAsDouble(m_groupName, name, values);
}

H5CgnsZone* H5CgnsParticleGroupSolution::GroupReader::zone() const
{
	return m_solution->zone();
}
