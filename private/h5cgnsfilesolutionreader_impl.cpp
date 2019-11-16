#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsbaseiterativedata.h"
#include "h5cgnsfile.h"
#include "h5cgnsfileseparatesolutionutil.h"
#include "h5cgnsfilesolutionreader_impl.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include <Poco/File.h>

#include <algorithm>
#include <sstream>

using namespace iRICLib;

H5CgnsFileSolutionReader::Impl::Impl(H5CgnsFileSolutionReader* reader) :
	m_mode {Mode::Standard},
	m_file {nullptr},
	m_targetFile {nullptr},
	m_solutionId {0},
	m_reader {reader}
{}

H5CgnsFileSolutionReader::Impl::~Impl()
{
	delete m_targetFile;
}

int H5CgnsFileSolutionReader::Impl::setSolutionId(int id)
{
	if (m_mode == Mode::Standard) {
		return setSolutionIdStandard(id);
	} else if (m_mode == Mode::Separate) {
		return setSolutionIdSeparate(id);
	}

	return IRIC_NO_ERROR;
}

void H5CgnsFileSolutionReader::Impl::detectMode()
{
	m_mode = Mode::Standard;

	std::vector<double> timeVals;
	std::vector<int> iterVals;
	m_file->ccBase()->biterData()->readTime(&timeVals);
	m_file->ccBase()->biterData()->readIteration(&iterVals);

	auto maxSolId = static_cast<int> (max(timeVals.size(), iterVals.size()));
	if (maxSolId == 0) {return;}

	auto fName = H5CgnsFileSeparateSolutionUtil::fileNameForSolution(m_file->fileName(), maxSolId);
	Poco::File f(fName);
	if (f.exists()) {
		m_mode = Mode::Separate;
	}
}

int H5CgnsFileSolutionReader::Impl::setSolutionIdStandard(int id)
{
	if (m_solutionId == id) {return IRIC_NO_ERROR;}

	_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::setSolutionId");
	int ier = m_file->setSolutionId(id);
	_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::setSolutionId", ier);
	RETURN_IF_ERR;

	m_solutionId = id;

	return IRIC_NO_ERROR;
}

int H5CgnsFileSolutionReader::Impl::setSolutionIdSeparate(int id)
{
	if (m_solutionId == id) {return IRIC_NO_ERROR;}

	delete m_targetFile;
	m_targetFile = nullptr;

	auto Fname = H5CgnsFileSeparateSolutionUtil::fileNameForSolution(m_file->fileName(), id);
	try {
		m_targetFile = new H5CgnsFile(Fname, H5CgnsFile::Mode::OpenReadOnly);
		_IRIC_LOGGER_TRACE_CALL_START("H5CgnsFile::setSolutionId");
		int ier = m_targetFile->setSolutionId(1);
		_IRIC_LOGGER_TRACE_CALL_END_WITHVAL("H5CgnsFile::setSolutionId", ier);
		m_solutionId = id;
		return IRIC_NO_ERROR;
	} catch (...) {
		std::ostringstream ss;
		ss << "In H5CgnsFileSolutionReader::Impl::setSolutionIdSeparate(), opening " << Fname << " failed";
		_iric_logger_error(ss.str());
		return IRIC_H5_CREATE_FAIL;
	}
}
