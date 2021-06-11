#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>
#ifdef _MSC_VER
#endif

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

extern "C" {

void writeSolution(const char* filename, int* fid, bool iterMode)
{
	int isize, jsize;

	int ier = cg_iRIC_Read_Grid2d_Str_Size_Mul(*fid, &isize, &jsize);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size_Mul() ier == 0", ier == 0);

	std::vector<double> x, y;
	std::vector<double> vx, vy, depth;
	std::vector<int> wet;
	std::vector<double> ccdepth;
	std::vector<int> ccwet;

	// fill iface
	std::vector<int> iface_is_edge;
	std::vector<double> iface_is_edge_reals;
	iface_is_edge.assign(isize*(jsize - 1), 0);
	iface_is_edge_reals.assign(isize*(jsize - 1), 0.);
	for (int j = 0; j < jsize - 1; ++j) {
		for (int i = 0; i < isize; ++i) {
			if (j == 0 || j == (jsize - 2) || i == 0 || i == (isize - 1)) {
				iface_is_edge[j * isize + i] = 1;
				iface_is_edge_reals[j * isize + i] = .1;
			}
		}
	}

	// fill jface
	std::vector<int> jface_is_edge;
	std::vector<double> jface_is_edge_reals;
	jface_is_edge.assign((isize - 1)*jsize, 0);
	jface_is_edge_reals.assign((isize - 1)*jsize, 0.);
	for (int j = 0; j < jsize; ++j) {
		for (int i = 0; i < isize - 1; ++i) {
			if (j == 0 || j == (jsize - 1) || i == 0 || i == (isize - 2)) {
				jface_is_edge[j * (isize - 1) + i] = 2;
				jface_is_edge_reals[j * (isize - 1) + i] = .2;
			}
		}
	}

	std::vector<double> particle_x, particle_y;
	std::vector<double> particle_vx, particle_vy;
	std::vector<int> particle_active;

	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);
	ier = cg_iRIC_Read_Grid2d_Coords_Mul(*fid, x.data(), y.data());

	vx.assign(isize * jsize, 1);
	vy.assign(isize * jsize, 0.3);
	depth.assign(isize * jsize, 4);
	wet.assign(isize * jsize, 0);

	int particle_num = 20;
	particle_x.assign(particle_num, 0);
	particle_y.assign(particle_num, 0);
	particle_vx.assign(particle_num, 2);
	particle_vy.assign(particle_num, 3);
	particle_active.assign(particle_num, 1);

	for (int i = 0; i < particle_num; ++i) {
		particle_x[i] = i;
	}

	for (int i = 0; i < 5; ++i) {
		if (iterMode) {
			int IterVal = i;
			ier = cg_iRIC_Write_Sol_Iteration_Mul(*fid, IterVal);
			VERIFY_LOG("cg_iRIC_Write_Sol_Iteration_Mul() ier == 0", ier == 0);
		} else {
			double TimeVal = i * 2.13;
			ier = cg_iRIC_Write_Sol_Time_Mul(*fid, TimeVal);
			VERIFY_LOG("cg_iRIC_Write_Sol_Time_Mul() ier == 0", ier == 0);
		}

		ier = cg_iRIC_Write_Sol_Grid2d_Coords_Mul(*fid, x.data(), y.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Grid2d_Coords_Mul() ier == 0", ier == 0);

		// Vertex solutions

		depth.assign(isize * jsize, (double)i);
		ier = cg_iRIC_Write_Sol_Node_Real_Mul(*fid, "Depth", depth.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Node_Real_Mul() for Depth ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Node_Real_Mul(*fid, "VelocityX", vx.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Node_Real_Mul() for VelocityX ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Node_Real_Mul(*fid, "VelocityY", vy.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Node_Real_Mul() for VelocityY ier == 0", ier == 0);

		wet.assign(isize * jsize, i);
		ier = cg_iRIC_Write_Sol_Node_Integer_Mul(*fid, "IBC", wet.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Node_Integer_Mul() for IBC ier == 0", ier == 0);

		// CellCenter solutions

		ccdepth.assign((isize - 1) * (jsize - 1), 0.2 + i);
		ier = cg_iRIC_Write_Sol_Cell_Real("CCDepth", ccdepth.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Real() ier == 0", ier == 0);

		ccwet.assign((isize - 1) * (jsize - 1), i + 1);
		ier = cg_iRIC_Write_Sol_Cell_Integer("CCWet", ccwet.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Integer() ier == 0", ier == 0);

		// IFaceCenter solutions

		ier = cg_iRIC_Write_Sol_IFace_Integer_Mul(*fid, "IFaceIsEdge", iface_is_edge.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_IFace_Integer() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_IFace_Real_Mul(*fid, "IFaceIsEdgeReals", iface_is_edge_reals.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_IFace_Real() ier == 0", ier == 0);

		// JFaceCenter solutions

		ier = cg_iRIC_Write_Sol_JFace_Integer_Mul(*fid, "JFaceIsEdge", jface_is_edge.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_JFace_Integer() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_JFace_Real_Mul(*fid, "JFaceIsEdgeReals", jface_is_edge_reals.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_JFace_Real() ier == 0", ier == 0);

		// BaseIterativeData

		double Dist = i * - 0.2 + 20;
		ier = cg_iRIC_Write_Sol_BaseIterative_Real_Mul(*fid, "Discharge", Dist);
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Real_Mul() for Discharge ier == 0", ier == 0);
		int DamOpen = i;
		ier = cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(*fid, "DamOpen", DamOpen);
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Integer_Mul() for DamOpen ier == 0", ier == 0);
		std::ostringstream ss;
		ss << "Test" << i;
		ier = cg_iRIC_Write_Sol_BaseIterative_String_Mul(*fid, "TestStr", ss.str().c_str());
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_String_Mul() for TestStr ier == 0", ier == 0);

		// Particle solutions

		ier = cg_iRIC_Write_Sol_Particle_Pos2d_Mul(*fid, particle_num, particle_x.data(), particle_y.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Pos2d_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(*fid, "VelX", particle_vx.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelX ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(*fid, "VelY", particle_vy.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelY ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Integer_Mul(*fid, "Active", particle_active.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Integer_Mul() for Active ier == 0", ier == 0);

		// ParticleGroup solutions

		ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(*fid, "group1");
		VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul() ier == 0", ier == 0);
		for (int j = 0; j < particle_num; ++j) {
			ier = cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul(*fid, particle_x.at(j), particle_y.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul() for VelX ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, "VelX", particle_vx.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Real_Mul() for VelX ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, "VelY", particle_vy.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Real_Mul() for VelY ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(*fid, "Active", particle_active.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul() for VelX ier == 0", ier == 0);
		}
		ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(*fid);
		VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(*fid, "group2");
		VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul() ier == 0", ier == 0);
		for (int j = 0; j < particle_num; ++j) {
			ier = cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul(*fid, particle_x.at(j), 2);
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul() for VelX ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, "VelX", particle_vx.at(j) + 2);
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Real_Mul() for VelX ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, "VelY", particle_vy.at(j) + 1);
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Real_Mul() for VelY ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(*fid, "Active", particle_active.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul() for VelX ier == 0", ier == 0);
		}
		ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(*fid);
		VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Flush(*fid);
		VERIFY_LOG("cg_iRIC_Flush() ier == 0", ier == 0);
	}
}

void writeSolution3d(const char* filename, int* fid)
{
	int isize, jsize;

	int ier = cg_iRIC_Read_Grid2d_Str_Size_Mul(*fid, &isize, &jsize);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size_Mul() ier == 0", ier == 0);

	std::vector<double> x, y, z;
	std::vector<double> vx, vy, depth;
	std::vector<int> wet;

	std::vector<double> particle_x, particle_y, particle_z;
	std::vector<double> particle_vx, particle_vy, particle_vz;
	std::vector<int> particle_active;

	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);
	z.assign(isize * jsize, 0);
	ier = cg_iRIC_Read_Grid2d_Coords_Mul(*fid, x.data(), y.data());

	ier = cg_iRIC_Write_Grid3d_Coords_Mul(*fid, isize, jsize, 1, x.data(), y.data(), z.data());
	VERIFY_LOG("cg_iRIC_Write_Grid3d_Coords_Mul() ier == 0", ier == 0);

	vx.assign(isize * jsize, 1);
	vy.assign(isize * jsize, 0.3);
	depth.assign(isize * jsize, 4);
	wet.assign(isize * jsize, 0);

	int particle_num = 20;
	particle_x.assign(particle_num, 0);
	particle_y.assign(particle_num, 0);
	particle_z.assign(particle_num, 0);
	particle_vx.assign(particle_num, 2);
	particle_vy.assign(particle_num, 3);
	particle_vz.assign(particle_num, 1);
	particle_active.assign(particle_num, 1);

	for (int i = 0; i < particle_num; ++i) {
		particle_x[i] = i;
	}

	for (int i = 0; i < 5; ++i) {
		double TimeVal = i * 2.13;
		ier = cg_iRIC_Write_Sol_Time_Mul(*fid, TimeVal);
		VERIFY_LOG("cg_iRIC_Write_Sol_Time_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Grid3d_Coords_Mul(*fid, x.data(), y.data(), z.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Grid3d_Coords_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Node_Real_Mul(*fid, "Depth", depth.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Node_Real_Mul() for Depth ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Node_Real_Mul(*fid, "VelocityX", vx.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Node_Real_Mul() for VelocityX ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Node_Real_Mul(*fid, "VelocityY", vy.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Node_Real_Mul() for VelocityY ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Node_Integer_Mul(*fid, "IBC", wet.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Node_Integer_Mul() for IBC ier == 0", ier == 0);

		double Dist = i * - 0.2 + 20;
		ier = cg_iRIC_Write_Sol_BaseIterative_Real_Mul(*fid, "Discharge", Dist);
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Real_Mul() for Discharge ier == 0", ier == 0);
		int DamOpen = i;
		ier = cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(*fid, "DamOpen", DamOpen);
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Integer_Mul() for DamOpen ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Pos3d_Mul(*fid, particle_num, particle_x.data(), particle_y.data(), particle_z.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Pos2d_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(*fid, "VelX", particle_vx.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelX ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(*fid, "VelY", particle_vy.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelY ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(*fid, "VelZ", particle_vz.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelZ ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Integer_Mul(*fid, "Active", particle_active.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Integer_Mul() for Active ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(*fid, "group1");
		VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul() ier == 0", ier == 0);
		for (int j = 0; j < particle_num; ++j) {
			ier = cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul(*fid, particle_x.at(j), particle_y.at(j), particle_z.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul() for VelX ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, "VelX", particle_vx.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Real_Mul() for VelX ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, "VelY", particle_vy.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Real_Mul() for VelY ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(*fid, "Active", particle_active.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul() for VelX ier == 0", ier == 0);
		}
		ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(*fid);
		VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(*fid, "group2");
		VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul() ier == 0", ier == 0);
		for (int j = 0; j < particle_num; ++j) {
			ier = cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul(*fid, particle_x.at(j), particle_y.at(j), 2);
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul() for VelX ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, "VelX", particle_vx.at(j) + 1);
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Real_Mul() for VelX ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, "VelY", particle_vy.at(j) + 2);
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Real_Mul() for VelY ier == 0", ier == 0);

			ier = cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(*fid, "Active", particle_active.at(j));
			VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul() for VelX ier == 0", ier == 0);
		}
		ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(*fid);
		VERIFY_LOG("cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Flush(*fid);
		VERIFY_LOG("cg_iRIC_Flush() ier == 0", ier == 0);
	}
}

void readSolution(int fid)
{
	char buffer[200];
	int sol_count;
	int ier = cg_iRIC_Read_Sol_Count_Mul(fid, &sol_count);
	VERIFY_LOG("cg_iRIC_Read_Sol_Count_Mul() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Sol_Count_Mul() sol_count == 5", sol_count == 5);

	//double t;
	int isize, jsize;

	std::vector<double> grid_x, grid_y;
	std::vector<double> real_sol;
	std::vector<int> int_sol;
	std::vector<double> real_ccsol;
	std::vector<int> int_ccsol;
	std::vector<int> iface_is_edge;
	std::vector<double> iface_is_edge_reals;
	std::vector<int> jface_is_edge;
	std::vector<double> jface_is_edge_reals;

	ier = cg_iRIC_Read_Grid2d_Str_Size_Mul(fid, &isize, &jsize);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size_Mul() ier == 0", ier == 0);

	grid_x.assign(isize * jsize, 0);
	grid_y.assign(isize * jsize, 0);
	real_sol.assign(isize * jsize, 0);
	int_sol.assign(isize * jsize, 0);
	real_ccsol.assign((isize - 1) * (jsize - 1), 0);
	int_ccsol.assign((isize - 1) * (jsize - 1), 0);
	iface_is_edge.assign(isize * (jsize - 1), 0);
	iface_is_edge_reals.assign(isize * (jsize - 1), 0);
	jface_is_edge.assign((isize - 1) * jsize, 0);
	jface_is_edge_reals.assign((isize - 1) * jsize, 0);

	for (int S = 1; S <= sol_count; ++S) {

		// GridCoord

		ier = cg_iRIC_Read_Sol_Grid2d_Coords_Mul(fid, S, grid_x.data(), grid_y.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Grid2d_Coords_Mul() ier == 0", ier == 0);

		// Vertex solutions

		ier = cg_iRIC_Read_Sol_Node_Real_Mul(fid, S, "Depth", real_sol.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Node_Real_Mul() ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_Node_Real_Mul() real_sol[0] == %g", (double)(S - 1));
		VERIFY_LOG(buffer, real_sol[0] == (double)(S - 1));
		sprintf(buffer, "cg_iRIC_Read_Sol_Node_Real_Mul() real_sol[%lu] == %g", real_sol.size() - 1, (double)(S - 1));
		VERIFY_LOG(buffer, real_sol[real_sol.size()-1] == (double)(S - 1));

		ier = cg_iRIC_Read_Sol_Node_Integer_Mul(fid, S, "IBC", int_sol.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Node_Integer_Mul() ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_Node_Integer_Mul() int_sol[0] == %d", (S - 1));
		VERIFY_LOG(buffer, int_sol[0] == (S - 1));
		sprintf(buffer, "cg_iRIC_Read_Sol_Node_Integer_Mul() int_sol[%lu] == %d", int_sol.size() - 1, (S - 1));
		VERIFY_LOG(buffer, int_sol[int_sol.size() - 1] == (S - 1));

		// CellCenter solutions

		ier = cg_iRIC_Read_Sol_Cell_Real_Mul(fid, S, "CCDepth", real_ccsol.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Cell_Real_Mul() ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_Cell_Real_Mul() real_ccsol[0] == %g", 0.2 + (S - 1));
		VERIFY_LOG(buffer, real_ccsol[0] == 0.2 + (S - 1));
		sprintf(buffer, "cg_iRIC_Read_Sol_Cell_Real_Mul() real_ccsol[%lu] == %g", real_ccsol.size() - 1, 0.2 + (S - 1));
		VERIFY_LOG(buffer, real_ccsol[real_ccsol.size() - 1] == 0.2 + (S - 1));

		ier = cg_iRIC_Read_Sol_Cell_Integer_Mul(fid, S, "CCWet", int_ccsol.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Cell_Integer_Mul() ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_Cell_Integer_Mul() int_ccsol[0] == %d", S);
		VERIFY_LOG(buffer, int_ccsol[0] == S);
		sprintf(buffer, "cg_iRIC_Read_Sol_Cell_Integer_Mul() int_ccsol[%lu] == %d", int_ccsol.size() - 1, S);
		VERIFY_LOG(buffer, int_ccsol[int_ccsol.size() - 1] == S);

		// IFaceCenter solutions

		ier = cg_iRIC_Read_Sol_IFace_Integer_Mul(fid, S, "IFaceIsEdge", iface_is_edge.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_IFace_Integer() ier == 0", ier == 0);

		ier = cg_iRIC_Read_Sol_IFace_Real_Mul(fid, S, "IFaceIsEdgeReals", iface_is_edge_reals.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_IFace_Real() ier == 0", ier == 0);

		// verify iface
		for (int j = 0; j < jsize - 1; ++j) {
			for (int i = 0; i < isize; ++i) {
				if (j == 0 || j == (jsize - 2) || i == 0 || i == (isize - 1)) {
					sprintf(buffer, "cg_iRIC_Read_Sol_IFace_Integer_Mul() iface_is_edge[%d] == %d", j * isize + i, 1);
					VERIFY_LOG(buffer, iface_is_edge[j * isize + i] == 1);
					sprintf(buffer, "cg_iRIC_Read_Sol_IFace_Integer_Mul() iface_is_edge[%d] == %g", j * isize + i, .1);
					VERIFY_LOG(buffer, iface_is_edge_reals[j * isize + i] == .1);
				}
			}
		}

		// JFaceCenter solutions

		ier = cg_iRIC_Read_Sol_JFace_Integer_Mul(fid, S, "JFaceIsEdge", jface_is_edge.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_JFace_Integer() ier == 0", ier == 0);

		ier = cg_iRIC_Read_Sol_JFace_Real_Mul(fid, S, "JFaceIsEdgeReals", jface_is_edge_reals.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_JFace_Real() ier == 0", ier == 0);

		// verify jface
		for (int j = 0; j < jsize; ++j) {
			for (int i = 0; i < isize - 1; ++i) {
				if (j == 0 || j == (jsize - 1) || i == 0 || i == (isize - 2)) {
					sprintf(buffer, "cg_iRIC_Read_Sol_JFace_Integer_Mul() jface_is_edge[%d] == %d", j * (isize - 1) + i, 2);
					VERIFY_LOG(buffer, jface_is_edge[j * (isize - 1) + i] == 2);
					sprintf(buffer, "cg_iRIC_Read_Sol_IFace_Integer_Mul() jface_is_edge_reals[%d] == %g", j * (isize - 1) + i, .2);
					VERIFY_LOG(buffer, jface_is_edge_reals[j * (isize - 1) + i] == .2);
				}
			}
		}

		// BaseIterativeData

		double d;
		double Dist = (S - 1) * -0.2 + 20;
		ier = cg_iRIC_Read_Sol_BaseIterative_Real_Mul(fid, S, "Discharge", &d);
		VERIFY_LOG("cg_iRIC_Read_Sol_BaseIterative_Real_Mul() for Discharge ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_BaseIterative_Real_Mul() for Discharge d == %g", Dist);
		VERIFY_LOG(buffer, d == Dist);

		int i;
		int DamOpen = (S - 1);
		ier = cg_iRIC_Read_Sol_BaseIterative_Integer_Mul(fid, S, "DamOpen", &i);
		VERIFY_LOG("cg_iRIC_Read_Sol_BaseIterative_Integer_Mul() for DamOpen ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_BaseIterative_Integer_Mul() for DamOpen i == %d", DamOpen);
		VERIFY_LOG(buffer, i == DamOpen);

		std::ostringstream ss;
		ss << "Test" << S - 1;
		std::string validVal = ss.str();
		std::vector<char> retval;
		int len;
		ier = cg_iRIC_Read_Sol_BaseIterative_StringLen_Mul(fid, S, "TestStr", &len);
		VERIFY_LOG("cg_iRIC_Read_Sol_BaseIterative_StringLen_Mul() for TestStr ier == 0", ier == 0);
		retval.assign(len + 1, '\0');
		ier = cg_iRIC_Read_Sol_BaseIterative_String_Mul(fid, S, "TestStr", retval.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_BaseIterative_String_Mul() for TestStr ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_BaseIterative_String_Mul() for TestStr s == %s", validVal.c_str());
		VERIFY_LOG(buffer, validVal == retval.data());
	}
}

void case_SolWriteStd(const std::string& origCgnsName)
{
	iRIC_InitOption(IRIC_OPTION_STDSOLUTION);

	bool hdf = true;

	remove("case_solstd.cgn");

	//
	// Test Writing Standard (IRIC_OPTION_STDSOLUTION) with times
	//

	fs::copy(origCgnsName, "case_solstd.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_solstd.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution("case_solstd.cgn", &fid, false);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	//
	// Test Reading Standard (IRIC_OPTION_STDSOLUTION) with times
	//

	ier = cg_iRIC_Open("case_solstd.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	readSolution(fid);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	VERIFY_REMOVE("case_solstd.cgn", hdf);

	//
	// Test Writing 3D Standard (IRIC_OPTION_STDSOLUTION) with times
	//

	fs::copy(origCgnsName, "case_solstd3d.cgn");

	ier = cg_iRIC_Open("case_solstd3d.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution3d("case_solstd3d.cgn", &fid);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	VERIFY_REMOVE("case_solstd3d.cgn", hdf);

	// @todo add codes to test

	//
	// Test Writing Standard (IRIC_OPTION_STDSOLUTION) with iterations
	//

	fs::copy(origCgnsName, "case_solstditer.cgn");

	ier = cg_iRIC_Open("case_solstditer.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution("case_solstditer.cgn", &fid, true);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	//
	// Test Reading Standard (IRIC_OPTION_STDSOLUTION) with iterations
	//

	ier = cg_iRIC_Open("case_solstditer.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	readSolution(fid);
	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	VERIFY_REMOVE("case_solstditer.cgn", hdf);

	// @todo add codes to test
}

void case_SolWriteDivide(const std::string& origCgnsName)
{
	iRIC_InitOption(IRIC_OPTION_DIVIDESOLUTIONS);

	bool hdf = true;

	remove("case_soldivide.cgn");
	remove("result/Solution1.cgn");
	remove("result/Solution2.cgn");
	remove("result/Solution3.cgn");
	remove("result/Solution4.cgn");
	remove("result/Solution5.cgn");

	//
	// Test Writing Divided Solutions (IRIC_OPTION_DIVIDESOLUTIONS) with times
	//

	fs::copy(origCgnsName, "case_soldivide.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_soldivide.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution("case_soldivide.cgn", &fid, false);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	//
	// Test Reading Divided Solutions (IRIC_OPTION_DIVIDESOLUTIONS) with times
	//

	ier = cg_iRIC_Open("case_soldivide.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	readSolution(fid);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	VERIFY_REMOVE("case_soldivide.cgn", hdf);
	VERIFY_REMOVE("result/Solution1.cgn", hdf);
	VERIFY_REMOVE("result/Solution2.cgn", hdf);
	VERIFY_REMOVE("result/Solution3.cgn", hdf);
	VERIFY_REMOVE("result/Solution4.cgn", hdf);
	VERIFY_REMOVE("result/Solution5.cgn", hdf);

	//
	// Test Writing 3D Divided Solutions (IRIC_OPTION_DIVIDESOLUTIONS) with times
	//

	remove("case_soldivide3d.cgn");
	remove("result/Solution1.cgn");
	remove("result/Solution2.cgn");
	remove("result/Solution3.cgn");
	remove("result/Solution4.cgn");
	remove("result/Solution5.cgn");

	// @todo add codes to test

	fs::copy(origCgnsName, "case_soldivide3d.cgn");

	ier = cg_iRIC_Open("case_soldivide3d.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution3d("case_soldivide3d.cgn", &fid);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	VERIFY_REMOVE("case_soldivide3d.cgn", hdf);
	VERIFY_REMOVE("result/Solution1.cgn", hdf);
	VERIFY_REMOVE("result/Solution2.cgn", hdf);
	VERIFY_REMOVE("result/Solution3.cgn", hdf);
	VERIFY_REMOVE("result/Solution4.cgn", hdf);
	VERIFY_REMOVE("result/Solution5.cgn", hdf);

	// @todo add codes to test

	//
	// Test Writing Divided Solutions (IRIC_OPTION_DIVIDESOLUTIONS) with iterations
	//

	remove("case_soldivideiter.cgn");
	remove("result/Solution1.cgn");
	remove("result/Solution2.cgn");
	remove("result/Solution3.cgn");
	remove("result/Solution4.cgn");
	remove("result/Solution5.cgn");

	fs::copy(origCgnsName, "case_soldivideiter.cgn");

	ier = cg_iRIC_Open("case_soldivideiter.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution("case_soldivideiter.cgn", &fid, true);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	//
	// Test Reading Divided Solutions (IRIC_OPTION_DIVIDESOLUTIONS) with iterations
	//

	ier = cg_iRIC_Open("case_soldivideiter.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	// cg_iRIC_SetFilename(fid, "case_soldivideiter.cgn");

	readSolution(fid);
	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	VERIFY_REMOVE("case_soldivideiter.cgn", hdf);
	VERIFY_REMOVE("result/Solution1.cgn", hdf);
	VERIFY_REMOVE("result/Solution2.cgn", hdf);
	VERIFY_REMOVE("result/Solution3.cgn", hdf);
	VERIFY_REMOVE("result/Solution4.cgn", hdf);
	VERIFY_REMOVE("result/Solution5.cgn", hdf);

	// restore mode.
	iRIC_InitOption(IRIC_OPTION_STDSOLUTION);
}

void case_SolWriteStd_adf()
{
	case_SolWriteStd("case_init.cgn");
}

void case_SolWriteStd_hdf5()
{
	case_SolWriteStd("case_init_hdf5.cgn");
}

void case_SolWriteDivide_adf()
{
	case_SolWriteDivide("case_init.cgn");
}

void case_SolWriteDivide_hdf5()
{
	case_SolWriteDivide("case_init_hdf5.cgn");
}

} // extern "C"
