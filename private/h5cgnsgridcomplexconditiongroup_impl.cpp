#include "../h5cgnsbase.h"
#include "../h5cgnsconditiongroup.h"
#include "../h5cgnsfile.h"
#include "../h5cgnsgridcomplexconditiontop.h"
#include "../h5util.h"
#include "../iriclib_errorcodes.h"

#include "../internal/iric_logger.h"
#include <set>

#include "h5cgnsgridcomplexconditiongroup_impl.h"

#include <sstream>

using namespace iRICLib;

H5CgnsGridComplexConditionGroup::Impl::Impl()
{}

H5CgnsGridComplexConditionGroup::Impl::~Impl()
{
	for (auto i : m_items) {
		delete i;
	}
}

void H5CgnsGridComplexConditionGroup::Impl::loadItems()
{
	std::set<std::string> names;
	H5Util::getGroupNames(m_groupId, &names);

	int i = 1;
	while (true) {
		auto tmpName = itemName(i);
		if (names.find(tmpName) == names.end()) {break;}

		openItem(i, true);
		++ i;
	}
}

H5CgnsConditionGroup* H5CgnsGridComplexConditionGroup::Impl::openItem(int num, bool noErrorLog)
{
	if (num != static_cast<int>(m_items.size() + 1)) {return nullptr;}

	auto name = itemName(num);

	hid_t gid;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, name, H5Util::userDefinedDataLabel(), &gid, noErrorLog);
	_IRIC_LOGGER_TRACE_CALL_END("H5Util::openGroup");
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto g = new H5CgnsConditionGroup(name, gid, m_top->base()->file()->mode());
	m_items.push_back(g);

	return g;
}

H5CgnsConditionGroup* H5CgnsGridComplexConditionGroup::Impl::createItem(int num)
{
	if (num != static_cast<int> (m_items.size() + 1)) {return nullptr;}

	auto mode = m_top->base()->file()->mode();

	if (mode == H5CgnsFile::Mode::OpenReadOnly) {
		std::ostringstream ss;
		ss << "in H5CgnsGridComplexConditionGroup::Impl::createItem(), mode is OpenReadOnly";
		return nullptr;
	}
	auto name = itemName(num);

	hid_t gid;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createUserDefinedDataGroup");
	int ier =  H5Util::createUserDefinedDataGroup(m_groupId, name, &gid);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createUserDefinedDataGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto g = new H5CgnsConditionGroup(name, gid, m_top->base()->file()->mode());
	m_items.push_back(g);

	return g;
}

std::string H5CgnsGridComplexConditionGroup::Impl::itemName(int num)
{
	std::ostringstream ss;
	ss << "Item" << num;

	return ss.str();
}
