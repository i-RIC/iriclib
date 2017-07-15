#ifndef FS_COPY_H
#define FS_COPY_H

#include <fstream>

namespace fs {

inline void copy(const std::string& from, const std::string& to)
{
	std::ifstream ifs(from, std::ios_base::binary);
	std::ofstream ofs(to, std::ios_base::binary | std::ios_base::trunc);
	ofs << ifs.rdbuf();
}

} // fs

#endif // FS_COPY_H
