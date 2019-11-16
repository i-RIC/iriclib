#include "h5cgnscellflowsolution.h"
#include "h5cgnszone.h"

using namespace iRICLib;

H5CgnsCellFlowSolution::H5CgnsCellFlowSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	H5CgnsFlowSolution(name, groupId, zone)
{}

int H5CgnsCellFlowSolution::dataDims(std::vector<hsize_t>* dims) const
{
	return zone()->cellDims(dims);
}
