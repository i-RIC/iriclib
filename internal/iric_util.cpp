#include "../error_macros.h"
#include "../h5cgnsfile.h"
#include "../h5cgnsfilesolutionreader.h"
#include "../h5cgnsfilesolutionwriter.h"
#include "../iriclib_errorcodes.h"

#include "iric_h5cgnsfiles.h"
#include "iric_util.h"
#include "iric_outputerror.h"

namespace iRICLib {

int _iric_get_zone(int fid, int gid, H5CgnsZone** zone, const std::string& f_name)
{
	H5CgnsFile* file = nullptr;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	auto z = file->zoneById(gid);
	if (z == nullptr) {
		_iric_output_zonenotexists_error(fid, gid, f_name);
		return IRIC_GRID_NOT_FOUND;
	}

	*zone = z;

	return IRIC_NO_ERROR;
}

int _iric_get_zone_for_solread(int fid, int gid, int solid, H5CgnsZone** zone, const std::string& f_name)
{
	H5CgnsFile* file = nullptr;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	auto reader = file->solutionReader();
	reader->setSolutionId(solid);

	auto f2 = reader->targetFile();
	auto z = f2->zoneById(gid);
	if (z == nullptr) {
		_iric_output_zonenotexists_error(fid, gid, f_name);
		return IRIC_GRID_NOT_FOUND;
	}

	*zone = z;

	return IRIC_NO_ERROR;
}

int _iric_get_zone_for_solwrite(int fid, int gid, H5CgnsZone** zone, const std::string& f_name)
{
	H5CgnsFile* file = nullptr;
	int ier = _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	auto writer = file->solutionWriter();
	auto f2 = writer->targetFile();
	auto z = f2->zoneById(gid);
	if (z == nullptr) {
		_iric_output_zonenotexists_error(fid, gid, f_name);
		return IRIC_GRID_NOT_FOUND;
	}

	*zone = z;

	return IRIC_NO_ERROR;
}

} // namespace iRICLib
