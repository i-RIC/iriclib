#include "h5cgnsfilesolutionreader.h"

#include "private/h5cgnsfilesolutionreader_impl.h"

using namespace iRICLib;

H5CgnsFileSolutionReader::H5CgnsFileSolutionReader(H5CgnsFile* file) :
	impl {new Impl {this}}
{
	impl->m_file = file;

	impl->detectMode();
}

H5CgnsFileSolutionReader::~H5CgnsFileSolutionReader()
{
	delete impl;
}

H5CgnsFileSolutionReader::Mode H5CgnsFileSolutionReader::mode() const
{
	return impl->m_mode;
}

int H5CgnsFileSolutionReader::setSolutionId(int id)
{
	return impl->setSolutionId(id);
}

H5CgnsFile* H5CgnsFileSolutionReader::targetFile() const
{
	if (impl->m_mode == Mode::Standard) {
		return impl->m_file;
	} else {
		return impl->m_targetFile;
	}
}
