#include "error_macros.h"
#include "h5cgnsbase.h"
#include "h5cgnsfile.h"
#include "h5cgnsgeographicdatagroup.h"
#include "h5cgnsgeographicdatatop.h"
#include "iriclib_errorcodes.h"
#include "iriclib_geoutil.h"

#include "internal/iric_h5cgnsfiles.h"
#include "internal/iric_logger.h"

#include <sstream>

using namespace iRICLib;

namespace {

int getGeoGraphicDataGroup(int fid, const std::string& name, H5CgnsGeographicDataGroup** group)
{
	H5CgnsFile* file = nullptr;
	int ier= _iric_h5cgnsfiles_get(fid, &file);
	RETURN_IF_ERR;

	auto geoDataTop = file->ccBase()->geoDataTop();

	if (! geoDataTop->groupExists(name)) {
		std::ostringstream ss;
		ss << "In getGeoGraphicDataGroup(), group with name " << name << " not found";
		_iric_logger_error(ss.str());

		return IRIC_INVALID_GROUPNAME;
	}

	*group = geoDataTop->group(name);
	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Geo_Count(int fid, const char* name, int* count)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGeographicDataGroup* group;
	int ier = getGeoGraphicDataGroup(fid, name, &group);
	RETURN_IF_ERR;

	ier = group->count(count);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Geo_Filename(int fid, const char* name, int geoid, char* strvalue, int* type)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsGeographicDataGroup* group;
	int ier = getGeoGraphicDataGroup(fid, name, &group);
	RETURN_IF_ERR;

	std::string fname;
	H5CgnsGeographicDataGroup::Type t;
	ier = group->read(geoid, &fname, &t);
	RETURN_IF_ERR;

	for (size_t i = 0; i < fname.length(); ++i) {
		*(strvalue + i) = fname.at(i);
	}
	*(strvalue + fname.length()) = 0;
	*type = static_cast<int> (t);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}
