#include "h5datasetcloser.h"

#include "internal/iric_logger.h"

using namespace iRICLib;

H5DatasetCloser::H5DatasetCloser(hid_t datasetId) :
	m_datasetId {datasetId}
{}

H5DatasetCloser::~H5DatasetCloser()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Dclose");
	herr_t status = H5Dclose(m_datasetId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Dclose");

	if (status < 0) {
		_iric_logger_error("H5DatasetCloser::~H5DatasetCloser", "H5Dclose", status);
	}
}
