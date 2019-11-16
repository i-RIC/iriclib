#include "h5cgnsgeographicdatatop.h"

#include "private/h5cgnsgeographicdatatop_impl.h"

using namespace iRICLib;

H5CgnsGeographicDataTop::H5CgnsGeographicDataTop(hid_t groupId, H5CgnsBase* base) :
	impl {new Impl {this}}
{
	impl->m_groupId = groupId;
	impl->m_base = base;

	impl->loadGroups();
}

H5CgnsGeographicDataTop::~H5CgnsGeographicDataTop()
{
	delete impl;
}

std::vector<std::string> H5CgnsGeographicDataTop::groupNames() const
{
	std::vector<std::string> ret;

	for (const auto& pair : impl->m_groups) {
		ret.push_back(pair.first);
	}

	return ret;
}

bool H5CgnsGeographicDataTop::groupExists(const std::string& name) const
{
	auto it = impl->m_groups.find(name);
	return (it != impl->m_groups.end());
}

H5CgnsGeographicDataGroup* H5CgnsGeographicDataTop::group(const std::string& name)
{
	auto it = impl->m_groups.find(name);
	if (it != impl->m_groups.end()) {return it->second;}

	return impl->createGroup(name);
}

H5CgnsBase* H5CgnsGeographicDataTop::base() const
{
	return impl->m_base;
}
