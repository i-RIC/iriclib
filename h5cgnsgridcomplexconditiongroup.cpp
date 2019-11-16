#include "h5cgnsgridcomplexconditiongroup.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsgridcomplexconditiongroup_impl.h"

using namespace iRICLib;

H5CgnsGridComplexConditionGroup::H5CgnsGridComplexConditionGroup(hid_t groupId, const std::string& name, H5CgnsGridComplexConditionTop* top) :
	impl {new Impl {}}
{
	impl->m_groupId = groupId;
	impl->m_name = name;
	impl->m_top = top;

	impl->loadItems();
}

H5CgnsGridComplexConditionGroup::~H5CgnsGridComplexConditionGroup()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(impl->m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsGridComplexConditionGroup::~H5CgnsGridComplexConditionGroup", "H5Gclose", status);
	}

	delete impl;
}

H5CgnsConditionGroup* H5CgnsGridComplexConditionGroup::item(int num)
{
	if (num > 0 && num <= static_cast<int> (impl->m_items.size())) {
		return impl->m_items.at(num - 1);
	}
	return impl->createItem(num);
}

int H5CgnsGridComplexConditionGroup::itemCount() const
{
	return static_cast<int> (impl->m_items.size());
}
