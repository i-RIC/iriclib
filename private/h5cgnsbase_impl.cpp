#include "../h5cgnsbaseiterativedata.h"
#include "../h5cgnsconditiongroup.h"
#include "../h5cgnsfile.h"
#include "../h5cgnsgeographicdatatop.h"
#include "../h5cgnsgridcomplexconditiontop.h"
#include "../h5cgnssolverinformation.h"
#include "../h5util.h"
#include "../iriclib_errorcodes.h"

#include "../internal/iric_logger.h"

#include "h5cgnsbase_impl.h"
#include "h5cgnsfile_impl.h"

using namespace iRICLib;

namespace {

#define CCNAME "CalculationConditions"
#define GCCNAME "GridComplexConditions"
#define GEODATANAME "GeographicData"
#define SOLVERINFONAME "SolverInformation"

} // namespace

H5CgnsBase::Impl::Impl(H5CgnsBase* base):
	m_gccTop {nullptr},
	m_ccGroup {nullptr},
	m_biterData {nullptr},
	m_geoDataTop {nullptr},
	m_solverInformation {nullptr},
	m_file {nullptr},
	m_base {base}
{}

H5CgnsBase::Impl::~Impl()
{
	delete m_gccTop;
	delete m_ccGroup;
	delete m_geoDataTop;
	delete m_biterData;
	delete m_solverInformation;

	for (auto zone : m_zones) {
		delete zone;
	}

	m_zones.clear();
	m_zoneMap.clear();

	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status =  H5Gclose(m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsBase::Impl::~Impl", "H5Gclose", status);
	}
}

void H5CgnsBase::Impl::openOrCreateCcGroup()
{
	if (m_file->mode() == H5CgnsFile::Mode::Create) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::createCcGroup");
		createCcGroup();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::createCcGroup");
	} else if (m_file->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openCcGroup");
		openCcGroup();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openCcGroup");
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openCcGroup");
		openCcGroup();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openCcGroup");
		if (m_ccGroup == nullptr) {
			_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::createCcGroup");
			createCcGroup();
			_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::createCcGroup");
		}
	}
}

void H5CgnsBase::Impl::openCcGroup()
{
	if (m_names.find(CCNAME) == m_names.end()) {return;}

	hid_t ccGroupId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, CCNAME, H5Util::userDefinedDataLabel(), &ccGroupId, true);
	_IRIC_LOGGER_TRACE_CALL_END("H5Util::openGroup");
	if (ier != IRIC_NO_ERROR) {return;}

	m_ccGroup = new H5CgnsConditionGroup(CCNAME, ccGroupId, m_file->mode());
}

void H5CgnsBase::Impl::createCcGroup()
{
	hid_t ccGroupId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier = H5Util::createUserDefinedDataGroup(m_groupId, CCNAME, &ccGroupId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	m_ccGroup = new H5CgnsConditionGroup(CCNAME, ccGroupId, m_file->mode());
}

void H5CgnsBase::Impl::openOrCreateGccTop()
{
	if (m_file->mode() == H5CgnsFile::Mode::Create) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::createGccTop");
		createGccTop();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::createGccTop");
	} else if (m_file->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openGccTop");
		openGccTop();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openGccTop");
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openGccTop");
		openGccTop();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openGccTop");
		if (m_gccTop == nullptr) {
			_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::createGccTop");
			createGccTop();
			_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::createGccTop");
		}
	}
}

void H5CgnsBase::Impl::openGccTop()
{
	if (m_names.find(GCCNAME) == m_names.end()) {return;}

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, GCCNAME, H5Util::userDefinedDataLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	m_gccTop = new H5CgnsGridComplexConditionTop(gId, m_base);
}

void H5CgnsBase::Impl::createGccTop()
{
	hid_t gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier = H5Util::createUserDefinedDataGroup(m_groupId, GCCNAME, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	m_gccTop = new H5CgnsGridComplexConditionTop(gId, m_base);
}

void H5CgnsBase::Impl::openOrCreateGeoDataTop()
{
	if (m_file->mode() == H5CgnsFile::Mode::Create) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::createGeoDataTop");
		createGeoDataTop();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::createGeoDataTop");
	} else if (m_file->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openGeoDataTop");
		openGeoDataTop();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openGeoDataTop");
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openGeoDataTop");
		openGeoDataTop();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openGeoDataTop");
		if (m_geoDataTop == nullptr) {
			_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::createGeoDataTop");
			createGeoDataTop();
			_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::createGeoDataTop");
		}
	}
}

void H5CgnsBase::Impl::openGeoDataTop()
{
	if (m_names.find(GEODATANAME) == m_names.end()) {return;}

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, GEODATANAME, H5Util::userDefinedDataLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	m_geoDataTop = new H5CgnsGeographicDataTop(gId, m_base);
}

void H5CgnsBase::Impl::createGeoDataTop()
{
	hid_t gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier = H5Util::createUserDefinedDataGroup(m_groupId, GEODATANAME, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	m_geoDataTop = new H5CgnsGeographicDataTop(gId, m_base);
}

void H5CgnsBase::Impl::openOrCreateSolverInformation()
{
	if (m_file->mode() == H5CgnsFile::Mode::Create) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::createSolverInformation");
		createSolverInformation();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::createSolverInformation");
	} else if (m_file->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openSolverInformation");
		openSolverInformation();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openSolverInformation");
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openSolverInformation");
		openSolverInformation();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openSolverInformation");
		if (m_solverInformation == nullptr) {
			_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::createSolverInformation");
			createSolverInformation();
			_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::createSolverInformation");
		}
	}
}

void H5CgnsBase::Impl::openSolverInformation()
{
	if (m_names.find(SOLVERINFONAME) == m_names.end()) {return;}

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, SOLVERINFONAME, H5Util::userDefinedDataLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	m_solverInformation = new H5CgnsSolverInformation(gId);
}

void H5CgnsBase::Impl::createSolverInformation()
{
	hid_t gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier = H5Util::createUserDefinedDataGroup(m_groupId, SOLVERINFONAME, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	m_solverInformation = new H5CgnsSolverInformation(gId);
}

void H5CgnsBase::Impl::loadNames()
{
	H5Util::getGroupNames(m_groupId, &m_names);
}

void H5CgnsBase::Impl::clearNames()
{
	m_names.clear();
}

H5CgnsBaseIterativeData* H5CgnsBase::Impl::createBaseIterativeData()
{
	hid_t biterGroupId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
	int ier = H5Util::createGroupWithValue(m_groupId, H5CgnsBaseIterativeData::groupName(), H5CgnsBaseIterativeData::label(), 0, &biterGroupId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	return new H5CgnsBaseIterativeData(biterGroupId, m_base);
}

void H5CgnsBase::Impl::loadZones()
{
	std::vector<std::string> names;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(m_groupId, &names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	for (const auto& name : names) {
		hid_t gId;
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
		int ier = H5Util::openGroup(m_groupId, name, H5CgnsZone::label(), &gId, true);
		_IRIC_LOGGER_TRACE_CALL_END("H5Util::openGroup");
		if (ier != IRIC_NO_ERROR) {continue;}

		auto z = new H5CgnsZone(name, gId, m_base);
		m_zones.push_back(z);
		m_zoneMap.insert({name, z});
	}
}

H5CgnsZone* H5CgnsBase::Impl::createZone(const std::string& name, H5CgnsZone::Type type, const std::vector<int>& size)
{
	if (m_file->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		_iric_logger_warn("In H5CgnsBase::Impl::createZone(), zone can not be created for CGNS file in read only mode.");
		return nullptr;
	}

	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = H5Util::createGroup(m_groupId, name, H5CgnsZone::label(), "I4", &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto z = new H5CgnsZone(name, type, size, gId, m_base);
	m_zones.push_back(z);
	m_zoneMap.insert({name, z});

	m_file->impl->m_zones.push_back(z);

	return z;
}
