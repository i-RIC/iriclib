#include "h5propertylistcloser.h"

#include "internal/iric_logger.h"

using namespace iRICLib;

H5PropertyListCloser::H5PropertyListCloser(hid_t propertyListId) :
	m_propertyListId {propertyListId}
{}

H5PropertyListCloser::~H5PropertyListCloser()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Pclose");
	herr_t status = H5Pclose(m_propertyListId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Pclose");

	if (status < 0) {
		_iric_logger_error("H5PropertyListCloser::~H5PropertyListCloser", "H5Pclose", status);
	}
}
