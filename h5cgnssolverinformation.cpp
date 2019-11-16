#include "error_macros.h"
#include "h5cgnssolverinformation.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnssolverinformation_impl.h"

using namespace iRICLib;

H5CgnsSolverInformation::H5CgnsSolverInformation(hid_t groupId) :
	impl {new Impl {}}
{
	impl->m_groupId = groupId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, &(impl->m_names));
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
}

H5CgnsSolverInformation::~H5CgnsSolverInformation()
{
	delete impl;
}

int H5CgnsSolverInformation::readSolverName(std::string* name)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, "Name", name);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsSolverInformation::readSolverVersion(std::string* version)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, "Version", version);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsSolverInformation::writeSolverName(const std::string& name)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::updateOrCreateDataArray");
	int ier = H5Util::updateOrCreateDataArray(impl->m_groupId, "Name", name, &(impl->m_names));
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::updateOrCreateDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsSolverInformation::writeSolverVersion(const std::string& version)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::updateOrCreateDataArray");
	int ier = H5Util::updateOrCreateDataArray(impl->m_groupId, "Version", version, &(impl->m_names));
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::updateOrCreateDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
