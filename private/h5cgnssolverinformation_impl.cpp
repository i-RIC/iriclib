#include "h5cgnssolverinformation_impl.h"

#include "../internal/iric_logger.h"

using namespace iRICLib;

H5CgnsSolverInformation::Impl::Impl() :
	m_groupId {0}
{}

H5CgnsSolverInformation::Impl::~Impl()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsSolverInformation::Impl::~Impl", "H5Gclose", status);
	}
}
