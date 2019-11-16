#include "h5cgnsnodeflowsolution.h"
#include "h5cgnszone.h"

using namespace iRICLib;

H5CgnsNodeFlowSolution::H5CgnsNodeFlowSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	H5CgnsFlowSolution(name, groupId, zone)
{}

int H5CgnsNodeFlowSolution::dataDims(std::vector<hsize_t>* dims) const
{
	return zone()->nodeDims(dims);
}
