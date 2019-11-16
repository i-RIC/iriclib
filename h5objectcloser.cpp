#include "h5objectcloser.h"

#include "internal/iric_logger.h"

using namespace iRICLib;

H5ObjectCloser::H5ObjectCloser(hid_t objectId) :
	m_objectId {objectId}
{}

H5ObjectCloser::~H5ObjectCloser()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Oclose");
	herr_t status = H5Oclose(m_objectId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Oclose");

	if (status < 0) {
		_iric_logger_error("H5ObjectCloser::~H5ObjectCloser", "H5Oclose", status);
	}
}
