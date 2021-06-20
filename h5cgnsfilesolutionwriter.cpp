#include "error_macros.h"
#include "h5cgnsfilesolutionwriter.h"
#include "h5cgnsfile.h"
#include "iriclib_errorcodes.h"

#include "private/h5cgnsfilesolutionwriter_impl.h"

#include <Poco/File.h>

using namespace iRICLib;

H5CgnsFileSolutionWriter::H5CgnsFileSolutionWriter(Mode mode, H5CgnsFile* file) :
	impl {new Impl {this}}
{
	impl->m_mode = mode;
	impl->m_file = file;
}

H5CgnsFileSolutionWriter::~H5CgnsFileSolutionWriter()
{
	delete impl;
}

int H5CgnsFileSolutionWriter::writeTime(double time)
{
	return impl->writeTime(time);
}

int H5CgnsFileSolutionWriter::writeIteration(int iteration)
{
	return impl->writeIteration(iteration);
}

int H5CgnsFileSolutionWriter::writeBaseIterativeData(const std::string& name, int value)
{
	return impl->writeBaseIterativeData(name, value);
}

int H5CgnsFileSolutionWriter::writeBaseIterativeData(const std::string& name, double value)
{
	return impl->writeBaseIterativeData(name, value);
}

int H5CgnsFileSolutionWriter::writeBaseIterativeData(const std::string& name, const std::string value)
{
	return impl->writeBaseIterativeData(name, value);
}

H5CgnsFile* H5CgnsFileSolutionWriter::targetFile() const
{
	if (impl->m_mode == Mode::Standard) {
		return impl->m_file;
	} else {
		return impl->m_targetFile;
	}
}

int H5CgnsFileSolutionWriter::flush()
{
	delete impl->m_targetFile;
	impl->m_targetFile = nullptr;

	int ier = impl->m_file->flush();
	RETURN_IF_ERR;

	Poco::File tmpFile(impl->m_file->tmpFileName());
	if (tmpFile.exists()) {
		try {
			tmpFile.remove();
		} catch (...) {
			// do nothing
		}
	}

	Poco::File cgnsFile(impl->m_file->fileName());
	cgnsFile.copyTo(impl->m_file->tmpFileName());

	return IRIC_NO_ERROR;
}

int H5CgnsFileSolutionWriter::close()
{
	Poco::File tmpFile(impl->m_file->tmpFileName());
	if (tmpFile.exists()) {
		try {
			tmpFile.remove();
		} catch (...) {
			// do nothing
		}
	}
	return IRIC_NO_ERROR;
}
