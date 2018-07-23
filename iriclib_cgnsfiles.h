#ifndef IRICLIB_CGNSFILES_H
#define IRICLIB_CGNSFILES_H

#include <vector>

namespace iRICLib {

class CgnsFile;

class CgnsFiles
{
public:
	CgnsFiles();
	~CgnsFiles();

	CgnsFile*& operator[] (int index);
	CgnsFile* at(int index) const;
	int size() const;

	CgnsFiles& operator=(const std::vector<CgnsFile*> files);

private:
	std::vector<CgnsFile*> m_files;
};

} // namespace iRICLib

#endif // IRICLIB_CGNSFILES_H
