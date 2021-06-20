#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsbaseiterativedata.h"
#include "h5cgnsfile.h"
#include "h5cgnsfilesolutionreader.h"
#include "h5cgnsfilesolutionwriter.h"
#include "h5propertylistcloser.h"
#include "h5util.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include "private/h5cgnsbase_impl.h"
#include "private/h5cgnsfile_impl.h"

#include <Poco/Path.h>

#include <sstream>
#include <stdexcept>

using namespace iRICLib;

namespace {

void _initCgnsFile(hid_t fileId)
{
	H5Util::writeData(fileId, " format", "IEEE_LITTLE_32");
	H5Util::writeData(fileId, " hdf5version", "HDF5 Version 1.8.22");
	float cgnsVersion = 3.21f;
	H5Util::createGroupWithValue(fileId, "CGNSLibraryVersion", "CGNSLibraryVersion_t", cgnsVersion);
}

} // namespace

H5CgnsFile::H5CgnsFile(const std::string &fileName, Mode mode) :
	impl {new Impl {this}}
{
	_iric_logger_init();

	impl->m_mode = mode;
	impl->m_fileName = fileName;

	if (mode == Mode::Create) {
		_IRIC_LOGGER_TRACE_CALL_START("H5Pcreate");
		hid_t fileCreationProperty = H5Pcreate(H5P_FILE_CREATE);
		_IRIC_LOGGER_TRACE_CALL_END("H5Pcreate");

		if (fileCreationProperty < 0) {
			_iric_logger_error("H5CgnsFile::H5CgnsFile", "H5Pcreate", fileCreationProperty);
		}

		H5PropertyListCloser groupCreationPropertyCloser(fileCreationProperty);

		_IRIC_LOGGER_TRACE_CALL_START("H5Pset_link_creation_order");
		H5Pset_link_creation_order(fileCreationProperty, H5P_CRT_ORDER_TRACKED | H5P_CRT_ORDER_INDEXED);
		_IRIC_LOGGER_TRACE_CALL_END("H5Pset_link_creation_order");

		impl->m_fileId = H5Fcreate(fileName.c_str(), H5F_ACC_TRUNC, fileCreationProperty, H5P_DEFAULT);
		if (impl->m_fileId >= 0) {
			_initCgnsFile(impl->m_fileId);
			auto iricBase = impl->createBase(2);
			impl->m_bases.push_back(iricBase);
			impl->m_baseMap.insert({2, iricBase});
			impl->m_ccBase = iricBase;
		}
	} else {
		unsigned int flags = H5F_ACC_RDWR;
		if (mode == Mode::OpenReadOnly) {
			flags = H5F_ACC_RDONLY;
		}
		impl->m_fileId = H5Fopen(fileName.c_str(), flags, H5P_DEFAULT);

		if (impl->m_fileId >= 0) {
			impl->loadBases();

			impl->loadZones();
		}
	}

	if (impl->m_fileId < 0) {
		delete impl;
		std::ostringstream ss;
		ss << "Opening " << fileName << " failed.";
		throw std::runtime_error(ss.str());
	}
}

H5CgnsFile::~H5CgnsFile()
{
	delete impl;
}

H5CgnsFile::Mode H5CgnsFile::mode() const
{
	return impl->m_mode;
}

std::string H5CgnsFile::fileName() const
{
	return impl->m_fileName;
}

std::string H5CgnsFile::tmpFileName() const
{
	Poco::Path path(impl->m_fileName);
	return path.parent().append(Poco::Path("Case1_tmp.cgn")).toString();
}

int H5CgnsFile::baseNum() const
{
	return static_cast<int> (impl->m_bases.size());
}

H5CgnsBase* H5CgnsFile::base()
{
	return base(2);
}

H5CgnsBase* H5CgnsFile::base(int dim)
{
	auto it = impl->m_baseMap.find(dim);
	if (it != impl->m_baseMap.end()) {return it->second;}

	if (impl->m_mode == Mode::OpenReadOnly) {return nullptr;}

	auto newBase = impl->createBase(dim);
	impl->m_bases.push_back(newBase);
	impl->m_baseMap.insert({dim, newBase});

	return newBase;
}

H5CgnsBase* H5CgnsFile::baseById(int bid)
{
	if (bid < 1 || bid > static_cast<int> (impl->m_bases.size())) {return nullptr;}

	return impl->m_bases.at(bid - 1);
}

H5CgnsBase* H5CgnsFile::ccBase() const
{
	return impl->m_ccBase;
}

bool H5CgnsFile::baseExists(int dim) const
{
	auto it = impl->m_baseMap.find(dim);
	return it != impl->m_baseMap.end();
}

int H5CgnsFile::zoneNum() const
{
	return static_cast<int> (impl->m_zones.size());
}

H5CgnsZone* H5CgnsFile::zoneById(int zid)
{
	if (zid <= 0 || zid > static_cast<int> (impl->m_zones.size())) {return nullptr;}

	return impl->m_zones.at(zid - 1);
}

int H5CgnsFile::writeTime(double time)
{
	auto base = ccBase();
	int count;
	int ier = base->biterData()->writeTime(time, &count);
	RETURN_IF_ERR;

	ier = setSolutionId(count);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFile::writeIteration(int iteration)
{
	auto base = ccBase();
	int count;
	int ier = base->biterData()->writeIteration(iteration, &count);
	RETURN_IF_ERR;

	ier = setSolutionId(count);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFile::setSolutionId(int solutionId)
{
	for (auto base : impl->m_bases) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::setSolutionId");
		int ier = base->setSolutionId(solutionId);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBase::setSolutionId", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

int H5CgnsFile::copyGridsTo(H5CgnsFile* target)
{
	for (auto base : impl->m_bases) {
		auto base2 = target->base(base->dimension());
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::copyGridsTo");
		int ier = base->copyGridsTo(base2);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBase::copyGridsTo", ier);
		RETURN_IF_ERR;
	}

	return IRIC_NO_ERROR;
}

int H5CgnsFile::flush()
{
	for (auto base : impl->m_bases) {
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsBase::flush");
		int ier = base->flush();
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsBase::flush", ier);
		RETURN_IF_ERR;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5Fflush");
	herr_t status = H5Fflush(impl->m_fileId, H5F_SCOPE_LOCAL);
	_IRIC_LOGGER_TRACE_CALL_END("H5Fflush");
	if (status < 0) {
		_iric_logger_error("H5CgnsFile::flush", "H5Fflush", status);
	}

	return IRIC_NO_ERROR;
}

int H5CgnsFile::getGridId(H5CgnsZone* zone, int* gridId)
{
	return impl->getGridId(zone, gridId);
}

int H5CgnsFile::lastGridId(int* id)
{
	*id = static_cast<int> (impl->m_zones.size());

	return IRIC_NO_ERROR;
}

H5CgnsFileSolutionReader* H5CgnsFile::solutionReader()
{
	if (impl->m_solutionReader != nullptr) {return impl->m_solutionReader;}

	impl->m_solutionReader = new H5CgnsFileSolutionReader(this);
	return impl->m_solutionReader;
}

H5CgnsFileSolutionWriter* H5CgnsFile::solutionWriter()
{
	if (impl->m_solutionWriter != nullptr) {return impl->m_solutionWriter;}

	impl->m_solutionWriter = new H5CgnsFileSolutionWriter(impl->m_writerMode, this);
	return impl->m_solutionWriter;
}

void H5CgnsFile::setWriterMode(H5CgnsFileSolutionWriter::Mode mode)
{
	impl->m_writerMode = mode;
}
