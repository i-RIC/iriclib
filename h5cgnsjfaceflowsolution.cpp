#include "h5cgnsjfaceflowsolution.h"
#include "h5cgnszone.h"

using namespace iRICLib;

H5CgnsJFaceFlowSolution::H5CgnsJFaceFlowSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	H5CgnsFlowSolution(name, groupId, zone)
{}

int H5CgnsJFaceFlowSolution::dataDims(std::vector<hsize_t>* dims) const
{
	return zone()->jFaceDims(dims);
}
