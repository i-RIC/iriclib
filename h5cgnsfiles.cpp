#include "h5cgnsfile.h"
#include "h5cgnsfiles.h"
#include "iriclib_errorcodes.h"

#include "internal/iric_logger.h"

#include <sstream>

using namespace iRICLib;

H5CgnsFiles::H5CgnsFiles()
{}

H5CgnsFiles::~H5CgnsFiles()
{
	clear();
}

H5CgnsFile* H5CgnsFiles::operator[] (int fid)
{
	return m_files[fid - 1];
}

H5CgnsFile* H5CgnsFiles::at(int fid) const
{
	return m_files.at(fid - 1);
}

int H5CgnsFiles::size() const
{
	return static_cast<int> (m_files.size());
}

int H5CgnsFiles::registerFile(H5CgnsFile* file)
{
	for (unsigned int i = 0; i < m_files.size(); ++i) {
		if (m_files[i] == nullptr) {
			m_files[i] = file;
			return i + 1;
		}
	}
	m_files.push_back(file);
	return static_cast<int> (m_files.size());
}

int H5CgnsFiles::unregisterFile(int fid)
{
	if (fid <= 0 || fid > static_cast<int>(m_files.size())) {
		std::ostringstream ss;
		ss << "In H5CgnsFiles::unregisterFile(), invalid fid << " << fid << " specified. m_files.size() == " << m_files.size();
		_iric_logger_error(ss.str());

		return IRIC_INVALID_FILEID;
	}

	if (m_files[fid - 1] == nullptr) {
		std::ostringstream ss;
		ss << "In H5CgnsFiles::unregisterFile(), the file with fid << " << fid << " is already unregistered. Ignored.";
		_iric_logger_warn(ss.str());

		return IRIC_NO_ERROR;
	}

	delete m_files[fid - 1];
	m_files[fid - 1] = nullptr;

	return IRIC_NO_ERROR;
}

void H5CgnsFiles::clear()
{
	for (auto f : m_files) {
		delete f;
	}
	m_files.clear();
}
