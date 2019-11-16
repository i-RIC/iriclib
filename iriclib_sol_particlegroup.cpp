#include "error_macros.h"
#include "h5cgnsparticlegroupsolution.h"
#include "h5cgnszone.h"
#include "iriclib_errorcodes.h"
#include "iriclib_sol_particlegroup.h"
#include "vectorutil.h"

#include "internal/iric_util.h"

using namespace iRICLib;

namespace {

int getParticleGroupSolutionForRead(int fid, int gid, int step, H5CgnsParticleGroupSolution** solution, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solread(fid, gid, step, &zone, f_name);
	RETURN_IF_ERR;

	*solution = zone->particleGroupSolution();
	return IRIC_NO_ERROR;
}

int getParticleGroupSolutionForWrite(int fid, int gid, H5CgnsParticleGroupSolution** solution, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solwrite(fid, gid, &zone, f_name);
	RETURN_IF_ERR;

	*solution = zone->particleGroupSolution();
	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Sol_ParticleGroup_Count_WithGridId_Mul(int fid, int gid, int step, const char* groupname, int* count)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_ParticleGroup_WithGridId_Count_Mul");
	RETURN_IF_ERR;

	ier = solution->count(groupname, count);
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, double* x_arr, double* y_arr)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_ParticleGroup_WithGridId_Pos2d_Mul");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec;
	ier = solution->readCoordinatesX(groupname, &xvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesY(groupname, &yvec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId_Mul(int fid, int gid, int step, const char* groupname, double* x_arr, double* y_arr, double* z_arr)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_ParticleGroup_WithGridId_Pos3d_Mul");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec, zvec;
	ier = solution->readCoordinatesX(groupname, &xvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesY(groupname, &yvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesZ(groupname, &zvec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);
	_vectorToPointerT(zvec, z_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, double* v_arr)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_ParticleGroup_WithGridId_Real_Mul");
	RETURN_IF_ERR;

	std::vector<double> buffer;
	ier = solution->readValue(groupname, name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId_Mul(int fid, int gid, int step, const char* groupname, const char* name, int* v_arr)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_ParticleGroup_WithGridId_Integer_Mul");
	RETURN_IF_ERR;

	std::vector<int> buffer;
	ier = solution->readValue(groupname, name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_WithGridId_Mul(int fid, int gid, const char* name)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_WithGridId_Mul");
	RETURN_IF_ERR;

	solution->writeBegin(name);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_WithGridId_Mul(int fid, int gid)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_WithGridId_Mul");
	RETURN_IF_ERR;

	ier = solution->writeEnd();
	RETURN_IF_ERR;

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroup_Pos2d_WithGridId_Mul(int fid, int gid, double x, double y)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroup_Pos2d_WithGridId_Mul");
	RETURN_IF_ERR;

	solution->writePos2d(x, y);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroup_Pos3d_WithGridId_Mul(int fid, int gid, double x, double y, double z)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroup_Pos3d_WithGridId_Mul");
	RETURN_IF_ERR;

	solution->writePos3d(x, y, z);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroup_Integer_WithGridId_Mul(int fid, int gid, const char* name, int value)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroup_Integer_WithGridId_Mul");
	RETURN_IF_ERR;

	solution->writeValue(name, value);

	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_ParticleGroup_Real_WithGridId_Mul(int fid, int gid, const char* name, double value)
{
	H5CgnsParticleGroupSolution* solution = nullptr;
	int ier = getParticleGroupSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_ParticleGroup_Real_WithGridId_Mul");
	RETURN_IF_ERR;

	solution->writeValue(name, value);

	return IRIC_NO_ERROR;
}