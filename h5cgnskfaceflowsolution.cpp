#include "h5cgnskfaceflowsolution.h"
#include "h5cgnszone.h"

using namespace iRICLib;

H5CgnsKFaceFlowSolution::H5CgnsKFaceFlowSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	H5CgnsFlowSolution(name, groupId, zone)
{}

int H5CgnsKFaceFlowSolution::dataDims(std::vector<hsize_t>* dims) const
{
	return zone()->kFaceDims(dims);
}
