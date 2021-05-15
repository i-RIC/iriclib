#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsfile.h"
#include "h5cgnsflowsolution.h"
#include "h5cgnsgridcoordinates.h"
#include "h5cgnsparticlegroupsolution.h"
#include "h5cgnsparticlesolution.h"
#include "h5cgnspolydatasolution.h"
#include "h5cgnszone.h"
#include "h5groupcloser.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnszone_impl.h"

#include <sstream>

using namespace iRICLib;

#define LABEL "Zone_t"
#define ELEMENT "Element"
#define ELEMENT_LABEL "Element_t"
#define ELEMENT_CONNECTIVITY "ElementConnectivity"
#define ELEMENT_RANGE "ElementRange"
#define INDEXRANGE_LABEL "IndexRange_t"

std::string H5CgnsZone::label()
{
	return LABEL;
}

H5CgnsZone::H5CgnsZone(const std::string& name, hid_t groupId, H5CgnsBase* base) :
	impl {new Impl {this}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_base = base;

	impl->readSizeAndType();
	impl->loadNames();
	impl->m_gridCoordinates = impl->openOrCreateGridCoordinates();
	impl->m_gridAttributes = impl->openOrCreateGridAttributes();
	impl->m_zoneBc = impl->openOrCreateZoneBc();
	impl->createZoneIterativeDataIfNotExists();
	impl->loadFlowSolutionPointerNames();
}

H5CgnsZone::H5CgnsZone(const std::string& name, Type type, const std::vector<int>& size, hid_t groupId, H5CgnsBase* base) :
	impl {new Impl {this}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_base = base;

	impl->m_type = type;
	impl->m_size = size;

	impl->writeSizeAndType();
	impl->m_gridCoordinates = impl->createGridCoordinates();
	impl->m_gridAttributes = impl->createGridAttributes();
	impl->createZoneIterativeData();
	impl->m_zoneBc = impl->createZoneBc();
}

H5CgnsZone::~H5CgnsZone()
{
	flush();
	clearSolutionGroups();

	delete impl;
}

hid_t H5CgnsZone::groupId() const
{
	return impl->m_groupId;
}

std::string H5CgnsZone::name() const
{
	return impl->m_name;
}

H5CgnsZone::Type H5CgnsZone::type() const
{
	return impl->m_type;
}

std::vector<int> H5CgnsZone::size() const
{
	return impl->m_size;
}

int H5CgnsZone::nodeCount() const
{
	std::vector<hsize_t> dims;
	nodeDims(&dims);
	int c = 1;
	for (auto d : dims) {
		c *= static_cast<int>(d);
	}
	return c;
}

int H5CgnsZone::cellCount() const
{
	std::vector<hsize_t> dims;
	cellDims(&dims);
	int c = 1;
	for (auto d : dims) {
		c *= static_cast<int>(d);
	}
	return c;
}

int H5CgnsZone::iFaceCount() const
{
	std::vector<hsize_t> dims;
	iFaceDims(&dims);
	int c = 1;
	for (auto d : dims) {
		c *= static_cast<int>(d);
	}
	return c;
}

int H5CgnsZone::jFaceCount() const
{
	std::vector<hsize_t> dims;
	jFaceDims(&dims);
	int c = 1;
	for (auto d : dims) {
		c *= static_cast<int>(d);
	}
	return c;
}

int H5CgnsZone::kFaceCount() const
{
	std::vector<hsize_t> dims;
	kFaceDims(&dims);
	int c = 1;
	for (auto d : dims) {
		c *= static_cast<int>(d);
	}
	return c;
}

int H5CgnsZone::nodeDims(std::vector<hsize_t>* dims) const
{
	if (type() == H5CgnsZone::Type::Structured) {
		int dim = base()->dimension();
		for (int i = 0; i < dim; ++i) {
			dims->push_back(impl->m_size.at(i));
		}
		return IRIC_NO_ERROR;
	}	else {
		dims->push_back(impl->m_size.at(0));
		return IRIC_NO_ERROR;
	}

}

int H5CgnsZone::cellDims(std::vector<hsize_t>* dims) const
{
	if (type() == H5CgnsZone::Type::Structured) {
		int dim = base()->dimension();
		for (int i = 0; i < dim; ++i) {
			dims->push_back(impl->m_size.at(i + dim));
		}
		return IRIC_NO_ERROR;
	}	else {
		dims->push_back(impl->m_size.at(1));
		return IRIC_NO_ERROR;
	}
}

int H5CgnsZone::iFaceDims(std::vector<hsize_t>* dims) const
{
	if (type() == H5CgnsZone::Type::Structured) {
		int dim = base()->dimension();
		for (int i = 0; i < dim; ++i) {
			if (i == 0) {
				dims->push_back(impl->m_size.at(i));
			} else {
				dims->push_back(impl->m_size.at(i + dim));
			}
		}
		return IRIC_NO_ERROR;
	}	else {
		return IRIC_NO_ERROR;
	}
}

int H5CgnsZone::jFaceDims(std::vector<hsize_t>* dims) const
{
	if (type() == H5CgnsZone::Type::Structured) {
		int dim = base()->dimension();
		for (int i = 0; i < dim; ++i) {
			if (i == 1) {
				dims->push_back(impl->m_size.at(i));
			} else {
				dims->push_back(impl->m_size.at(i + dim));
			}
		}
		return IRIC_NO_ERROR;
	}	else {
		return IRIC_NO_ERROR;
	}
}

int H5CgnsZone::kFaceDims(std::vector<hsize_t>* dims) const
{
	if (type() == H5CgnsZone::Type::Structured) {
		int dim = base()->dimension();
		for (int i = 0; i < dim; ++i) {
			if (i == 2) {
				dims->push_back(impl->m_size.at(i));
			} else {
				dims->push_back(impl->m_size.at(i + dim));
			}
		}
		return IRIC_NO_ERROR;
	}	else {
		return IRIC_NO_ERROR;
	}
}

H5CgnsBase* H5CgnsZone::base() const
{
	return impl->m_base;
}

int H5CgnsZone::solutionId() const
{
	return impl->m_solutionId;
}

int H5CgnsZone::setSolutionId(int solId)
{
	if (impl->m_solutionId == solId) {return IRIC_NO_ERROR;}

	clearSolutionGroups();
	impl->m_solutionId = solId;

	return IRIC_NO_ERROR;
}

int H5CgnsZone::getSolutionExists(bool* exists) const
{
	return impl->getSolutionExists(exists);
}

H5CgnsGridCoordinates* H5CgnsZone::gridCoordinates() const
{
	return impl->m_gridCoordinates;
}

H5CgnsGridAttributes* H5CgnsZone::gridAttributes() const
{
	return impl->m_gridAttributes;
}

H5CgnsZoneBc* H5CgnsZone::zoneBc() const
{
	return impl->m_zoneBc;
}

int H5CgnsZone::readTriangleElementsSize(int* size) const
{
	if (impl->m_type != Type::Unstructured) {
		_iric_logger_error("In H5CgnsZone::readTriangleElementsSize(), the grid type is not unstructured");
		return IRIC_WRONG_GRIDTYPE;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsZone::readTriangleElementsCount");
	int ier = readTriangleElementsValueCount(size);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsZone::readTriangleElementsCount", ier);
	RETURN_IF_ERR;

	*size /= 3;

	return IRIC_NO_ERROR;
}

int H5CgnsZone::readTriangleElementsValueCount(int* size) const
{
	if (impl->m_type != Type::Unstructured) {
		_iric_logger_error("In H5CgnsZone::readTriangleElementsCount(), the grid type is not unstructured");
		return IRIC_WRONG_GRIDTYPE;
	}

	std::ostringstream ss;
	ss << ELEMENT << "/" << ELEMENT_CONNECTIVITY;

	hid_t gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(impl->m_groupId, ss.str(), H5Util::dataArrayLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueLength");
	ier = H5Util::readGroupValueLength(gId, size);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsZone::readTriangleElements(std::vector<int>* indices) const
{
	if (impl->m_type != Type::Unstructured) {return false;}

	std::ostringstream ss;
	ss << ELEMENT << "/" << ELEMENT_CONNECTIVITY;

	hid_t gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(impl->m_groupId, ss.str(), H5Util::dataArrayLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValue");
	ier = H5Util::readGroupValue(gId, indices);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsZone::writeTriangleElements(const std::vector<int>& indices) const
{
	if (impl->m_type != Type::Unstructured) {return false;}

	hid_t element_id;
	std::vector<int> element_vals;
	element_vals.push_back(5);
	element_vals.push_back(0);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
	int ier = H5Util::createGroupWithValue(impl->m_groupId, ELEMENT, ELEMENT_LABEL, element_vals, &element_id);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(element_id, ELEMENT_CONNECTIVITY, indices);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	std::vector<int> range;
	range.push_back(1);
	range.push_back(static_cast<int> (indices.size() / 3));

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
	ier = H5Util::createGroupWithValue(element_id, ELEMENT_RANGE, INDEXRANGE_LABEL, range);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

bool H5CgnsZone::gridCoordinatesForSolutionExists() const
{
	return (impl->m_flowSolutionPointerNames.find("GridCoordinatesPointers") != impl->m_flowSolutionPointerNames.end());
}

H5CgnsGridCoordinates* H5CgnsZone::gridCoordinatesForSolution()
{
	if (impl->m_gridCoordinatesForSolution != nullptr) {
		return impl->m_gridCoordinatesForSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openGridCoordinatesForSolution();
	} else {
		return impl->createGridCoordinatesForSolution();
	}
}

bool H5CgnsZone::solutionExists(SolutionPosition pos) const
{
	switch (pos) {
	case SolutionPosition::Node:
		return nodeSolutionExists();
	case SolutionPosition::Cell:
		return cellSolutionExists();
	case SolutionPosition::IFace:
		return iFaceSolutionExists();
	case SolutionPosition::JFace:
		return jFaceSolutionExists();
	case SolutionPosition::KFace:
		return kFaceSolutionExists();
	}
}

H5CgnsFlowSolution* H5CgnsZone::solution(SolutionPosition pos)
{
	switch (pos) {
	case SolutionPosition::Node:
		return nodeSolution();
	case SolutionPosition::Cell:
		return cellSolution();
	case SolutionPosition::IFace:
		return iFaceSolution();
	case SolutionPosition::JFace:
		return jFaceSolution();
	case SolutionPosition::KFace:
		return kFaceSolution();
	}
}


bool H5CgnsZone::nodeSolutionExists() const
{
	if (impl->m_flowSolutionPointerNames.find("FlowSolutionPointers") != impl->m_flowSolutionPointerNames.end()) {return true;}
	if (impl->m_names.find("FlowSolution1") != impl->m_names.end()) {return true;}

	return false;
}

H5CgnsFlowSolution* H5CgnsZone::nodeSolution()
{
	if (impl->m_nodeSolution != nullptr) {
		return impl->m_nodeSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openNodeSolution();
	} else {
		return impl->createNodeSolution();
	}
}

bool H5CgnsZone::cellSolutionExists() const
{
	if (impl->m_flowSolutionPointerNames.find("FlowCellSolutionPointers") != impl->m_flowSolutionPointerNames.end()) {return true;}
	if (impl->m_names.find("FlowCellSolution1") != impl->m_names.end()) {return true;}

	return false;
}

H5CgnsFlowSolution* H5CgnsZone::cellSolution()
{
	if (impl->m_cellSolution != nullptr) {
		return impl->m_cellSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openCellSolution();
	} else {
		return impl->createCellSolution();
	}
}

bool H5CgnsZone::iFaceSolutionExists() const
{
	if (impl->m_flowSolutionPointerNames.find("FlowIFaceSolutionPointers") != impl->m_flowSolutionPointerNames.end()) {return true;}
	if (impl->m_names.find("FlowIFaceSolution1") != impl->m_names.end()) {return true;}

	return false;
}

H5CgnsFlowSolution* H5CgnsZone::iFaceSolution()
{
	if (impl->m_iFaceSolution != nullptr) {
		return impl->m_iFaceSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openIFaceSolution();
	} else {
		return impl->createIFaceSolution();
	}
}

bool H5CgnsZone::jFaceSolutionExists() const
{
	if (impl->m_flowSolutionPointerNames.find("FlowJFaceSolutionPointers") != impl->m_flowSolutionPointerNames.end()) {return true;}
	if (impl->m_names.find("FlowJFaceSolution1") != impl->m_names.end()) {return true;}

	return false;
}

H5CgnsFlowSolution* H5CgnsZone::jFaceSolution()
{
	if (impl->m_jFaceSolution != nullptr) {
		return impl->m_jFaceSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openJFaceSolution();
	} else {
		return impl->createJFaceSolution();
	}
}

bool H5CgnsZone::kFaceSolutionExists() const
{
	if (impl->m_flowSolutionPointerNames.find("FlowKFaceSolutionPointers") != impl->m_flowSolutionPointerNames.end()) {return true;}
	if (impl->m_names.find("FlowKFaceSolution1") != impl->m_names.end()) {return true;}

	return false;
}

H5CgnsFlowSolution* H5CgnsZone::kFaceSolution()
{
	if (impl->m_kFaceSolution != nullptr) {
		return impl->m_kFaceSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openKFaceSolution();
	} else {
		return impl->createKFaceSolution();
	}
}

bool H5CgnsZone::particleGroupSolutionExists() const
{
	if (impl->m_flowSolutionPointerNames.find("ParticleGroupSolutionPointers") != impl->m_flowSolutionPointerNames.end()) {return true;}
	if (impl->m_names.find("ParticleGroupSolution1") != impl->m_names.end()) {return true;}

	return false;
}

H5CgnsParticleGroupSolution* H5CgnsZone::particleGroupSolution()
{
	if (impl->m_particleGroupSolution != nullptr) {
		return impl->m_particleGroupSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openParticleGroupSolution();
	} else {
		return impl->createParticleGroupSolution();
	}
}

bool H5CgnsZone::particleSolutionExists() const
{
	if (impl->m_flowSolutionPointerNames.find("ParticleSolutionPointers") != impl->m_flowSolutionPointerNames.end()) {return true;}
	if (impl->m_names.find("ParticleSolution1") != impl->m_names.end()) {return true;}

	return false;
}

H5CgnsParticleSolution* H5CgnsZone::particleSolution()
{
	if (impl->m_particleSolution != nullptr) {
		return impl->m_particleSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openParticleSolution();
	} else {
		return impl->createParticleSolution();
	}
}

bool H5CgnsZone::polyDataSolutionExists() const
{
	if (impl->m_flowSolutionPointerNames.find("PolydataSolutionPointers") != impl->m_flowSolutionPointerNames.end()) {return true;}
	if (impl->m_names.find("PolydataSolution1") != impl->m_names.end()) {return true;}

	return false;
}

H5CgnsPolyDataSolution* H5CgnsZone::polyDataSolution()
{
	if (impl->m_polyDataSolution != nullptr) {
		return impl->m_polyDataSolution;
	}
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return impl->openPolyDataSolution();
	} else {
		return impl->createPolyDataSolution();
	}
}

int H5CgnsZone::copyGridTo(H5CgnsZone* target)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridCoordinates::copyTo");
	int ier = impl->m_gridCoordinates->copyTo(target->gridCoordinates());
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsGridCoordinates::copyTo", ier);
	RETURN_IF_ERR;

	if (type() == Type::Structured) {return IRIC_NO_ERROR;}

	// if unstructured grids, copy "Element" group
	hid_t srcElem, tgtElem;

	_IRIC_LOGGER_TRACE_CALL_START("H5Gopen2");
	srcElem = H5Gopen2(impl->m_groupId, ELEMENT, H5P_DEFAULT);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gopen2");
	if (srcElem < 0) {return IRIC_H5_CALL_ERROR;}

	H5GroupCloser srcElemCloser(srcElem);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	ier = H5Util::createGroup(target->impl->m_groupId, ELEMENT, &tgtElem);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser tgtElemCloser(tgtElem);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::copyGroup");
	ier = H5Util::copyGroup(srcElem, tgtElem, true);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::copyGroup", ier);

	return IRIC_NO_ERROR;
}

int H5CgnsZone::flush()
{
	if (impl->m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return IRIC_NO_ERROR;
	}
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsZone::Impl::writeZoneIterativeData");
	int ier = impl->writeZoneIterativeData();
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsZone::Impl::writeZoneIterativeData", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

void H5CgnsZone::clearSolutionGroups()
{
	delete impl->m_gridCoordinatesForSolution;
	impl->m_gridCoordinatesForSolution = nullptr;

	delete impl->m_nodeSolution;
	impl->m_nodeSolution = nullptr;

	delete impl->m_cellSolution;
	impl->m_cellSolution = nullptr;

	delete impl->m_iFaceSolution;
	impl->m_iFaceSolution = nullptr;

	delete impl->m_jFaceSolution;
	impl->m_jFaceSolution = nullptr;

	delete impl->m_kFaceSolution;
	impl->m_kFaceSolution = nullptr;

	delete impl->m_particleGroupSolution;
	impl->m_particleGroupSolution = nullptr;

	delete impl->m_particleSolution;
	impl->m_particleSolution = nullptr;

	delete impl->m_polyDataSolution;
	impl->m_polyDataSolution = nullptr;
}

int H5CgnsZone::deleteAllResults()
{
	std::vector<std::string> solHeaders;
	solHeaders.push_back("FlowSolution");
	solHeaders.push_back("FlowCellSolution");
	solHeaders.push_back("FlowIFaceSolution");
	solHeaders.push_back("FlowJFaceSolution");
	solHeaders.push_back("FlowKFaceSolution");
	solHeaders.push_back("ParticleGroupSolution");
	solHeaders.push_back("ParticleSolution");
	solHeaders.push_back("PolydataSolution");

	std::vector<std::string> names;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, &names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : names) {
		for (const auto& header : solHeaders) {
			if (name.substr(0, header.size()) == header) {
				// this is a solution node.
				_IRIC_LOGGER_TRACE_CALL_START("H5Ldelete");
				herr_t status = H5Ldelete(impl->m_groupId, name.c_str(), H5P_DEFAULT);
				_IRIC_LOGGER_TRACE_CALL_END("H5Ldelete");
				if (status < 0) {
					_iric_logger_error("H5CgnsZone::deleteAllResults", "H5Ldelete", status);
					return IRIC_H5_CALL_ERROR;
				}
			}
		}
	}

	return IRIC_NO_ERROR;
}
