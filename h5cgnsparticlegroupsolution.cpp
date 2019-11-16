#include "error_macros.h"
#include "h5cgnsparticlegroupsolution.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsparticlegroupsolution_impl.h"
#include "public/h5cgnsparticlegroupsolution_groupreader.h"

#include <sstream>

using namespace iRICLib;

H5CgnsParticleGroupSolution::H5CgnsParticleGroupSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	impl {new Impl {}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_zone = zone;
}

H5CgnsParticleGroupSolution::~H5CgnsParticleGroupSolution()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(impl->m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsParticleGroupSolution::~H5CgnsParticleGroupSolution", "H5Gclose", status);
	}

	delete impl;
}

std::string H5CgnsParticleGroupSolution::name() const
{
	return impl->m_name;
}

int H5CgnsParticleGroupSolution::readGroupNames(std::vector<std::string>* names) const
{
	std::string coordXSuffix = "_coordinateX";
	std::vector<std::string> tmpNames;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, &tmpNames);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : tmpNames) {
		auto offset = name.length() - coordXSuffix.length();
		if (offset < 0) {continue;}

		auto suffix = name.substr(offset, coordXSuffix.length());
		if (suffix != coordXSuffix) {continue;}

		names->push_back(name.substr(0, offset));
	}

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::count(const std::string& groupName, int* count)
{
	std::ostringstream ss;
	ss << groupName << "_coordinateX";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayLength");
	int ier = H5Util::readDataArrayLength(impl->m_groupId, ss.str(), count);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readValueNames(const std::string& groupName, std::vector<std::string>* names) const
{
	std::ostringstream ss;
	ss << groupName << "__";
	auto prefix = ss.str();

	std::vector<std::string> tmpNames;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, &tmpNames);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : tmpNames) {
		if (name.substr(0, prefix.length()) != prefix) {
			continue;
		}
		names->push_back(name.substr(prefix.length()));
	}

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readValueNames(const std::string& groupName, std::set<std::string>* names) const
{
	std::vector<std::string> namesVec;
	int ier = readValueNames(groupName, &namesVec);
	RETURN_IF_ERR;

	for (const auto& n : namesVec) {
		names->insert(n);
	}

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readCoordinatesX(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_coordinateX";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readCoordinatesY(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_coordinateY";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readCoordinatesZ(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_coordinateZ";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readValueType(const std::string& groupName, const std::string& valueName, H5Util::DataArrayValueType *type) const
{
	std::ostringstream ss;
	ss << groupName << "__" << valueName;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValueType");
	int ier = H5Util::readDataArrayValueType(impl->m_groupId, ss.str(), type);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValueType", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readValue(const std::string& groupName, const std::string& valueName, std::vector<int>* values) const
{
	std::ostringstream ss;
	ss << groupName << "__" << valueName;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readValue(const std::string& groupName, const std::string& valueName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "__" << valueName;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleGroupSolution::readValueAsDouble(const std::string& groupName, const std::string& valueName, std::vector<double>* values) const
{
	H5Util::DataArrayValueType type;
	int ier = readValueType(groupName, valueName, &type);
	RETURN_IF_ERR;

	if (type == H5Util::DataArrayValueType::RealDouble) {
		return readValue(groupName, valueName, values);
	} else if (type == H5Util::DataArrayValueType::Int) {
		std::vector<int> buffer;
		ier = readValue(groupName, valueName, &buffer);
		RETURN_IF_ERR;

		values->assign(buffer.size(), 0);
		for (unsigned int i = 0; i < buffer.size(); ++i) {
			(*values)[i] = buffer.at(i);
		}
	}
	return IRIC_NO_ERROR;
}

void H5CgnsParticleGroupSolution::writeBegin(const std::string& groupName)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsParticleGroupSolution::Impl::clear");
	impl->clear();
	_IRIC_LOGGER_TRACE_CALL_END("H5CgnsParticleGroupSolution::Impl::clear");

	impl->m_groupName = groupName;
}

int H5CgnsParticleGroupSolution::writeEnd()
{
	std::ostringstream ss;
	int ier;

	// coordinateX
	ss.str("");
	ss << impl->m_groupName << "_coordinateX";

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_coordinateX);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	// coordinateY
	ss.str("");
	ss << impl->m_groupName << "_coordinateY";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_coordinateY);
	RETURN_IF_ERR;

	// coordinateY
	if (impl->m_coordinateZ.size() != 0) {
		ss.str("");
		ss << impl->m_groupName << "_coordinateZ";
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
		ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_coordinateZ);
		RETURN_IF_ERR;
	}

	// integer values
	for (const auto& pair : impl->m_intValues) {
		const auto& name = pair.first;
		const auto& vals = pair.second;

		ss.str("");
		ss << impl->m_groupName << "__" << name;
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
		ier = H5Util::createDataArray(impl->m_groupId, ss.str(), vals);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
		RETURN_IF_ERR;
	}

	// real values
	for (const auto& pair : impl->m_realValues) {
		const auto& name = pair.first;
		const auto& vals = pair.second;

		ss.str("");
		ss << impl->m_groupName << "__" << name;
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
		ier = H5Util::createDataArray(impl->m_groupId, ss.str(), vals);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

void H5CgnsParticleGroupSolution::writePos2d(double x, double y)
{
	impl->m_coordinateX.push_back(x);
	impl->m_coordinateY.push_back(y);
}

void H5CgnsParticleGroupSolution::writePos3d(double x, double y, double z)
{
	impl->m_coordinateX.push_back(x);
	impl->m_coordinateY.push_back(y);
	impl->m_coordinateZ.push_back(z);
}

void H5CgnsParticleGroupSolution::writeValue(const std::string& name, int value)
{
	std::vector<int>* vals = nullptr;

	auto it = impl->m_intValues.find(name);
	if (it != impl->m_intValues.end()) {
		vals = &(it->second);
	} else {
		std::vector<int> empty;
		auto it2 = impl->m_intValues.insert({name, empty});
		vals = &(it2.first->second);
	}
	vals->push_back(value);
}

void H5CgnsParticleGroupSolution::writeValue(const std::string& name, double value)
{
	std::vector<double>* vals = nullptr;

	auto it = impl->m_realValues.find(name);
	if (it != impl->m_realValues.end()) {
		vals = &(it->second);
	} else {
		std::vector<double> empty;
		auto it2 = impl->m_realValues.insert({name, empty});
		vals = &(it2.first->second);
	}
	vals->push_back(value);
}

H5CgnsZone* H5CgnsParticleGroupSolution::zone() const
{
	return impl->m_zone;
}

H5CgnsParticleGroupSolution::GroupReader H5CgnsParticleGroupSolution::groupReader(const std::string& name)
{
	return GroupReader(name, this);
}
