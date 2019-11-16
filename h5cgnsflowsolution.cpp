#include "error_macros.h"
#include "h5cgnsflowsolution.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsflowsolution_impl.h"

using namespace iRICLib;

#define LABEL "FlowSolution_t"

std::string H5CgnsFlowSolution::label()
{
	return LABEL;
}

H5CgnsFlowSolution::H5CgnsFlowSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	impl {new Impl {}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_zone = zone;
}

H5CgnsFlowSolution::~H5CgnsFlowSolution()
{
	H5Gclose(impl->m_groupId);
	delete impl;
}

std::string H5CgnsFlowSolution::name() const
{
	return impl->m_name;
}

int H5CgnsFlowSolution::readValueNames(std::vector<std::string>* names) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFlowSolution::readValueNames(std::set<std::string>* names) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFlowSolution::readValueType(const std::string& name, H5Util::DataArrayValueType *type) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValueType");
	int ier = H5Util::readDataArrayValueType(impl->m_groupId, name, type);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValueType", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFlowSolution::readValue(const std::string& name, std::vector<int>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFlowSolution::readValue(const std::string& name, std::vector<double>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFlowSolution::readValueAsDouble(const std::string& name, std::vector<double>* values) const
{
	H5Util::DataArrayValueType type;
	int ier = readValueType(name, &type);
	RETURN_IF_ERR;

	if (type == H5Util::DataArrayValueType::RealDouble) {
		return readValue(name, values);
	} else if (type == H5Util::DataArrayValueType::Int) {
		std::vector<int> buffer;
		ier = readValue(name, &buffer);
		RETURN_IF_ERR;

		values->assign(buffer.size(), 0);
		for (unsigned int i = 0; i < buffer.size(); ++i) {
			(*values)[i] = buffer.at(i);
		}
	}
	return IRIC_NO_ERROR;
}

int H5CgnsFlowSolution::writeValue(const std::string& name, const std::vector<int>& values) const
{
	std::vector<hsize_t> dims;
	int ier = dataDims(&dims);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, name, values, dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFlowSolution::writeValue(const std::string& name, const std::vector<double>& values) const
{
	std::vector<hsize_t> dims;
	int ier = dataDims(&dims);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, name, values, dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

H5CgnsZone* H5CgnsFlowSolution::zone() const
{
	return impl->m_zone;
}
