#include "error_macros.h"
#include "h5cgnsparticlesolution.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsparticlesolution_impl.h"

using namespace iRICLib;

#define COORDSX "CoordinateX"
#define COORDSY "CoordinateY"
#define COORDSZ "CoordinateZ"

H5CgnsParticleSolution::H5CgnsParticleSolution(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	impl {new Impl {}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_zone = zone;
}

H5CgnsParticleSolution::~H5CgnsParticleSolution()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(impl->m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsParticleSolution::~H5CgnsParticleSolution", "H5Gclose", status);
	}

	delete impl;
}

std::string H5CgnsParticleSolution::name() const
{
	return impl->m_name;
}

int H5CgnsParticleSolution::count(int* count)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayLength");
	int ier = H5Util::readDataArrayLength(impl->m_groupId, COORDSX, count);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readValueNames(std::vector<std::string>* names) const
{
	std::vector<std::string> tmpNames;

	std::string coordsHeader = "Coordinate";

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(impl->m_groupId, &tmpNames);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	RETURN_IF_ERR;

	for (const auto& name : tmpNames) {
		if (name.substr(0, coordsHeader.size()) == coordsHeader) {continue;}

		names->push_back(name);
	}

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readValueNames(std::set<std::string>* names) const
{
	std::vector<std::string> namesVec;
	int ier = readValueNames(&namesVec);
	RETURN_IF_ERR;

	for (const auto& n : namesVec) {
		names->insert(n);
	}
	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readCoordinatesX(std::vector<double>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsParticleSolution::readValue");
	int ier = readValue(COORDSX, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsParticleSolution::readValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readCoordinatesY(std::vector<double>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsParticleSolution::readValue");
	int ier = readValue(COORDSY, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsParticleSolution::readValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readCoordinatesZ(std::vector<double>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsParticleSolution::readValue");
	int ier = readValue(COORDSZ, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsParticleSolution::readValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readValueType(const std::string& name, H5Util::DataArrayValueType *type) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValueType");
	int ier = H5Util::readDataArrayValueType(impl->m_groupId, name, type);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValueType", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readValue(const std::string& name, std::vector<double>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readValue(const std::string& name, std::vector<int>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::readValueAsDouble(const std::string& name, std::vector<double>* values) const
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

int H5CgnsParticleSolution::writeCoordinatesX(const std::vector<double>& coords) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsParticleSolution::writeValue");
	int ier = writeValue(COORDSX, coords);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsParticleSolution::writeValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::writeCoordinatesY(const std::vector<double>& coords) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsParticleSolution::writeValue");
	int ier = writeValue(COORDSY, coords);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsParticleSolution::writeValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::writeCoordinatesZ(const std::vector<double>& coords) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsParticleSolution::writeValue");
	int ier = writeValue(COORDSZ, coords);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsParticleSolution::writeValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::writeValue(const std::string& name, const std::vector<double>& values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	int ier = H5Util::createDataArray(impl->m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsParticleSolution::writeValue(const std::string& name, const std::vector<int>& values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	int ier = H5Util::createDataArray(impl->m_groupId, name, values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

H5CgnsZone* H5CgnsParticleSolution::zone() const
{
	return impl->m_zone;
}
