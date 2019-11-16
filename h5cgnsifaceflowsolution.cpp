#include "h5cgnsifaceflowsolution.h"
#include "h5cgnszone.h"

using namespace iRICLib;

H5CgnsIFaceFlowSolution::H5CgnsIFaceFlowSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	H5CgnsFlowSolution(name, groupId, zone)
{}

int H5CgnsIFaceFlowSolution::dataDims(std::vector<hsize_t>* dims) const
{
	return zone()->iFaceDims(dims);
}
