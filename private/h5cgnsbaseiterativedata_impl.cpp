#include "../error_macros.h"
#include "../iriclib_errorcodes.h"

#include "../internal/iric_logger.h"

#include "h5cgnsbaseiterativedata_impl.h"

#include <map>
#include <vector>

using namespace iRICLib;

template <typename V>
int getValueCountT(const std::map<std::string, std::vector<V> >& values)
{
	for (const auto& pair : values) {
		auto c = pair.second.size();
		if (c > 0) {return static_cast<int> (c);}
	}
	return 0;
}

H5CgnsBaseIterativeData::Impl::Impl(H5CgnsBaseIterativeData* data) :
	m_data {data}
{}

int H5CgnsBaseIterativeData::Impl::valueCount()
{
	int c = 0;

	c = getValueCountT(m_realValues);
	if (c != 0) {return c;}
	c = getValueCountT(m_intValues);
	if (c != 0) {return c;}

	return 0;
}

int H5CgnsBaseIterativeData::Impl::readAllValues()
{
	int ier;
	std::vector<std::string> names;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBaseIterativeData::getResultNames");
	ier = m_data->getResultNames(&names);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBaseIterativeData::getResultNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : names) {
		H5Util::DataArrayValueType type;
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBaseIterativeData::readValueType");
		ier = m_data->readValueType(name, &type);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBaseIterativeData::readValueType", ier);
		RETURN_IF_ERR;
		if (type == H5Util::DataArrayValueType::Int) {
			std::vector<int> vals;
			_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBaseIterativeData::Impl::readValues");
			ier = readValues(name, &vals);
			_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBaseIterativeData::Impl::readValues", ier);
			RETURN_IF_ERR;

			m_intValues.insert({name, vals});
		} else if (type == H5Util::DataArrayValueType::RealDouble) {
			std::vector<double> vals;
			_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBaseIterativeData::Impl::readValues");
			ier = readValues(name, &vals);
			_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBaseIterativeData::Impl::readValues", ier);
			RETURN_IF_ERR;

			m_realValues.insert({name, vals});
		} else if (type == H5Util::DataArrayValueType::Char) {
			std::vector<std::string> vals;
			_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBaseIterativeData::Impl::readValues");
			ier = readValues(name, &vals);
			_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBaseIterativeData::Impl::readValues", ier);
			RETURN_IF_ERR;

			m_stringValues.insert({name, vals});
		}
	}

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::Impl::readValues(const std::string& name, std::vector<double>* values)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::Impl::readValues(const std::string& name, std::vector<int>* values)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsBaseIterativeData::Impl::readValues(const std::string& name, std::vector<std::string>* values)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
