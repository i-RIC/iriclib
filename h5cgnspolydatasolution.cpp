#include "error_macros.h"
#include "h5cgnspolydatasolution.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnspolydatasolution_impl.h"
#include "public/h5cgnspolydatasolution_groupreader.h"

#include <sstream>

using namespace iRICLib;

const int H5CgnsPolyDataSolution::POLYGON;
const int H5CgnsPolyDataSolution::POLYLINE;

H5CgnsPolyDataSolution::H5CgnsPolyDataSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	impl {new Impl {}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_zone = zone;
}

H5CgnsPolyDataSolution::~H5CgnsPolyDataSolution()
{
	H5Gclose(impl->m_groupId);
	delete impl;
}

std::string H5CgnsPolyDataSolution::name() const
{
	return impl->m_name;
}

void H5CgnsPolyDataSolution::writeBegin(const std::string& groupName)
{
	impl->clear();
	impl->m_groupName = groupName;
}

int H5CgnsPolyDataSolution::writeEnd()
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
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	// types
	ss.str("");
	ss << impl->m_groupName << "_type";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_types);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	// sizes
	ss.str("");
	ss << impl->m_groupName << "_size";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	ier = H5Util::createDataArray(impl->m_groupId, ss.str(), impl->m_sizes);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

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

	return true;
}

void H5CgnsPolyDataSolution::writePolygon(std::vector<double>& x, std::vector<double>& y)
{
	impl->m_types.push_back(POLYGON);
	impl->m_sizes.push_back(static_cast<int> (x.size()));
	for (const auto& v : x) {
		impl->m_coordinateX.push_back(v);
	}
	for (const auto& v : y) {
		impl->m_coordinateY.push_back(v);
	}
}

void H5CgnsPolyDataSolution::writePolyline(std::vector<double>& x, std::vector<double>& y)
{
	impl->m_types.push_back(POLYLINE);
	impl->m_sizes.push_back(static_cast<int> (x.size()));
	for (const auto& v : x) {
		impl->m_coordinateX.push_back(v);
	}
	for (const auto& v : y) {
		impl->m_coordinateY.push_back(v);
	}
}

void H5CgnsPolyDataSolution::writeValue(const std::string& name, int value)
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

void H5CgnsPolyDataSolution::writeValue(const std::string& name, double value)
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

int H5CgnsPolyDataSolution::readGroupNames(std::vector<std::string>* names) const
{
	std::string typeSuffix = "_type";
	std::vector<std::string> tmpNames;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, &tmpNames);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : tmpNames) {
		auto offset = name.length() - typeSuffix.length();
		if (offset < 0) {continue;}

		auto suffix = name.substr(offset, typeSuffix.length());
		if (suffix != typeSuffix) {continue;}

		names->push_back(name.substr(0, offset));
	}

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::dataCount(const std::string& groupName, int* count)
{
	std::ostringstream ss;
	ss << groupName << "_type";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayLength");
	int ier = H5Util::readDataArrayLength(impl->m_groupId, ss.str(), count);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::coordinatesCount(const std::string& groupName, int* count)
{
	std::ostringstream ss;
	ss << groupName << "_coordinateX";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayLength");
	int ier = H5Util::readDataArrayLength(impl->m_groupId, ss.str(), count);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readValueNames(const std::string& groupName, std::vector<std::string>* names) const
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

int H5CgnsPolyDataSolution::readValueNames(const std::string& groupName, std::set<std::string>* names) const
{
	std::vector<std::string> namesVec;
	int ier = readValueNames(groupName, &namesVec);
	RETURN_IF_ERR;

	for (const auto& name : namesVec) {
		names->insert(name);
	}

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readCoordinatesX(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_coordinateX";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readCoordinatesY(const std::string& groupName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_coordinateY";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readTypes(const std::string& groupName, std::vector<int>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_type";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readSizes(const std::string& groupName, std::vector<int>* values) const
{
	std::ostringstream ss;
	ss << groupName << "_size";
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readValueType(const std::string& groupName, const std::string& valueName, H5Util::DataArrayValueType *type) const
{
	std::ostringstream ss;
	ss << groupName << "__" << valueName;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValueType");
	int ier = H5Util::readDataArrayValueType(impl->m_groupId, ss.str(), type);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValueType", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readValue(const std::string& groupName, const std::string& valueName, std::vector<int>* values) const
{
	std::ostringstream ss;
	ss << groupName << "__" << valueName;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readValue(const std::string& groupName, const std::string& valueName, std::vector<double>* values) const
{
	std::ostringstream ss;
	ss << groupName << "__" << valueName;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, ss.str(), values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsPolyDataSolution::readValueAsDouble(const std::string& groupName, const std::string& valueName, std::vector<double>* values) const
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

H5CgnsZone* H5CgnsPolyDataSolution::zone() const
{
	return impl->m_zone;
}

H5CgnsPolyDataSolution::GroupReader H5CgnsPolyDataSolution::groupReader(const std::string& name)
{
	return GroupReader(name, this);
}
