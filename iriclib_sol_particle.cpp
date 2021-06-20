#include "error_macros.h"
#include "h5cgnsparticlesolution.h"
#include "h5cgnszone.h"
#include "iriclib_errorcodes.h"
#include "iriclib_sol_particle.h"
#include "vectorutil.h"

#include "internal/iric_logger.h"
#include "internal/iric_util.h"

using namespace iRICLib;

namespace {

int getParticleSolutionForRead(int fid, int gid, int step, H5CgnsParticleSolution** solution, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solread(fid, gid, step, &zone, f_name);
	RETURN_IF_ERR;

	*solution = zone->particleSolution();
	return IRIC_NO_ERROR;
}

int getParticleSolutionForWrite(int fid, int gid, H5CgnsParticleSolution** solution, const std::string& f_name)
{
	H5CgnsZone* zone = nullptr;
	int ier = _iric_get_zone_for_solwrite(fid, gid, &zone, f_name);
	RETURN_IF_ERR;

	*solution = zone->particleSolution();
	return IRIC_NO_ERROR;
}

} // namespace

int cg_iRIC_Read_Sol_Particle_Count_WithGridId(int fid, int gid, int step, int* count)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_Particle_WithGridId_Count");
	RETURN_IF_ERR;

	ier = solution->count(count);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(int fid, int gid, int step, double* x_arr, double* y_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_Particle_WithGridId_Pos2d");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec;
	ier = solution->readCoordinatesX(&xvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesY(&yvec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(int fid, int gid, int step, double* x_arr, double* y_arr, double* z_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_Particle_WithGridId_Pos3d");
	RETURN_IF_ERR;

	std::vector<double> xvec, yvec, zvec;
	ier = solution->readCoordinatesX(&xvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesY(&yvec);
	RETURN_IF_ERR;
	ier = solution->readCoordinatesZ(&zvec);
	RETURN_IF_ERR;

	_vectorToPointerT(xvec, x_arr);
	_vectorToPointerT(yvec, y_arr);
	_vectorToPointerT(zvec, z_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Particle_Real_WithGridId(int fid, int gid, int step, const char* name, double* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_Particle_WithGridId_Real");
	RETURN_IF_ERR;

	std::vector<double> buffer;
	ier = solution->readValue(name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Read_Sol_Particle_Integer_WithGridId(int fid, int gid, int step, const char* name, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForRead(fid, gid, step, &solution, "cg_iRIC_Read_Sol_Particle_WithGridId_Integer");
	RETURN_IF_ERR;

	std::vector<int> buffer;
	ier = solution->readValue(name, &buffer);
	RETURN_IF_ERR;

	_vectorToPointerT(buffer, v_arr);

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(int fid, int gid, int count, double* x_arr, double* y_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_Particle_WithGridId_Pos2d");
	RETURN_IF_ERR;

	std::vector<double> xvec(count), yvec(count);

	_pointerToVectorT(x_arr, &xvec);
	_pointerToVectorT(y_arr, &yvec);

	ier = solution->writeCoordinatesX(xvec);
	RETURN_IF_ERR;
	ier = solution->writeCoordinatesY(yvec);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(int fid, int gid, int count, double* x_arr, double* y_arr, double* z_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_Particle_WithGridId_Pos3d");
	RETURN_IF_ERR;

	std::vector<double> xvec(count), yvec(count), zvec(count);

	_pointerToVectorT(x_arr, &xvec);
	_pointerToVectorT(y_arr, &yvec);
	_pointerToVectorT(z_arr, &zvec);

	ier = solution->writeCoordinatesX(xvec);
	RETURN_IF_ERR;
	ier = solution->writeCoordinatesY(yvec);
	RETURN_IF_ERR;
	ier = solution->writeCoordinatesZ(zvec);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Particle_Real_WithGridId(int fid, int gid, const char* name, double* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_Particle_WithGridId_Real");
	RETURN_IF_ERR;

	int count;
	ier = solution->count(&count);
	RETURN_IF_ERR;;

	std::vector<double> buffer(count);

	_pointerToVectorT(v_arr, &buffer);

	ier = solution->writeValue(name, buffer);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}

int cg_iRIC_Write_Sol_Particle_Integer_WithGridId(int fid, int gid, const char* name, int* v_arr)
{
	_IRIC_LOGGER_TRACE_ENTER();

	H5CgnsParticleSolution* solution = nullptr;
	int ier = getParticleSolutionForWrite(fid, gid, &solution, "cg_iRIC_Write_Sol_Particle_WithGridId_Integer");
	RETURN_IF_ERR;

	int count;
	ier = solution->count(&count);
	RETURN_IF_ERR;;

	std::vector<int> buffer(count);

	_pointerToVectorT(v_arr, &buffer);

	ier = solution->writeValue(name, buffer);
	RETURN_IF_ERR;

	_IRIC_LOGGER_TRACE_LEAVE();
	return IRIC_NO_ERROR;
}
