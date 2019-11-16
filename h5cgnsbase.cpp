#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsbaseiterativedata.h"
#include "h5cgnsconditiongroup.h"
#include "h5cgnsfile.h"
#include "h5groupcloser.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include <hdf5.h>

#include <set>
#include <sstream>

#include "private/h5cgnsbase_impl.h"

using namespace iRICLib;

#define LABEL "CGNSBase_t"
#define DEFAULT_ZONE_NAME "iRICZone"
#define ERRORCODE_NAME "ErrorCode"

std::string H5CgnsBase::label()
{
	return LABEL;
}

H5CgnsBase::H5CgnsBase(int dimension, const std::string &name, hid_t groupId, H5CgnsFile* file) :
	impl {new Impl {this}}
{
	impl->m_dimension = dimension;
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_file = file;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::loadNames");
	impl->loadNames();
	_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::loadNames");

	if (dimension == 2) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openOrCreateCcGroup");
		impl->openOrCreateCcGroup();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openOrCreateCcGroup");

		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openOrCreateGeoDataTop");
		impl->openOrCreateGeoDataTop();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openOrCreateGeoDataTop");

		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openOrCreateSolverInformation");
		impl->openOrCreateSolverInformation();
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openOrCreateSolverInformation");
	}
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::openOrCreateGccTop");
	impl->openOrCreateGccTop();
	_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::openOrCreateGccTop");

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::clearNames");
	impl->clearNames();
	_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::clearNames");

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::Impl::loadZones");
	impl->loadZones();
	_IRIC_LOGGER_TRACE_CALL_END("H5CgnsBase::Impl::loadZones");
}

H5CgnsBase::~H5CgnsBase()
{
	delete impl;
}

int H5CgnsBase::dimension() const
{
	return impl->m_dimension;
}

std::string H5CgnsBase::name() const
{
	return impl->m_name;
}

H5CgnsConditionGroup* H5CgnsBase::ccGroup() const
{
	return impl->m_ccGroup;
}

H5CgnsGridComplexConditionTop* H5CgnsBase::gccTop() const
{
	return impl->m_gccTop;
}

H5CgnsBaseIterativeData* H5CgnsBase::biterData()
{
	if (impl->m_biterData != nullptr) {return impl->m_biterData;}

	std::set<std::string> names;
	H5Util::getGroupNames(impl->m_groupId, &names);

	if (impl->m_file->mode() == H5CgnsFile::Mode::Create) {
		impl->m_biterData = impl->createBaseIterativeData();
	} else if (impl->m_file->mode() == H5CgnsFile::Mode::OpenReadOnly) {
		if (names.find(H5CgnsBaseIterativeData::groupName()) == names.end()) {return nullptr;}

		hid_t gid;
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
		int ier = H5Util::openGroup(impl->m_groupId, H5CgnsBaseIterativeData::groupName(), H5CgnsBaseIterativeData::label(), &gid);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
		if (ier == IRIC_NO_ERROR) {
			impl->m_biterData = new H5CgnsBaseIterativeData(gid, this);
		}
	} else if (impl->m_file->mode() == H5CgnsFile::Mode::OpenModify) {
		if (names.find(H5CgnsBaseIterativeData::groupName()) == names.end()) {
			impl->m_biterData = impl->createBaseIterativeData();
		} else {
			hid_t gid;
			_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
			int ier = H5Util::openGroup(impl->m_groupId, H5CgnsBaseIterativeData::groupName(), H5CgnsBaseIterativeData::label(), &gid);
			_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
			if (ier != IRIC_NO_ERROR) {return nullptr;}

			impl->m_biterData = new H5CgnsBaseIterativeData(gid, this);
		}
	}
	return impl->m_biterData;
}

H5CgnsGeographicDataTop* H5CgnsBase::geoDataTop() const
{
	return impl->m_geoDataTop;
}

H5CgnsSolverInformation* H5CgnsBase::solverInformation() const
{
	return impl->m_solverInformation;
}

int H5CgnsBase::writeErrorCode(int errorCode)
{
	int gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openOrCreateUserDefinedDataGroup");
	int ier = H5Util::createUserDefinedDataGroup(impl->m_groupId, ERRORCODE_NAME, &gId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Util::openOrCreateUserDefinedDataGroup");
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	std::vector<int> data;
	data.push_back(errorCode);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::updateOrCreateDataArray");
	ier = H5Util::updateOrCreateDataArray(gId, "Value", data);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::updateOrCreateDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsBase::readErrorCode(int* errorCode)
{
	int gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openOrCreateUserDefinedDataGroup");
	int ier = H5Util::openGroup(impl->m_groupId, ERRORCODE_NAME, H5Util::userDefinedDataLabel(), &gId, true);
	_IRIC_LOGGER_TRACE_CALL_END("H5Util::openOrCreateUserDefinedDataGroup");

	if (ier != IRIC_NO_ERROR) {
		// no error code is output.
		*errorCode = 0;
		return IRIC_NO_ERROR;
	}

	H5GroupCloser closer(gId);

	std::vector<int> data;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::updateOrCreateDataArray");
	ier = H5Util::readDataArrayValue(gId, "Value", &data);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::updateOrCreateDataArray", ier);
	RETURN_IF_ERR;

	if (data.size() < 1) {
		std::ostringstream ss;
		ss << "In H5CgnsBase::readErrorCode(), data length == 0";
		_iric_logger_error(ss.str());

		return IRIC_NO_DATA;
	}
	*errorCode = data.at(0);

	return IRIC_NO_ERROR;
}

int H5CgnsBase::zoneNum() const
{
	return static_cast<int> (impl->m_zones.size());
}

H5CgnsZone* H5CgnsBase::zoneById(int zid)
{
	if (zid < 1 || zid > static_cast<int> (impl->m_zones.size())) {return nullptr;}

	return impl->m_zones.at(zid - 1);
}

std::vector<std::string> H5CgnsBase::zoneNames() const
{
	std::vector<std::string> ret;

	for (const auto& pair : impl->m_zoneMap) {
		ret.push_back(pair.first);
	}

	return ret;
}

H5CgnsZone* H5CgnsBase::defaultZone()
{
	return zone(DEFAULT_ZONE_NAME);
}

H5CgnsZone* H5CgnsBase::zone(const std::string& name)
{
	auto it = impl->m_zoneMap.find(name);
	if (it == impl->m_zoneMap.end()) {return nullptr;}

	return it->second;
}

bool H5CgnsBase::zoneExists(const std::string& name)
{
	auto it = impl->m_zoneMap.find(name);
	return it != impl->m_zoneMap.end();
}

H5CgnsZone* H5CgnsBase::createDefaultZone(H5CgnsZone::Type type, const std::vector<int> &size)
{
	return createZone(nextDefaultName(), type, size);
}

H5CgnsZone* H5CgnsBase::createZone(const std::string& name, H5CgnsZone::Type type, const std::vector<int>& size)
{
	return impl->createZone(name, type, size);
}

std::string H5CgnsBase::nextDefaultName()
{
	if (impl->m_zones.size() == 0) {
		return DEFAULT_ZONE_NAME;
	} else {
		std::ostringstream ss;
		ss << DEFAULT_ZONE_NAME << impl->m_zones.size() + 1;
		return ss.str();
	}
}

int H5CgnsBase::setSolutionId(int solutionId)
{
	for (auto zone : impl->m_zones) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsZone::setSolutionId");
		int ier = zone->setSolutionId(solutionId);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsZone::setSolutionId", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

int H5CgnsBase::copyGridsTo(H5CgnsBase* target)
{
	for (auto zone : impl->m_zones) {
		auto zone2 = target->createZone(zone->name(), zone->type(), zone->size());
		int ier = zone->copyGridTo(zone2);
		RETURN_IF_ERR;
	}
	return IRIC_NO_ERROR;
}

int H5CgnsBase::flush()
{
	if (impl->m_biterData != nullptr) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBaseIterativeData::flush");
		int ier = impl->m_biterData->flush();
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBaseIterativeData::flush", ier);
		RETURN_IF_ERR;
	}

	for (auto zone : impl->m_zones) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsZone::flush");
		int ier = zone->flush();
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsZone::flush", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

H5CgnsFile* H5CgnsBase::file() const
{
	return impl->m_file;
}
