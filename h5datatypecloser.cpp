#include "h5datatypecloser.h"

#include "internal/iric_logger.h"

using namespace iRICLib;

H5DataTypeCloser::H5DataTypeCloser(hid_t dataTypeId) :
	m_dataTypeId {dataTypeId}
{}

H5DataTypeCloser::~H5DataTypeCloser()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Tclose");
	herr_t status = H5Tclose(m_dataTypeId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Tclose");

	if (status < 0) {
		_iric_logger_error("H5DataTypeCloser::~H5DataTypeCloser", "H5Tclose", status);
	}
}
