#include "../error_macros.h"
#include "../h5cgnsgeographicdatagroup.h"
#include "../h5util.h"
#include "../iriclib_errorcodes.h"
#include "../internal/iric_logger.h"

#include "h5cgnsgeographicdatatop_impl.h"

using namespace iRICLib;

H5CgnsGeographicDataTop::Impl::Impl(H5CgnsGeographicDataTop* top) :
	m_top {top}
{}

H5CgnsGeographicDataTop::Impl::~Impl()
{
	for (const auto& pair : m_groups) {
		delete pair.second;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status =  H5Gclose(m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsGeographicDataTop::Impl::~Impl", "H5Gclose", status);
	}
}

int H5CgnsGeographicDataTop::Impl::loadGroups()
{
	std::vector<std::string> names;
	int ier = H5Util::getGroupNames(m_groupId, &names);
	RETURN_IF_ERR;

	for (const auto& name : names) {
		hid_t gId;
		ier = H5Util::openGroup(m_groupId, name, H5Util::userDefinedDataLabel(), &gId);
		RETURN_IF_ERR;

		auto g = new H5CgnsGeographicDataGroup(gId);
		m_groups.insert({name, g});
	}

	return IRIC_NO_ERROR;
}

H5CgnsGeographicDataGroup* H5CgnsGeographicDataTop::Impl::createGroup(const std::string& name)
{
	hid_t gId;
	int ier = H5Util::createUserDefinedDataGroup(m_groupId, name, &gId);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto g = new H5CgnsGeographicDataGroup(gId);
	m_groups.insert({name, g});

	return g;
}
