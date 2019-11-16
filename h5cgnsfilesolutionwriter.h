#ifndef H5CGNSFILESOLUTIONWRITER_H
#define H5CGNSFILESOLUTIONWRITER_H

#include "iriclib_global.h"

namespace iRICLib {

class H5CgnsFile;

class H5CgnsFileSolutionWriter
{
public:
	enum Mode {
		Standard,
		Separate,
	};

	H5CgnsFileSolutionWriter(Mode mode, H5CgnsFile* file);
	~H5CgnsFileSolutionWriter();

	int writeTime(double time);
	int writeIteration(int iteration);

	H5CgnsFile* targetFile() const;

private:
	class Impl;
	Impl* impl;
};

} // namespace iRICLib

#ifdef _DEBUG
	#include "private/h5cgnsfilesolutionwriter_impl.h"
#endif // _DEBUG

#endif // H5CGNSFILESOLUTIONWRITER_H
