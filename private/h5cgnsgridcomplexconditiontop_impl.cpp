#include "../h5cgnsbase.h"
#include "../h5cgnsfile.h"
#include "../h5cgnsgridcomplexconditiongroup.h"
#include "../h5util.h"
#include "../iriclib_errorcodes.h"

#include "../internal/iric_logger.h"

#include "h5cgnsgridcomplexconditiontop_impl.h"

#include <sstream>

using namespace iRICLib;

H5CgnsGridComplexConditionTop::Impl::Impl(H5CgnsGridComplexConditionTop* top) :
	m_top {top}
{}

H5CgnsGridComplexConditionTop::Impl::~Impl()
{
	clear();
}

void H5CgnsGridComplexConditionTop::Impl::loadGroups()
{
	std::vector<std::string> names;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(m_groupId, &names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);

	if (ier != IRIC_NO_ERROR) {return;}

	for (const auto& name : names) {
		openGroup(name);
	}
}

void H5CgnsGridComplexConditionTop::Impl::clear()
{
	for (auto& pair : m_groupMap) {
		delete pair.second;
	}
	m_groupMap.clear();
}

H5CgnsGridComplexConditionGroup* H5CgnsGridComplexConditionTop::Impl::openOrCreateGroup(const std::string& name)
{
	auto mode = m_base->file()->mode();
	if (mode == H5CgnsFile::Mode::Create) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridComplexConditionTop::Impl::createGroup");
		auto ret = createGroup(name);
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsGridComplexConditionTop::Impl::createGroup");
		return ret;
	} else if (mode == H5CgnsFile::Mode::OpenReadOnly) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridComplexConditionTop::Impl::openGroup");
		auto ret = openGroup(name);
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsGridComplexConditionTop::Impl::openGroup");
		return ret;
	} else {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridComplexConditionTop::Impl::openGroup");
		auto ret = openGroup(name);
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsGridComplexConditionTop::Impl::openGroup");

		if (ret != nullptr) {return ret;}

		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridComplexConditionTop::Impl::createGroup");
		ret = createGroup(name);
		_IRIC_LOGGER_TRACE_CALL_END("H5CgnsGridComplexConditionTop::Impl::createGroup");

		return ret;
	}
}

H5CgnsGridComplexConditionGroup* H5CgnsGridComplexConditionTop::Impl::openGroup(const std::string& name)
{
	hid_t gId;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(m_groupId, name, H5Util::userDefinedDataLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto g = new H5CgnsGridComplexConditionGroup(gId, name, m_top);
	m_groupMap.insert({name, g});

	return g;
}

H5CgnsGridComplexConditionGroup* H5CgnsGridComplexConditionTop::Impl::createGroup(const std::string& name)
{
	auto mode = m_base->file()->mode();
	if (mode == H5CgnsFile::Mode::OpenReadOnly) {
		std::ostringstream ss;
		ss << "In H5CgnsGridComplexConditionTop::Impl::createGroup(), mode is OpenReadOnly";
		_iric_logger_error(ss.str());
		return nullptr;
	}
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroup");
	int ier = H5Util::createGroup(m_groupId, name, H5Util::userDefinedDataLabel(), H5Util::userDefinedDataType(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroup", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	auto g = new H5CgnsGridComplexConditionGroup(gId, name, m_top);
	m_groupMap.insert({name, g});

	return g;
}
