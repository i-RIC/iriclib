#include "h5cgnsfilesolutionwriter.h"
#include "h5cgnsfile.h"

#include "private/h5cgnsfilesolutionwriter_impl.h"

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
