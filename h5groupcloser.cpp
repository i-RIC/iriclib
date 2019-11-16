#include "h5groupcloser.h"

#include "internal/iric_logger.h"

using namespace iRICLib;

H5GroupCloser::H5GroupCloser(hid_t groupId) :
	m_groupId {groupId}
{}

H5GroupCloser::~H5GroupCloser()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5GroupCloser::~H5GroupCloser", "H5Gclose", status);
	}
}
