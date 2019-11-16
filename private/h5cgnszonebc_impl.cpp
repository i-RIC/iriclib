#include "../h5cgnsbc.h"
#include "../h5util.h"
#include "../iriclib_errorcodes.h"

#include "../internal/iric_logger.h"

#include "h5cgnszonebc_impl.h"

#include <sstream>
#include <vector>

#define BC_DATA "UserDefined"

using namespace iRICLib;

H5CgnsZoneBc::Impl::Impl(H5CgnsZoneBc* zoneBc) :
	m_groupId {-1},
	m_zone {nullptr},
	m_zoneBc {zoneBc}
{}

H5CgnsZoneBc::Impl::~Impl()
{
	clear();

	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsZoneBc::Impl::~Impl", "H5Gclose", status);
	}
}

void H5CgnsZoneBc::Impl::loadBcs()
{
	std::vector<std::string> names;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(m_groupId, &names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	for (const auto& name : names) {
		hid_t gId;
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
		int ier = H5Util::openGroup(m_groupId, name, H5CgnsBc::label(), &gId, true);
		_IRIC_LOGGER_TRACE_CALL_END("H5Util::openGroup");

		if (ier != IRIC_NO_ERROR) {continue;}

		auto bc = new H5CgnsBc(name, gId, m_zoneBc);
		m_bcMap.insert({name, bc});
	}
}

H5CgnsBc* H5CgnsZoneBc::Impl::createBc(const std::string& name)
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
	int ier = H5Util::createGroupWithValue(m_groupId, name, H5CgnsBc::label(), BC_DATA, &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto bc = new H5CgnsBc(name, gId, m_zoneBc);
	m_bcMap.insert({name, bc});
	return bc;
}

void H5CgnsZoneBc::Impl::clear()
{
	for (const auto& bc : m_bcMap) {
		delete bc.second;
	}
	m_bcMap.clear();
}

std::string H5CgnsZoneBc::Impl::name(const std::string& typeName, int num)
{
	std::ostringstream ss;
	ss << typeName << "_" << num;
	return ss.str();
}
