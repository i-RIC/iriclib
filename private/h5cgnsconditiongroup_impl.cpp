#include "../error_macros.h"
#include "../h5groupcloser.h"
#include "../h5util.h"
#include "../iriclib_errorcodes.h"

#include "h5cgnsconditiongroup_impl.h"

using namespace iRICLib;

int H5CgnsConditionGroup::Impl::openOrCreateGroups(const std::string& name, const std::string& paramName, const std::string& dataType, hid_t* groupId)
{
	int ier;

	hid_t gId;
	if (m_names.find(name) == m_names.end()) {
		ier = H5Util::createUserDefinedDataGroup(m_groupId, name, &gId);
		RETURN_IF_ERR;

		m_names.insert(name);
	} else {
		ier = H5Util::openGroup(m_groupId, name, H5Util::userDefinedDataLabel(), &gId);
		RETURN_IF_ERR;
	}

	H5GroupCloser groupCloser(gId);

	std::set<std::string> tmpNames;
	H5Util::getGroupNames(gId, &tmpNames);

	if (tmpNames.find(paramName) == tmpNames.end()) {
		ier = H5Util::createGroup(gId, paramName, H5Util::dataArrayLabel(), dataType, groupId);
		RETURN_IF_ERR;
	} else {
		ier = H5Util::openGroup(gId, paramName, H5Util::dataArrayLabel(), groupId);
		RETURN_IF_ERR;
	}
	return IRIC_NO_ERROR;
}
