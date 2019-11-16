#include "error_macros.h"
#include "h5cgnsgeographicdatagroup.h"
#include "h5groupcloser.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsgeographicdatagroup_impl.h"

#include <sstream>

using namespace iRICLib;

H5CgnsGeographicDataGroup::H5CgnsGeographicDataGroup(hid_t groupId) :
	impl {new Impl {}}
{
	impl->m_groupId = groupId;
}

H5CgnsGeographicDataGroup::~H5CgnsGeographicDataGroup()
{
	delete impl;
}

int H5CgnsGeographicDataGroup::count(int* count) const
{
	std::vector<std::string> names;
	int ier = H5Util::getGroupNames(impl->m_groupId, &names);
	RETURN_IF_ERR;

	*count = static_cast<int> (names.size());
	return IRIC_NO_ERROR;
}

int H5CgnsGeographicDataGroup::read(int id, std::string* filename, Type* type)
{
	std::ostringstream ss;
	ss << id;

	hid_t gId;
	int ier = H5Util::openGroup(impl->m_groupId, ss.str(), H5Util::userDefinedDataLabel(), &gId);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	ier = H5Util::readDataArrayValue(gId, "filename", filename);
	RETURN_IF_ERR;

	std::vector<int> buffer;
	ier = H5Util::readDataArrayValue(gId, "type", &buffer);
	RETURN_IF_ERR;

	if (buffer.size() < 1) {
		std::ostringstream ss;
		ss << "In H5CgnsGeographicDataGroup::read(), type has no value";
		_iric_logger_error(ss.str());

		return IRIC_DATA_NOT_FOUND;
	}
	*type = static_cast<Type> (buffer.at(0));

	return IRIC_NO_ERROR;
}

int H5CgnsGeographicDataGroup::add(const std::string& filename, Type type)
{
	int id = impl->m_count + 1;

	std::ostringstream ss;
	ss << id;

	hid_t gId;
	int ier = H5Util::createUserDefinedDataGroup(impl->m_groupId, ss.str(), &gId);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	ier = H5Util::createDataArray(gId, "filename", filename);
	RETURN_IF_ERR;

	std::vector<int> buffer;
	buffer.push_back(static_cast<int> (type));
	ier = H5Util::createDataArray(gId, "type", buffer);

	++ impl->m_count;

	return IRIC_NO_ERROR;
}

int H5CgnsGeographicDataGroup::clear()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::deleteAllChildren");
	int ier = H5Util::deleteAllChildren(impl->m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::deleteAllChildren", ier);
	RETURN_IF_ERR;

	impl->m_count = 0;

	return IRIC_NO_ERROR;
}
