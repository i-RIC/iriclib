#include "h5attributecloser.h"

#include "internal/iric_logger.h"

using namespace iRICLib;

H5AttributeCloser::H5AttributeCloser(hid_t attributeId) :
	m_attributeId {attributeId}
{}

H5AttributeCloser::~H5AttributeCloser()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Aclose");
	herr_t status = H5Aclose(m_attributeId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Aclose");

	if (status < 0) {
		_iric_logger_error("H5AttributeCloser::~H5AttributeCloser", "H5Aclose", status);
	}
}
