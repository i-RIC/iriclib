#include "iric_logger.h"
#include "iric_outputerror.h"

#include <sstream>

namespace iRICLib {

void _iric_output_zonenotexists_error(int fid, int gid, const std::string& fname)
{
	std::ostringstream ss;
	ss << "In " << fname << "(), CGNS file with fid " << fid << " does not have grid for gid " << gid;
	_iric_logger_error(ss.str());
}

} // namespace iRICLib
