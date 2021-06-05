#include "../h5cgnsbase.h"
#include "../h5cgnszone.h"

#include "../internal/iric_logger.h"

#include "h5cgnsgridcoordinates_impl.h"

using namespace iRICLib;

H5CgnsGridCoordinates::Impl::Impl() :
	m_groupId {0},
	m_zone {nullptr}
{}

H5CgnsGridCoordinates::Impl::~Impl()
{
	_IRIC_LOGGER_TRACE_CALL_START("H5Gclose");
	herr_t status = H5Gclose(m_groupId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Gclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsGridCoordinates::Impl::~Impl", "H5Gclose", status);
	}
}

std::vector<hsize_t> H5CgnsGridCoordinates::Impl::dimensions() const
{
	auto size = m_zone->size();
	std::vector<hsize_t> ret;

	if (m_zone->type() == H5CgnsZone::Type::Unstructured) {
		ret.push_back(size.at(0));
		return ret;
	} else {
		auto base = m_zone->base();
		auto dim = base->dimension();
		for (int i = 0; i < dim; ++i) {
			ret.push_back(size.at(dim - 1 - i)); // reverse order
		}
		return ret;
	}
}
