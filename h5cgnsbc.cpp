#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsbc.h"
#include "h5cgnsfile.h"
#include "h5cgnszonebc.h"
#include "h5cgnszone.h"
#include "h5groupcloser.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsbc_impl.h"

using namespace iRICLib;

#define LABEL "BC_t"
#define POINTLIST "PointList"

std::string H5CgnsBc::label()
{
	return LABEL;
}

H5CgnsBc::H5CgnsBc(const std::string& name, hid_t groupId, H5CgnsZoneBc* zoneBc) :
	H5CgnsConditionGroup(name, groupId, zoneBc->zone()->base()->file()->mode()),
	impl {new Impl {}}
{
	impl->m_groupId = groupId;
	impl->m_zoneBc = zoneBc;
}

H5CgnsBc::~H5CgnsBc()
{
	// impl->m_groupId is closed by ~H5CgnsConditionGroup(), so do not close here.
	delete impl;
}

int H5CgnsBc::readIndicesSize(int* size) const
{
	int indexDim = 1;
	auto zone = impl->m_zoneBc->zone();
	if (zone->type() == H5CgnsZone::Type::Structured) {
		indexDim = zone->base()->dimension();
	}
	int tmpSize;
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBc::readIndicesValueCount");
	int ier = readIndicesValueCount(&tmpSize);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBc::readIndicesValueCount", ier);
	RETURN_IF_ERR;

	*size = tmpSize / indexDim;

	return IRIC_NO_ERROR;
}

int H5CgnsBc::readIndicesValueCount(int* size) const
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(impl->m_groupId, POINTLIST, H5Util::indexArrayLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValueLength");
	ier = H5Util::readGroupValueLength(gId, size);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValueLength", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsBc::readIndices(std::vector<int>* indices) const
{
	hid_t gId;
	_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
	int ier = H5Util::openGroup(impl->m_groupId, POINTLIST, H5Util::indexArrayLabel(), &gId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::openGroup", ier);
	RETURN_IF_ERR;

	H5GroupCloser closer(gId);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValue");
	ier = H5Util::readGroupValue(gId, indices);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsBc::writeIndices(const std::vector<int>& indices) const
{
	int indexDim = 1;
	auto zone = impl->m_zoneBc->zone();
	if (zone->type() == H5CgnsZone::Type::Structured) {
		indexDim = zone->base()->dimension();
	}
	auto count = indices.size() / indexDim;
	std::vector<hsize_t> dims;
	dims.push_back(count);
	dims.push_back(indexDim);

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
	int ier = H5Util::createGroupWithValue(impl->m_groupId, POINTLIST, H5Util::indexArrayLabel(), indices, dims);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
