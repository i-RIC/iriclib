#include "iriclib_cgnsfiles.h"
#include "iriclib_cgnsfile.h"

using namespace iRICLib;

CgnsFiles::CgnsFiles()
{}

CgnsFiles::~CgnsFiles()
{
	for (int id = 0; id != m_files.size(); ++id)
	{
		CgnsFile* f = m_files[id];
		if (f == nullptr) {continue;}

		delete f;
		m_files[id] = nullptr;
		cg_close(id);
	}
}

CgnsFile*& CgnsFiles::operator[] (int index)
{
	return m_files[index];
}

CgnsFile* CgnsFiles::at(int index) const
{
	return m_files.at(index);
}

int CgnsFiles::size() const
{
	return m_files.size();
}

CgnsFiles& CgnsFiles::operator=(const std::vector<CgnsFile*> files)
{
	m_files = files;

	return *this;
}
