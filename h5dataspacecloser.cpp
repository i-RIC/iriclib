#include "h5dataspacecloser.h"

#include "internal/iric_logger.h"

using namespace iRICLib;

H5DataSpaceCloser::H5DataSpaceCloser(hid_t dataSpaceId) :
	m_dataSpaceId {dataSpaceId}
{}

H5DataSpaceCloser::~H5DataSpaceCloser()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Sclose");
	herr_t status = H5Sclose(m_dataSpaceId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Sclose");

	if (status < 0) {
		_iric_logger_error("H5DataSpaceCloser::~H5DataSpaceCloser", "H5Sclose", status);
	}
}
