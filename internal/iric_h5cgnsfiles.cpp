#include "iric_h5cgnsfiles.h"
#include "../h5cgnsfiles.h"
#include "../iriclib_errorcodes.h"

#include "iric_logger.h"

#include <sstream>

namespace {

iRICLib::H5CgnsFiles files;
int lastFileId = 0;

}

namespace iRICLib
{

int _iric_lastFileId(int* fid)
{
	*fid = lastFileId;
	return IRIC_NO_ERROR;
}

int _iric_h5cgnsfiles_register(H5CgnsFile* file, int* fid)
{
	*fid = files.registerFile(file);
	lastFileId = *fid;

	return IRIC_NO_ERROR;
}

int _iric_h5cgnsfiles_unregister(int fid)
{
	return files.unregisterFile(fid);
}

int _iric_h5cgnsfiles_get(int fid, H5CgnsFile** file)
{
	if (fid < 1 || fid > files.size()) {
		std::ostringstream ss;
		ss << "In _iric_h5cgnsfiles_get() wrong fid " << fid << " specified";
		_iric_logger_error(ss.str());

		return IRIC_INVALID_FILEID;
	}

	*file = files.at(fid);
	return IRIC_NO_ERROR;
}

} // namespace iRICLib
