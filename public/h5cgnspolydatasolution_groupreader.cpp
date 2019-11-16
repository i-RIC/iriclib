#include "error_macros.h"
#include "h5cgnspolydatasolution_groupreader.h"
#include "iriclib_errorcodes.h"

using namespace iRICLib;

namespace {

template <typename V>
void setupVals(const std::vector<V>& src, const std::vector<int>& cellCounts, std::vector<V>* tgt)
{
	for (unsigned int i = 0; i < src.size(); ++i) {
		auto v = src[i];
		int cellCount = cellCounts[i];
		for (int j = 0; j < cellCount; ++j) {
			tgt->push_back(v);
		}
	}
}

} // namespace

H5CgnsPolyDataSolution::GroupReader::GroupReader(const std::string& groupName, H5CgnsPolyDataSolution* sol) :
	m_groupName (groupName),
	m_solution {sol}
{}

int H5CgnsPolyDataSolution::GroupReader::readValueNames(std::vector<std::string>* names) const
{
	return m_solution->readValueNames(m_groupName, names);
}

int H5CgnsPolyDataSolution::GroupReader::readValueNames(std::set<std::string>* names) const
{
	return m_solution->readValueNames(m_groupName, names);
}

int H5CgnsPolyDataSolution::GroupReader::readValueType(const std::string& name, H5Util::DataArrayValueType *type) const
{
	return m_solution->readValueType(m_groupName, name, type);
}

int H5CgnsPolyDataSolution::GroupReader::readValue(const std::string& name, std::vector<int>* values) const
{
	std::vector<int> tmpVals;
	int ier = m_solution->readValue(m_groupName, name, &tmpVals);
	RETURN_IF_ERR;

	setupVals(tmpVals, m_cellCounts, values);

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::GroupReader::readValue(const std::string& name, std::vector<double>* values) const
{
	std::vector<double> tmpVals;
	int ier = m_solution->readValue(m_groupName, name, &tmpVals);
	RETURN_IF_ERR;

	setupVals(tmpVals, m_cellCounts, values);

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::GroupReader::readValueAsDouble(const std::string& name, std::vector<double>* values) const
{
	std::vector<double> tmpVals;
	int ier = m_solution->readValueAsDouble(m_groupName, name, &tmpVals);
	RETURN_IF_ERR;

	setupVals(tmpVals, m_cellCounts, values);

	return IRIC_NO_ERROR;
}

H5CgnsZone* H5CgnsPolyDataSolution::GroupReader::zone() const
{
	return m_solution->zone();
}

void H5CgnsPolyDataSolution::GroupReader::setCellCounts(const std::vector<int>& cellCounts)
{
	m_cellCounts = cellCounts;
}
