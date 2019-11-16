#include "error_macros.h"
#include "h5cgnsgridcomplexconditiontop.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "private/h5cgnsgridcomplexconditiontop_impl.h"

using namespace iRICLib;

H5CgnsGridComplexConditionTop::H5CgnsGridComplexConditionTop(hid_t groupId, H5CgnsBase* base) :
	impl {new Impl {this}}
{
	impl->m_groupId = groupId;
	impl->m_base = base;

	impl->loadGroups();
}

H5CgnsGridComplexConditionTop::~H5CgnsGridComplexConditionTop()
{
	H5Gclose(impl->m_groupId);
	delete impl;
}

H5CgnsGridComplexConditionGroup* H5CgnsGridComplexConditionTop::group(const std::string& name)
{
	auto it = impl->m_groupMap.find(name);
	if (it != impl->m_groupMap.end()) {return it->second;}

	return impl->createGroup(name);
}

bool H5CgnsGridComplexConditionTop::groupExists(const std::string& name) const
{
	auto it = impl->m_groupMap.find(name);
	return (it != impl->m_groupMap.end());
}

int H5CgnsGridComplexConditionTop::clear()
{
	impl->clear();

	int ier = H5Util::deleteAllChildren(impl->m_groupId);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

H5CgnsBase* H5CgnsGridComplexConditionTop::base() const
{
	return impl->m_base;
}
