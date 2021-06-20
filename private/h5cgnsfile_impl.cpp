#include "../h5cgnsbase.h"
#include "../h5cgnsfilesolutionreader.h"
#include "../h5cgnsfilesolutionwriter.h"
#include "../h5util.h"
#include "../iriclib_errorcodes.h"

#include "../internal/iric_logger.h"

#include "h5cgnsfile_impl.h"

#include <hdf5.h>

#include <sstream>
#include <string>
#include <vector>

using namespace iRICLib;

H5CgnsFile::Impl::Impl(H5CgnsFile* file) :
	m_ccBase {nullptr},
	m_solutionReader {nullptr},
	m_solutionWriter {nullptr},
	m_writerMode {H5CgnsFileSolutionWriter::Mode::Standard},
	m_file {file}
{}

H5CgnsFile::Impl::~Impl()
{
	close();
}

int H5CgnsFile::Impl::open()
{
	loadBases();
	loadZones();

	return IRIC_NO_ERROR;
}

int H5CgnsFile::Impl::close()
{
	for (auto base : m_bases) {
		delete base;
	}

	delete m_solutionReader;
	delete m_solutionWriter;

	_IRIC_LOGGER_TRACE_CALL_START("H5Fclose");
	herr_t status = H5Fclose(m_fileId);
	_IRIC_LOGGER_TRACE_CALL_END("H5Fclose");

	if (status < 0) {
		_iric_logger_error("H5CgnsFile::Impl::close", "H5Fclose", status);
	}
	return IRIC_NO_ERROR;
}

void H5CgnsFile::Impl::loadBases()
{
	std::vector<std::string> groupNames;

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::getGroupNames");
	int ier = H5Util::getGroupNames(m_fileId, &groupNames);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::getGroupNames", ier);
	if (ier != IRIC_NO_ERROR) {return;}

	for (const auto& name : groupNames) {
		hid_t groupId;
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::openGroup");
		int ier = H5Util::openGroup(m_fileId, name, H5CgnsBase::label(), &groupId, true);
		_IRIC_LOGGER_TRACE_CALL_END("H5Util::openGroup");
		if (ier != IRIC_NO_ERROR) {continue;}

		std::vector<int> dims;
		_IRIC_LOGGER_TRACE_CALL_START("H5Util::readGroupValue");
		ier = H5Util::readGroupValue(groupId, &dims);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::readGroupValue", ier);
		if (ier != IRIC_NO_ERROR) {continue;}

		int firstDim = dims.at(0);

		auto base = new H5CgnsBase(firstDim, name, groupId, m_file);
		m_bases.push_back(base);
		m_baseMap.insert({firstDim, base});

		if (firstDim == 2) {
			m_ccBase = base;
		}
	}
}

H5CgnsBase* H5CgnsFile::Impl::createBase(int dimension)
{
	auto name = baseName(dimension);

	hid_t baseGroupId;
	std::vector<int> vals;
	vals.push_back(dimension); // cellDim
	vals.push_back(dimension); // physDim

	_IRIC_LOGGER_TRACE_CALL_START("H5Util::createGroupWithValue");
	int ier = H5Util::createGroupWithValue(m_fileId, name, H5CgnsBase::label(), vals, &baseGroupId);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5Util::createGroupWithValue", ier);
	if (ier != IRIC_NO_ERROR) {return nullptr;}

	return new H5CgnsBase(dimension, name, baseGroupId, m_file);
}

std::string H5CgnsFile::Impl::baseName(int dimension)
{
	if (dimension == 2) {return "iRIC";}

	std::ostringstream ss;
	ss << "iRIC" << dimension << "D";
	return ss.str();
}

void H5CgnsFile::Impl::loadZones()
{
	for (size_t i = 0; i < m_bases.size(); ++i) {
		auto base = m_bases.at(i);
		for (int j = 0; j < base->zoneNum(); ++j) {
			auto zone = base->zoneById(j + 1);
			m_zones.push_back(zone);
		}
	}
}

int H5CgnsFile::Impl::getGridId(H5CgnsZone* zone, int* gridId)
{
	for (size_t i = 0; i < m_zones.size(); ++i) {
		auto z = m_zones.at(i);
		if (z == zone) {
			*gridId = static_cast<int> (i + 1);
			return IRIC_NO_ERROR;
		}
	}
	_iric_logger_error("In H5CgnsFile::Impl::getGridId(), specified zone not found in m_zones");

	return IRIC_GRID_NOT_FOUND;
}
