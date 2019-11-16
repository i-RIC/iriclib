#include "../error_macros.h"
#include "../h5cgnsfile.h"
#include "../h5cgnsfileseparatesolutionutil.h"
#include "../iriclib_errorcodes.h"

#include "../internal/iric_logger.h"

#include "h5cgnsfilesolutionwriter_impl.h"

#include <sstream>

using namespace iRICLib;

H5CgnsFileSolutionWriter::Impl::Impl(H5CgnsFileSolutionWriter* writer) :
	m_targetFile {nullptr},
	m_solutionId {0},
	m_writer {writer}
{}

H5CgnsFileSolutionWriter::Impl::~Impl()
{
	delete m_targetFile;
}

int H5CgnsFileSolutionWriter::Impl::writeTime(double time)
{
	if (m_mode == Mode::Standard) {
		return writeTimeStandard(time);
	} else if (m_mode == Mode::Separate) {
		return writeTimeSeparate(time);
	}

	return IRIC_NO_ERROR;
}

int H5CgnsFileSolutionWriter::Impl::writeIteration(int iteration)
{
	if (m_mode == Mode::Standard) {
		return writeIterationStandard(iteration);
	} else if (m_mode == Mode::Separate) {
		return writeIterationSeparate(iteration);
	}

	return IRIC_NO_ERROR;
}

int H5CgnsFileSolutionWriter::Impl::writeTimeStandard(double time)
{
	return m_file->writeTime(time);
}

int H5CgnsFileSolutionWriter::Impl::writeTimeSeparate(double time)
{
	delete m_targetFile;

	++ m_solutionId;
	int ier = H5CgnsFileSeparateSolutionUtil::createResultFolderIfNotExists(m_file->fileName());
	RETURN_IF_ERR;

	auto fName = H5CgnsFileSeparateSolutionUtil::fileNameForSolution(m_file->fileName(), m_solutionId);
	try {
		m_targetFile = new H5CgnsFile(fName, H5CgnsFile::Mode::Create);
	} catch (...) {
		std::ostringstream ss;
		ss << "In H5CgnsFileSolutionWriter::Impl::writeIterationSeparate(), creating " << fName << " failed";
		_iric_logger_error(ss.str());
		return IRIC_H5_CREATE_FAIL;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::copyGrids");
	ier = m_file->copyGridsTo(m_targetFile);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::copyGrids", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::writeTime");
	ier = m_file->writeTime(time);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::writeTime", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::writeTime");
	ier = m_targetFile->writeTime(time);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::writeTime", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFileSolutionWriter::Impl::writeIterationStandard(int iteration)
{
	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::writeIteration");
	int ier = m_file->writeIteration(iteration);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::writeIteration", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int H5CgnsFileSolutionWriter::Impl::writeIterationSeparate(int iteration)
{
	delete m_targetFile;
	m_targetFile = nullptr;

	++ m_solutionId;
	int ier = H5CgnsFileSeparateSolutionUtil::createResultFolderIfNotExists(m_file->fileName());
	RETURN_IF_ERR;

	auto fName = H5CgnsFileSeparateSolutionUtil::fileNameForSolution(m_file->fileName(), m_solutionId);
	try {
		m_targetFile = new H5CgnsFile(fName, H5CgnsFile::Mode::Create);
	} catch (...) {
		std::ostringstream ss;
		ss << "In H5CgnsFileSolutionWriter::Impl::writeIterationSeparate(), creating " << fName << " failed";
		_iric_logger_error(ss.str());
		return IRIC_H5_CREATE_FAIL;
	}

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::copyGrids");
	ier = m_file->copyGridsTo(m_targetFile);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::copyGrids", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::writeIteration");
	ier = m_file->writeIteration(iteration);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::writeIteration", ier);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::writeIteration");
	ier = m_targetFile->writeIteration(iteration);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::writeIteration", ier);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}
