#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsgridcoordinates.h"
#include "h5cgnszone.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsgridcoordinates_impl.h"

using namespace iRICLib;

#define LABEL "GridCoordinates_t"

std::string H5CgnsGridCoordinates::label()
{
	return LABEL;
}

H5CgnsGridCoordinates::H5CgnsGridCoordinates(const std::string& name, hid_t groupId, H5CgnsZone* zone) :
	impl {new Impl {}}
{
	impl->m_name = name;
	impl->m_groupId = groupId;
	impl->m_zone = zone;
}

H5CgnsGridCoordinates::~H5CgnsGridCoordinates()
{
	delete impl;
}

std::string H5CgnsGridCoordinates::name() const
{
	return impl->m_name;
}

int H5CgnsGridCoordinates::readCoordinatesX(std::vector<double>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, "CoordinateX", values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsGridCoordinates::readCoordinatesY(std::vector<double>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, "CoordinateY", values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsGridCoordinates::readCoordinatesZ(std::vector<double>* values) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readDataArrayValue");
	int ier = H5Util::readDataArrayValue(impl->m_groupId, "CoordinateZ", values);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readDataArrayValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsGridCoordinates::writeCoordinatesX(const std::vector<double>& coords) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	int ier = H5Util::createDataArray(impl->m_groupId, "CoordinateX", coords, impl->dimensions());
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsGridCoordinates::writeCoordinatesY(const std::vector<double>& coords) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	int ier = H5Util::createDataArray(impl->m_groupId, "CoordinateY", coords, impl->dimensions());
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsGridCoordinates::writeCoordinatesZ(const std::vector<double>& coords) const
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createDataArray");
	int ier = H5Util::createDataArray(impl->m_groupId, "CoordinateZ", coords, impl->dimensions());
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createDataArray", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsGridCoordinates::copyTo(H5CgnsGridCoordinates* coords)
{
	int ier;
	std::vector<double> buffer;

	auto dim = impl->m_zone->base()->dimension();

	// copy X
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridCoordinates::readCoordinatesX");
	ier = readCoordinatesX(&buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsGridCoordinates::readCoordinatesX", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridCoordinates::writeCoordinatesX");
	ier = coords->writeCoordinatesX(buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsGridCoordinates::writeCoordinatesX", ier);
	RETURN_IF_ERR;

	if (dim == 1) {return IRIC_NO_ERROR;}

	// copy Y
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridCoordinates::readCoordinatesY");
	ier = readCoordinatesY(&buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsGridCoordinates::readCoordinatesY", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridCoordinates::writeCoordinatesY");
	ier = coords->writeCoordinatesY(buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsGridCoordinates::writeCoordinatesY", ier);
	RETURN_IF_ERR;

	if (dim == 2) {return IRIC_NO_ERROR;}

	// copy Z
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridCoordinates::readCoordinatesZ");
	ier = readCoordinatesZ(&buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsGridCoordinates::readCoordinatesZ", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsGridCoordinates::writeCoordinatesZ");
	ier = coords->writeCoordinatesZ(buffer);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsGridCoordinates::writeCoordinatesZ", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
