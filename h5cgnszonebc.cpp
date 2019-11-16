#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsfile.h"
#include "h5cgnszone.h"
#include "h5cgnszonebc.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnszonebc_impl.h"

using namespace iRICLib;

#define ZONEBC_NAME "ZoneBC"
#define ZONEBC_LABEL "ZoneBC_t"

std::string H5CgnsZoneBc::name()
{
	return ZONEBC_NAME;
}

std::string H5CgnsZoneBc::label()
{
	return ZONEBC_LABEL;
}

H5CgnsZoneBc::H5CgnsZoneBc(hid_t groupId, H5CgnsZone* zone) :
	impl {new Impl {this}}
{
	impl->m_groupId = groupId;
	impl->m_zone = zone;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsZoneBc::Impl::loadBcs");
	impl->loadBcs();
	_IRIC_LOGGER_TRACE_CALL_END("H5CgnsZoneBc::Impl::loadBcs");
}

H5CgnsZoneBc::~H5CgnsZoneBc()
{
	delete impl;
}

int H5CgnsZoneBc::bcCount(const std::string& typeName) const
{
	int id = 1;
	while (true) {
		bool e = bcExists(typeName, id);
		if (! e) {break;}

		++ id;
	}
	return id - 1;
}

H5CgnsBc* H5CgnsZoneBc::bc(const std::string& typeName, int num)
{
	auto name = impl->name(typeName, num);
	auto it = impl->m_bcMap.find(name);
	if (it != impl->m_bcMap.end()) {return it->second;}

	if (impl->m_zone->base()->file()->mode() == H5CgnsFile::Mode::OpenReadOnly) {return nullptr;}

	return impl->createBc(name);
}

bool H5CgnsZoneBc::bcExists(const std::string& typeName, int num) const
{
	auto name = impl->name(typeName, num);
	auto it = impl->m_bcMap.find(name);
	return it != impl->m_bcMap.end();
}

int H5CgnsZoneBc::clear()
{
	impl->clear();

	int ier = H5Util::deleteAllChildren(impl->m_groupId);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

H5CgnsZone* H5CgnsZoneBc::zone() const
{
	return impl->m_zone;
}
