#include "../error_macros.h"
#include "../h5cgnsbase.h"
#include "../h5cgnscellflowsolution.h"
#include "../h5cgnsfile.h"
#include "../h5cgnsflowsolution.h"
#include "../h5cgnsgridattributes.h"
#include "../h5cgnsgridcoordinates.h"
#include "../h5cgnsifaceflowsolution.h"
#include "../h5cgnsjfaceflowsolution.h"
#include "../h5cgnskfaceflowsolution.h"
#include "../h5cgnsnodeflowsolution.h"
#include "../h5cgnsparticlegroupsolution.h"
#include "../h5cgnsparticlesolution.h"
#include "../h5cgnspolydatasolution.h"
#include "../h5cgnszone.h"
#include "../h5cgnszonebc.h"
#include "../h5groupcloser.h"
#include "../h5util.h"
#include "../iriclib_errorcodes.h"

#include "../internal/iric_logger.h"

#include "h5cgnszone_impl.h"

#include <sstream>

using namespace iRICLib;

namespace {

#define ZONETYPE_NAME "ZoneType"
#define ZONETYPE_LABEL "ZoneType_t"
#define STRUCTURED "Structured"
#define UNSTRUCTURED "Unstructured"

#define GRIDCOORDINATES_NAME "GridCoordinates"
#define GRIDLOCATION_LABEL "GridLocation_t"

#define GRIDATTRIBUTES_NAME "GridConditions"

#define ZONEITERATIVEDATA_NAME "ZoneIterativeData"
#define ZONEITERATIVEDATA_LABEL "ZoneIterativeData_t"

int writeSolutionPointers(hid_t groupId, int maxSolutionId, const std::string& name, const std::string& prefix, std::set<std::string>* names)
{
	int MAXLEN = 32;
	std::vector<char> buffer;

	buffer.assign(MAXLEN * maxSolutionId, 0);

	for (int S = 0; S < maxSolutionId; ++S) {
		memcpy(buffer.data() + MAXLEN * S, prefix.data(), prefix.length());

		std::ostringstream ss;
		ss << (S + 1);
		auto numStr = ss.str();
		memcpy(buffer.data() + MAXLEN * S + prefix.length(), numStr.data(), numStr.length());
	}

	std::vector<hsize_t> dims;
	dims.push_back(maxSolutionId);
	dims.push_back(MAXLEN);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::updateOrCreateDataArray");
	int ier = H5Util::updateOrCreateDataArray(groupId, name, buffer, dims, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::updateOrCreateDataArray", ier);

	return IRIC_NO_ERROR;
}

} // namespace

H5CgnsZone::Impl::Impl(H5CgnsZone* zone) :
	m_solutionId {0},
	m_groupId {-1},
	m_gridCoordinates {nullptr},
	m_gridAttributes {nullptr},
	m_zoneBc {nullptr},
	m_gridCoordinatesForSolution {nullptr},
	m_nodeSolution {nullptr},
	m_cellSolution {nullptr},
	m_iFaceSolution {nullptr},
	m_jFaceSolution {nullptr},
	m_kFaceSolution {nullptr},
	m_particleGroupSolution {nullptr},
	m_particleSolution {nullptr},
	m_polyDataSolution {nullptr},
	m_base {nullptr},
	m_zone {zone}
{}

H5CgnsZone::Impl::~Impl()
{
	delete m_gridCoordinates;
	delete m_gridAttributes;
	delete m_zoneBc;

	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsZone::Impl::~Impl", "H5Gclose", status);
	}
}

void H5CgnsZone::Impl::readSizeAndType()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValue");
	int ier = H5Util::readGroupValue(m_groupId, &m_size);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValue", ier);

	hid_t gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	ier = H5Util::openGroup(m_groupId, ZONETYPE_NAME, ZONETYPE_LABEL, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	H5GroupCloser closer(gId);

	std::string value;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValue");
	ier = H5Util::readGroupValue(gId, &value);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValue", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	if (value == STRUCTURED) {
		m_type = Type::Structured;
	} else if (value == UNSTRUCTURED) {
		m_type = Type::Unstructured;
	}
}

void H5CgnsZone::Impl::writeSizeAndType()
{
	int indexDim = 1;
	if (m_type == Type::Structured) {
		indexDim = m_base->dimension();
	}
	std::vector<hsize_t> dims(2);
	dims[0] = indexDim;
	dims[1] = 3;

	auto size = dims[0] * dims[1];

	// add zeros, in case size do not contain NBoundVertex data
	auto dataToAdd = size - m_size.size();
	for (hsize_t i = 0; i < dataToAdd; ++i) {
		m_size.push_back(0);
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::writeData");
	int ier = H5Util::writeData(m_groupId, " data", m_size, dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::writeData", ier);

	if (m_type == Type::Structured) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
		ier = H5Util::createGroupWithValue(m_groupId, ZONETYPE_NAME, ZONETYPE_LABEL, STRUCTURED);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);
	} else if (m_type == Type::Unstructured) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
		ier = H5Util::createGroupWithValue(m_groupId, ZONETYPE_NAME, ZONETYPE_LABEL, UNSTRUCTURED);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);
	}
}

void H5CgnsZone::Impl::loadNames()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(m_groupId, &m_names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
}

void H5CgnsZone::Impl::loadFlowSolutionPointerNames()
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, ZONEITERATIVEDATA_NAME, ZONEITERATIVEDATA_LABEL, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	H5GroupCloser closer(gId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	ier = H5Util::getGroupNames(gId, &m_flowSolutionPointerNames);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
}

int H5CgnsZone::Impl::getSolutionExists(bool* exists) const
{
	*exists = (m_flowSolutionPointerNames.size() > 0);

	return IRIC_NO_ERROR;
}

H5CgnsGridCoordinates* H5CgnsZone::Impl::openOrCreateGridCoordinates()
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openOrCreateGroup");
	int ier = H5Util::openOrCreateGroup(m_groupId, GRIDCOORDINATES_NAME, H5CgnsGridCoordinates::label(), H5Util::userDefinedDataType(), &gId, m_names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openOrCreateGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	return new H5CgnsGridCoordinates(GRIDCOORDINATES_NAME, gId, m_zone);
}

H5CgnsGridCoordinates* H5CgnsZone::Impl::createGridCoordinates()
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = H5Util::createGroup(m_groupId, GRIDCOORDINATES_NAME, H5CgnsGridCoordinates::label(), H5Util::userDefinedDataType(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openOrCreateGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	return new H5CgnsGridCoordinates(GRIDCOORDINATES_NAME, gId, m_zone);
}

H5CgnsGridAttributes* H5CgnsZone::Impl::openOrCreateGridAttributes()
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openOrCreateGroup");
	int ier = H5Util::openOrCreateGroup(m_groupId, GRIDATTRIBUTES_NAME, H5Util::userDefinedDataLabel(), H5Util::userDefinedDataType(), &gId, m_names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openOrCreateGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	return new H5CgnsGridAttributes(gId, m_zone);
}

H5CgnsGridAttributes* H5CgnsZone::Impl::createGridAttributes()
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = H5Util::createGroup(m_groupId, GRIDATTRIBUTES_NAME, H5Util::userDefinedDataLabel(), H5Util::userDefinedDataType(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	return new H5CgnsGridAttributes(gId, m_zone);
}

H5CgnsZoneBc* H5CgnsZone::Impl::openOrCreateZoneBc()
{
	if ((m_names.find(H5CgnsZoneBc::name()) == m_names.end()) && m_base->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		return nullptr;
	}

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openOrCreateGroup");
	int ier = H5Util::openOrCreateGroup(m_groupId, H5CgnsZoneBc::name() , H5CgnsZoneBc::label(), H5Util::userDefinedDataType(), &gId, m_names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openOrCreateGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	return new H5CgnsZoneBc(gId, m_zone);
}

H5CgnsZoneBc* H5CgnsZone::Impl::createZoneBc()
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = H5Util::createGroup(m_groupId, H5CgnsZoneBc::name() , H5CgnsZoneBc::label(), H5Util::userDefinedDataType(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	return new H5CgnsZoneBc(gId, m_zone);
}

void H5CgnsZone::Impl::createZoneIterativeDataIfNotExists()
{
	if (m_names.find(ZONEITERATIVEDATA_NAME) != m_names.end()) {return;}

	createZoneIterativeData();
}

void H5CgnsZone::Impl::createZoneIterativeData()
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = H5Util::createGroup(m_groupId, ZONEITERATIVEDATA_NAME, ZONEITERATIVEDATA_LABEL, H5Util::userDefinedDataType(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	H5GroupCloser closer(gId);
}

H5CgnsGridCoordinates* H5CgnsZone::Impl::openGridCoordinatesForSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "GridCoordinatesForSolution" << m_solutionId;
	auto name = ss.str();

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, name, H5CgnsGridCoordinates::label(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto coords = new H5CgnsGridCoordinates(name, gId, m_zone);
	m_gridCoordinatesForSolution = coords;

	return coords;
}

H5CgnsGridCoordinates* H5CgnsZone::Impl::createGridCoordinatesForSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "GridCoordinatesForSolution" << m_solutionId;
	auto name = ss.str();

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = H5Util::createGroup(m_groupId, name, H5CgnsGridCoordinates::label(), H5Util::userDefinedDataType(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto coords = new H5CgnsGridCoordinates(name, gId, m_zone);
	m_gridCoordinatesForSolution = coords;

	return coords;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::openNodeSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowSolution" << m_solutionId;
	auto name = ss.str();

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, name, H5CgnsFlowSolution::label(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsNodeFlowSolution(name, gId, m_zone);
	m_nodeSolution = sol;

	return sol;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::createNodeSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowSolution" << m_solutionId;
	auto name = ss.str();

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = H5Util::createGroup(m_groupId, name, H5CgnsFlowSolution::label(), H5Util::userDefinedDataType(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsNodeFlowSolution(name, gId, m_zone);
	m_nodeSolution = sol;

	return sol;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::openCellSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowCellSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsZone::Impl::openSolutionGroup");
	int ier = openSolutionGroup(ss.str(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsZone::Impl::openSolutionGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsCellFlowSolution(ss.str(), gId, m_zone);
	m_cellSolution = sol;

	return sol;
}


H5CgnsFlowSolution* H5CgnsZone::Impl::createCellSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowCellSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsZone::Impl::createSolution");
	int ier = createSolutionGroup(ss.str(), "CellCenter", &gId);
	_IRIC_LOGGER_TRACE_CALL_END("H5CgnsZone::Impl::createSolution");
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsCellFlowSolution(ss.str(), gId, m_zone);
	m_cellSolution = sol;

	return sol;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::openIFaceSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowIFaceSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openSolutionGroup");
	int ier = openSolutionGroup(ss.str(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openSolutionGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsIFaceFlowSolution(ss.str(), gId, m_zone);
	m_iFaceSolution = sol;

	return sol;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::createIFaceSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowIFaceSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createSolutionGroup");
	int ier = createSolutionGroup(ss.str(), "IFaceCenter", &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createSolutionGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsIFaceFlowSolution(ss.str(), gId, m_zone);
	m_iFaceSolution = sol;

	return sol;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::openJFaceSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowJFaceSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openSolutionGroup");
	int ier = openSolutionGroup(ss.str(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openSolutionGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsJFaceFlowSolution(ss.str(), gId, m_zone);
	m_jFaceSolution = sol;

	return sol;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::createJFaceSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowJFaceSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createSolutionGroup");
	int ier = createSolutionGroup(ss.str(), "JFaceCenter", &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createSolutionGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsJFaceFlowSolution(ss.str(), gId, m_zone);
	m_jFaceSolution = sol;

	return sol;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::openKFaceSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowKFaceSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openSolutionGroup");
	int ier = openSolutionGroup(ss.str(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Util::openSolutionGroup");
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsKFaceFlowSolution(ss.str(), gId, m_zone);
	m_kFaceSolution = sol;

	return sol;
}

H5CgnsFlowSolution* H5CgnsZone::Impl::createKFaceSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "FlowKFaceSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createSolutionGroup");
	int ier = createSolutionGroup(ss.str(), "KFaceCenter", &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createSolutionGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsKFaceFlowSolution(ss.str(), gId, m_zone);
	m_kFaceSolution = sol;

	return sol;
}

H5CgnsParticleGroupSolution* H5CgnsZone::Impl::openParticleGroupSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "ParticleSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, ss.str(), H5Util::userDefinedDataLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsParticleGroupSolution(ss.str(), gId, m_zone);
	m_particleGroupSolution = sol;

	return sol;
}

H5CgnsParticleGroupSolution* H5CgnsZone::Impl::createParticleGroupSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "ParticleSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier = H5Util::createUserDefinedDataGroup(m_groupId, ss.str(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsParticleGroupSolution(ss.str(), gId, m_zone);
	m_particleGroupSolution = sol;

	return sol;
}

H5CgnsParticleSolution* H5CgnsZone::Impl::openParticleSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "ParticleGroupSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, ss.str(), H5Util::userDefinedDataLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsParticleSolution(ss.str(), gId, m_zone);
	m_particleSolution = sol;

	return sol;
}

H5CgnsParticleSolution* H5CgnsZone::Impl::createParticleSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "ParticleGroupSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier = H5Util::createUserDefinedDataGroup(m_groupId, ss.str(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsParticleSolution(ss.str(), gId, m_zone);
	m_particleSolution = sol;

	return sol;
}

H5CgnsPolyDataSolution* H5CgnsZone::Impl::openPolyDataSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "PolydataSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, ss.str(), H5Util::userDefinedDataLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsPolyDataSolution(ss.str(), gId, m_zone);
	m_polyDataSolution = sol;

	return sol;
}

H5CgnsPolyDataSolution* H5CgnsZone::Impl::createPolyDataSolution()
{
	if (m_solutionId == 0) {return nullptr;}

	std::ostringstream ss;
	ss << "PolydataSolution" << m_solutionId;

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier = H5Util::createUserDefinedDataGroup(m_groupId, ss.str(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto sol = new H5CgnsPolyDataSolution(ss.str(), gId, m_zone);
	m_polyDataSolution = sol;

	return sol;
}

int H5CgnsZone::Impl::writeZoneIterativeData()
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, ZONEITERATIVEDATA_NAME, ZONEITERATIVEDATA_LABEL, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	std::set<std::string> names;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	ier = H5Util::getGroupNames(gId, &names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	if (m_gridCoordinatesForSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "GridCoordinatesPointers", "GridCoordinatesForSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	if (m_nodeSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "FlowSolutionPointers", "FlowSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	if (m_cellSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "FlowCellSolutionPointers", "FlowCellSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	if (m_iFaceSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "FlowIFaceSolutionPointers", "FlowIFaceSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	if (m_jFaceSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "FlowJFaceSolutionPointers", "FlowJFaceSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	if (m_kFaceSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "FlowKFaceSolutionPointers", "FlowKFaceSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	if (m_particleSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "ParticleSolutionPointers", "ParticleSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	if (m_particleGroupSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "ParticleGroupSolutionPointers", "ParticleGroupSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	if (m_polyDataSolution != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("writeSolutionPointers");
		ier = writeSolutionPointers(gId, m_solutionId, "PolyDataSolutionPointers", "PolyDataSolution", &names);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("writeSolutionPointers", ier);
		RETURN_IF_ERR
	}

	return IRIC_NO_ERROR;
}

int H5CgnsZone::Impl::openSolutionGroup(const std::string& name, hid_t* gId)
{
	if (m_solutionId == 0) {
		std::ostringstream ss;
		ss << "In H5CgnsZone::Impl::openSolutionGroup(), m_solutionId == 0";
		_iric_logger_error(ss.str());
		return IRIC_SOLUTION_ID_INVALID;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, name, H5CgnsFlowSolution::label(), gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsZone::Impl::createSolutionGroup(const std::string& name, const std::string& gridLocation, hid_t* gId)
{
	if (m_solutionId == 0) {
		std::ostringstream ss;
		ss << "In H5CgnsZone::Impl::openSolutionGroup(), m_solutionId == 0";
		_iric_logger_error(ss.str());
		return IRIC_SOLUTION_ID_INVALID;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier = H5Util::createGroup(m_groupId, name, H5CgnsFlowSolution::label(), H5Util::userDefinedDataType(), gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
	ier = H5Util::createGroupWithValue(*gId, "GridLocation", GRIDLOCATION_LABEL, gridLocation);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);

	if (ier != IRIC_NO_ERROR) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
		herr_t status = H5Gclose(*gId);
		_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

		if (status < 0) {
			_iric_logger_error("H5CgnsZone::Impl::openOrCreateSolution", "H5Gclose", status);
		}

		_IRIC_LOGGER_TRACE_CALL_START("H5Ldelete");
		status = H5Ldelete(m_groupId, name.c_str(), H5P_DEFAULT);
		_IRIC_LOGGER_TRACE_CALL_END("H5Ldelete");

		if (status < 0) {
			_iric_logger_error("H5CgnsZone::Impl::openOrCreateSolution", "H5Ldelete", status);
		}
		return ier;
	}

	return IRIC_NO_ERROR;
}
