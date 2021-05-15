#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsbaseiterativedata.h"
#include "h5cgnsfile.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsbaseiterativedata_impl.h"

#include <sstream>

using namespace iRICLib;

#define LABEL "BaseIterativeData_t"
#define GROUP_NAME "BaseIterativeData"
#define TIMEVALUES "TimeValues"
#define ITERATIONVALUES "IterationValues"

namespace {

template <typename V>
std::vector<V>* getVectorWithName(const std::string& name, std::map<std::string, std::vector<V> >* values)
{
	auto it = values->find(name);
	if (it != values->end()) {
		return &(it->second);
	} else {
		std::vector<V> empty;
		auto pair = values->insert({name, empty});
		return &(pair.first->second);
	}
}

template <typename V>
int writeDataT(const std::string& name, V value, std::map<std::string, std::vector<V> >* values, int* count)
{
	std::vector<V>* data = getVectorWithName(name, values);
	data->push_back(value);

	if (count != nullptr) {
		*count = static_cast<int> (data->size());
	}

	return IRIC_NO_ERROR;
}

template <typename V>
int writeDataT(const std::string& name, const std::vector<V>& value, std::map<std::string, std::vector<V> >* values)
{
	std::vector<V>* data = getVectorWithName(name, values);
	*data = value;
	return IRIC_NO_ERROR;
}

template <typename V>
int flushT(hid_t groupId, const std::map<std::string, std::vector<V> > values)
{
	for (const auto& pair : values) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::updateOrCreateDataArray");
		int ier = H5Util::updateOrCreateDataArray(groupId, pair.first, pair.second);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::updateOrCreateDataArray", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

template <typename V>
int readValuesT(const std::string& name, std::vector<V>* values, const std::map<std::string, std::vector<V> >& m)
{
	auto it = m.find(name);
	if (it == m.end()) {
		std::ostringstream ss;
		ss << "In readValuesT(), data with name " << name << " not found";
		_iric_logger_error(ss.str());

		return IRIC_DATA_NOT_FOUND;
	}
	*values = it->second;

	return IRIC_NO_ERROR;
}

template <typename V>
int readValueT(int solutionId, const std::string& name, V* value, const std::map<std::string, std::vector<V> >& m)
{
	auto it = m.find(name);
	if (it == m.end()) {
		std::ostringstream ss;
		ss << "In readValuesT(), data with name " << name << " not found";
		_iric_logger_error(ss.str());

		return IRIC_DATA_NOT_FOUND;
	}
	const auto& vals = it->second;

	if (solutionId < 1 || solutionId > static_cast<int> (vals.size())) {
		std::ostringstream ss;
		ss << "In readValuesT(), data has " << vals.size() << " values, but solutionId " << solutionId << " was specified";
		_iric_logger_error(ss.str());

		return IRIC_DATA_NOT_FOUND;
	}
	*value = vals.at(solutionId - 1);

	return IRIC_NO_ERROR;
}

} // namespace

std::string H5CgnsBaseIterativeData::label()
{
	return LABEL;
}

std::string H5CgnsBaseIterativeData::groupName()
{
	return GROUP_NAME;
}

H5CgnsBaseIterativeData::H5CgnsBaseIterativeData(hid_t groupId, H5CgnsBase* base) :
	impl {new Impl {this}}
{
	impl->m_groupId = groupId;
	impl->m_base = base;

	impl->readAllValues();
}

H5CgnsBaseIterativeData::~H5CgnsBaseIterativeData()
{
	if (impl->m_base->file()->mode() != H5CgnsFile::Mode::OpenReadOnly) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBaseIterativeData::flush");
		int ier = flush();
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBaseIterativeData::flush", ier);

		_IRIC_LOGGER_TRACE_CALL_START("H5Util::updateGroupValue");
		ier = H5Util::updateGroupValue(impl->m_groupId, impl->valueCount());
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::updateGroupValue", ier);
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(impl->m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsBaseIterativeData::~H5CgnsBaseIterativeData", "H5Gclose", status);
	}

	delete impl;
}

int H5CgnsBaseIterativeData::writeData(const std::string& name, double value, int* count)
{
	return writeDataT(name, value, &(impl->m_realValues), count);
}

int H5CgnsBaseIterativeData::writeData(const std::string& name, int value, int* count)
{
	return writeDataT(name, value, &(impl->m_intValues), count);
}

int H5CgnsBaseIterativeData::writeData(const std::string& name, const std::string& value, int* count)
{
	return writeDataT(name, value, &(impl->m_stringValues), count);
}

int H5CgnsBaseIterativeData::writeData(const std::string& name, const std::vector<double>& values)
{
	return writeDataT(name, values, &(impl->m_realValues));
}

int H5CgnsBaseIterativeData::writeData(const std::string& name, std::vector<int>& values)
{
	return writeDataT(name, values, &(impl->m_intValues));
}

int H5CgnsBaseIterativeData::writeData(const std::string& name, std::vector<std::string>& values)
{
	return writeDataT(name, values, &(impl->m_stringValues));
}

int H5CgnsBaseIterativeData::writeTime(double time, int* count)
{
	return writeData(TIMEVALUES, time, count);
}

int H5CgnsBaseIterativeData::writeIteration(int iteration, int* count)
{
	return writeData(ITERATIONVALUES, iteration, count);
}

int H5CgnsBaseIterativeData::clearData()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::deleteAllChildren");
	int ier = H5Util::deleteAllChildren(impl->m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::deleteAllChildren", ier);
	RETURN_IF_ERR;

	impl->m_intValues.clear();
	impl->m_realValues.clear();

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::flush()
{
	int ier;

	_IRIC_LOGGER_TRACE_CALL_START("flushT");
	ier = flushT(impl->m_groupId, impl->m_realValues);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("flushT", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("flushT");
	ier = flushT(impl->m_groupId, impl->m_intValues);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("flushT", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("flushT");
	ier = flushT(impl->m_groupId, impl->m_stringValues);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("flushT", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::getResultNames(std::vector<std::string>* names)
{
	std::vector<std::string> tmpNames;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, &tmpNames);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : tmpNames) {
		if (name == TIMEVALUES) {continue;}
		if (name == ITERATIONVALUES) {continue;}

		names->push_back(name);
	}

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::getResultNames(std::set<std::string>* names)
{
	std::set<std::string> tmpNames;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : tmpNames) {
		if (name == TIMEVALUES) {continue;}
		if (name == ITERATIONVALUES) {continue;}

		names->insert(name);
	}

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::readValueType(const std::string& name, H5Util::DataArrayValueType* type)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValueType");
	int ier = H5Util::readDataArrayValueType(impl->m_groupId, name, type);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValueType", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::readTime(std::vector<double>* values)
{
	int ier = readValues(TIMEVALUES, values);

	if (ier == IRIC_DATA_NOT_FOUND) {
		values->clear();
		return IRIC_NO_ERROR;
	}

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::readTime(int solutionId, double* value)
{
	return readValue(solutionId, TIMEVALUES, value);
}

int H5CgnsBaseIterativeData::readIteration(std::vector<int>* values)
{
	int ier = readValues(ITERATIONVALUES, values);
	if (ier == IRIC_DATA_NOT_FOUND) {
		values->clear();
		return IRIC_NO_ERROR;
	}

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::readIteration(int solutionId, int* value)
{
	return readValue(solutionId, ITERATIONVALUES, value);
}

int H5CgnsBaseIterativeData::readValues(const std::string& name, std::vector<double>* values)
{
	return readValuesT(name, values, impl->m_realValues);
}

int H5CgnsBaseIterativeData::readValue(int solutionId, const std::string& name, double* value)
{
	return readValueT(solutionId, name, value, impl->m_realValues);
}

int H5CgnsBaseIterativeData::readValues(const std::string& name, std::vector<int>* values)
{
	return readValuesT(name, values, impl->m_intValues);
}

int H5CgnsBaseIterativeData::readValue(int solutionId, const std::string& name, int* value)
{
	return readValueT(solutionId, name, value, impl->m_intValues);
}

int H5CgnsBaseIterativeData::readValues(const std::string& name, std::vector<std::string>* values)
{
	return readValuesT(name, values, impl->m_stringValues);
}

int H5CgnsBaseIterativeData::readValue(int solutionId, const std::string& name, std::string* value)
{
	return readValueT(solutionId, name, value, impl->m_stringValues);
}
