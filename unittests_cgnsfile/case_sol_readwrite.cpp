#include "macros.h"

#include "fs_copy.h"

#include <cgnslib.h>
#include <iriclib.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

extern "C" {

void writeSolution(char* filename, int fid, bool iterMode)
{
	cgsize_t isize, jsize;

	int ier = cg_iRIC_GotoGridCoord2d_Mul(fid, &isize, &jsize);
	VERIFY_LOG("cg_iRIC_GotoGridCoord2d_Mul() ier == 0", ier == 0);

	std::vector<double> x, y;
	std::vector<double> vx, vy, depth;
	std::vector<int> wet;
	std::vector<double> ccdepth;
	std::vector<int> ccwet;

	std::vector<double> particle_x, particle_y;
	std::vector<double> particle_vx, particle_vy;
	std::vector<int> particle_active;

	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);
	ier = cg_iRIC_GetGridCoord2d_Mul(fid, x.data(), y.data());

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
			ier = cg_iRIC_Write_Sol_Iteration_Mul(fid, IterVal);
			VERIFY_LOG("cg_iRIC_Write_Sol_Iteration_Mul() ier == 0", ier == 0);
		} else {
			double TimeVal = i * 2.13;
			ier = cg_iRIC_Write_Sol_Time_Mul(fid, TimeVal);
			VERIFY_LOG("cg_iRIC_Write_Sol_Time_Mul() ier == 0", ier == 0);
		}

		cg_iRIC_Write_Sol_GridCoord2d_Mul(fid, x.data(), y.data());

		// Vertex solutions

		depth.assign(isize * jsize, (double)i);
		cg_iRIC_Write_Sol_Real_Mul(fid, const_cast<char*>("Depth"), depth.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Real_Mul() for Depth ier == 0", ier == 0);

		cg_iRIC_Write_Sol_Real_Mul(fid, const_cast<char*>("VelocityX"), vx.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Real_Mul() for VelocityX ier == 0", ier == 0);

		cg_iRIC_Write_Sol_Real_Mul(fid, const_cast<char*>("VelocityY"), vy.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Real_Mul() for VelocityY ier == 0", ier == 0);

		wet.assign(isize * jsize, i);
		cg_iRIC_Write_Sol_Integer_Mul(fid, const_cast<char*>("IBC"), wet.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Integer_Mul() for IBC ier == 0", ier == 0);

		// CellCenter solutions

		ccdepth.assign((isize - 1) * (jsize - 1), 0.2 + i);
		ier = cg_iRIC_Write_Sol_Cell_Real(const_cast<char*>("CCDepth"), ccdepth.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Real() ier == 0", ier == 0);

		ccwet.assign((isize - 1) * (jsize - 1), i + 1);
		ier = cg_iRIC_Write_Sol_Cell_Integer(const_cast<char*>("CCWet"), ccwet.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Integer() ier == 0", ier == 0);

		// BaseIterativeData

		double Dist = i * - 0.2 + 20;
		cg_iRIC_Write_Sol_BaseIterative_Real_Mul(fid, const_cast<char*>("Discharge"), Dist);
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Real_Mul() for Discharge ier == 0", ier == 0);
		int DamOpen = i;
		cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(fid, const_cast<char*>("DamOpen"), DamOpen);
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Integer_Mul() for DamOpen ier == 0", ier == 0);

		// Particle solutions

		ier = cg_iRIC_Write_Sol_Particle_Pos2d_Mul(fid, particle_num, particle_x.data(), particle_y.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Pos2d_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(fid, const_cast<char*>("VelX"), particle_vx.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelX ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(fid, const_cast<char*>("VelY"), particle_vy.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelY ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Integer_Mul(fid, const_cast<char*>("Active"), particle_active.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Integer_Mul() for Active ier == 0", ier == 0);

		ier = cg_iRIC_Flush(filename, &fid);
		VERIFY_LOG("cg_iRIC_Flush() ier == 0", ier == 0);
	}
}

void writeSolution3d(char* filename, int fid)
{
	cgsize_t isize, jsize;

	int ier = cg_iRIC_GotoGridCoord2d_Mul(fid, &isize, &jsize);
	VERIFY_LOG("cg_iRIC_GotoGridCoord2d_Mul() ier == 0", ier == 0);

	std::vector<double> x, y, z;
	std::vector<double> vx, vy, depth;
	std::vector<int> wet;

	std::vector<double> particle_x, particle_y, particle_z;
	std::vector<double> particle_vx, particle_vy, particle_vz;
	std::vector<int> particle_active;

	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);
	z.assign(isize * jsize, 0);
	ier = cg_iRIC_GetGridCoord2d_Mul(fid, x.data(), y.data());

	ier = cg_iRIC_WriteGridCoord3d_Mul(fid, isize, jsize, 1, x.data(), y.data(), z.data());
	VERIFY_LOG("cg_iRIC_WriteGridCoord3d_Mul() ier == 0", ier == 0);

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
		ier = cg_iRIC_Write_Sol_Time_Mul(fid, TimeVal);
		VERIFY_LOG("cg_iRIC_Write_Sol_Time_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_GridCoord3d_Mul(fid, x.data(), y.data(), z.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_GridCoord3d_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Real_Mul(fid, const_cast<char*>("Depth"), depth.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Real_Mul() for Depth ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Real_Mul(fid, const_cast<char*>("VelocityX"), vx.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Real_Mul() for VelocityX ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Real_Mul(fid, const_cast<char*>("VelocityY"), vy.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Real_Mul() for VelocityY ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Integer_Mul(fid, const_cast<char*>("IBC"), wet.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Integer_Mul() for IBC ier == 0", ier == 0);

		double Dist = i * - 0.2 + 20;
		ier = cg_iRIC_Write_Sol_BaseIterative_Real_Mul(fid, const_cast<char*>("Discharge"), Dist);
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Real_Mul() for Discharge ier == 0", ier == 0);
		int DamOpen = i;
		ier = cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(fid, const_cast<char*>("DamOpen"), DamOpen);
		VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Integer_Mul() for DamOpen ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Pos3d_Mul(fid, particle_num, particle_x.data(), particle_y.data(), particle_z.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Pos2d_Mul() ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(fid, const_cast<char*>("VelX"), particle_vx.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelX ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(fid, const_cast<char*>("VelY"), particle_vy.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelY ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Real_Mul(fid, const_cast<char*>("VelZ"), particle_vz.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Real_Mul() for VelZ ier == 0", ier == 0);

		ier = cg_iRIC_Write_Sol_Particle_Integer_Mul(fid, const_cast<char*>("Active"), particle_active.data());
		VERIFY_LOG("cg_iRIC_Write_Sol_Particle_Integer_Mul() for Active ier == 0", ier == 0);

		ier = cg_iRIC_Flush(filename, &fid);
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

	double t;
	cgsize_t isize, jsize;

	std::vector<double> grid_x, grid_y;
	std::vector<double> real_sol;
	std::vector<int> int_sol;
	std::vector<double> real_ccsol;
	std::vector<int> int_ccsol;

	ier = cg_iRIC_GotoGridCoord2d_Mul(fid, &isize, &jsize);
	VERIFY_LOG("cg_iRIC_GotoGridCoord2d_Mul() ier == 0", ier == 0);

	grid_x.assign(isize * jsize, 0);
	grid_y.assign(isize * jsize, 0);
	real_sol.assign(isize * jsize, 0);
	int_sol.assign(isize * jsize, 0);
	real_ccsol.assign((isize - 1) * (jsize - 1), 0);
	int_ccsol.assign((isize - 1) * (jsize - 1), 0);

	for (int S = 1; S <= sol_count; ++S) {

		// GridCoord

		ier = cg_iRIC_Read_Sol_GridCoord2d_Mul(fid, S, grid_x.data(), grid_y.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_GridCoord2d_Mul() ier == 0", ier == 0);

		// Vertex solutions

		ier = cg_iRIC_Read_Sol_Real_Mul(fid, S, const_cast<char*>("Depth"), real_sol.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Real_Mul() ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_Real_Mul() real_sol[0] == %g", (double)(S - 1));
		VERIFY_LOG(buffer, real_sol[0] == (double)(S - 1));
		sprintf(buffer, "cg_iRIC_Read_Sol_Real_Mul() real_sol[%lu] == %g", real_sol.size() - 1, (double)(S - 1));
		VERIFY_LOG(buffer, real_sol[real_sol.size()-1] == (double)(S - 1));

		ier = cg_iRIC_Read_Sol_Integer_Mul(fid, S, const_cast<char*>("IBC"), int_sol.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Integer_Mul() ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_Integer_Mul() int_sol[0] == %d", (S - 1));
		VERIFY_LOG(buffer, int_sol[0] == (S - 1));
		sprintf(buffer, "cg_iRIC_Read_Sol_Integer_Mul() int_sol[%lu] == %d", int_sol.size() - 1, (S - 1));
		VERIFY_LOG(buffer, int_sol[int_sol.size() - 1] == (S - 1));

		// CellCenter solutions

		ier = cg_iRIC_Read_Sol_Cell_Real_Mul(fid, S, const_cast<char*>("CCDepth"), real_ccsol.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Cell_Real_Mul() ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_Cell_Real_Mul() real_ccsol[0] == %g", 0.2 + (S - 1));
		VERIFY_LOG(buffer, real_ccsol[0] == 0.2 + (S - 1));
		sprintf(buffer, "cg_iRIC_Read_Sol_Cell_Real_Mul() real_ccsol[%lu] == %g", real_ccsol.size() - 1, 0.2 + (S - 1));
		VERIFY_LOG(buffer, real_ccsol[real_ccsol.size() - 1] == 0.2 + (S - 1));

		ier = cg_iRIC_Read_Sol_Cell_Integer_Mul(fid, S, const_cast<char*>("CCWet"), int_ccsol.data());
		VERIFY_LOG("cg_iRIC_Read_Sol_Cell_Integer_Mul() ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_Cell_Integer_Mul() int_ccsol[0] == %d", S);
		VERIFY_LOG(buffer, int_ccsol[0] == S);
		sprintf(buffer, "cg_iRIC_Read_Sol_Cell_Integer_Mul() int_ccsol[%lu] == %d", int_ccsol.size() - 1, S);
		VERIFY_LOG(buffer, int_ccsol[int_ccsol.size() - 1] == S);

		// BaseIterativeData

		double d;
		double Dist = (S - 1) * -0.2 + 20;
		ier = cg_iRIC_Read_Sol_BaseIterative_Real_Mul(fid, S, const_cast<char*>("Discharge"), &d);
		VERIFY_LOG("cg_iRIC_Read_Sol_BaseIterative_Real_Mul() for Discharge ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_BaseIterative_Real_Mul() for Discharge d == %g", Dist);
		VERIFY_LOG(buffer, d == Dist);

		int i;
		int DamOpen = (S - 1);
		ier = cg_iRIC_Read_Sol_BaseIterative_Integer_Mul(fid, S, const_cast<char*>("DamOpen"), &i);
		VERIFY_LOG("cg_iRIC_Read_Sol_BaseIterative_Integer_Mul() for DamOpen ier == 0", ier == 0);
		sprintf(buffer, "cg_iRIC_Read_Sol_BaseIterative_Integer_Mul() for DamOpen i == %d", DamOpen);
		VERIFY_LOG(buffer, i == DamOpen);
	}
}

void case_SolWriteStd()
{
	iRIC_InitOption(IRIC_OPTION_STDSOLUTION);

	fs::copy("case_init.cgn", "case_solstd.cgn");

	int fid;
	int ier = cg_open("case_solstd.cgn", CG_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);
	cg_iRIC_SetFilename(fid, const_cast<char*>("case_solstd.cgn"));

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution(const_cast<char*>("case_solstd.cgn"), fid, false);

	cg_close(fid);

	ier = cg_open("case_solstd.cgn", CG_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	cg_iRIC_SetFilename(fid, const_cast<char*>("case_solstd.cgn"));

	readSolution(fid);

	cg_close(fid);

	remove("case_solstd.cgn");

	// @todo add codes to test

	fs::copy("case_init.cgn", "case_solstd3d.cgn");

	ier = cg_open("case_solstd3d.cgn", CG_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);
	cg_iRIC_SetFilename(fid, const_cast<char*>("case_solstd3d.cgn"));

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution3d(const_cast<char*>("case_solstd3d.cgn"), fid);

	cg_close(fid);

	remove("case_solstd3d.cgn");

	// @todo add codes to test

	fs::copy("case_init.cgn", "case_solstditer.cgn");

	ier = cg_open("case_solstditer.cgn", CG_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);
	cg_iRIC_SetFilename(fid, const_cast<char*>("case_solstditer.cgn"));

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution(const_cast<char*>("case_solstditer.cgn"), fid, true);

	cg_close(fid);

	remove("case_solstditer.cgn");

	// @todo add codes to test
}

void case_SolWriteDivide()
{
	iRIC_InitOption(IRIC_OPTION_DIVIDESOLUTIONS);

	remove("case_soldivide.cgn");
	remove("case_soldivide_Solution1.cgn");
	remove("case_soldivide_Solution2.cgn");
	remove("case_soldivide_Solution3.cgn");
	remove("case_soldivide_Solution4.cgn");
	remove("case_soldivide_Solution5.cgn");

	fs::copy("case_init.cgn", "case_soldivide.cgn");

	int fid;
	int ier = cg_open("case_soldivide.cgn", CG_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);
	cg_iRIC_SetFilename(fid, const_cast<char*>("case_soldivide.cgn"));

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution(const_cast<char*>("case_soldivide.cgn"), fid, false);

	cg_close(fid);

	ier = cg_open("case_soldivide.cgn", CG_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	cg_iRIC_SetFilename(fid, const_cast<char*>("case_soldivide.cgn"));

	readSolution(fid);

	cg_close(fid);

	remove("case_soldivide.cgn");
	remove("case_soldivide_Solution1.cgn");
	remove("case_soldivide_Solution2.cgn");
	remove("case_soldivide_Solution3.cgn");
	remove("case_soldivide_Solution4.cgn");
	remove("case_soldivide_Solution5.cgn");

	remove("case_soldivide3d.cgn");
	remove("case_soldivide3d_Solution1.cgn");
	remove("case_soldivide3d_Solution2.cgn");
	remove("case_soldivide3d_Solution3.cgn");
	remove("case_soldivide3d_Solution4.cgn");
	remove("case_soldivide3d_Solution5.cgn");

	// @todo add codes to test

	fs::copy("case_init.cgn", "case_soldivide3d.cgn");

	ier = cg_open("case_soldivide3d.cgn", CG_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);
	cg_iRIC_SetFilename(fid, const_cast<char*>("case_soldivide3d.cgn"));

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	writeSolution3d(const_cast<char*>("case_soldivide3d.cgn"), fid);

	cg_close(fid);

	remove("case_soldivide3d.cgn");
	remove("case_soldivide3d_Solution1.cgn");
	remove("case_soldivide3d_Solution2.cgn");
	remove("case_soldivide3d_Solution3.cgn");
	remove("case_soldivide3d_Solution4.cgn");
	remove("case_soldivide3d_Solution5.cgn");

	// @todo add codes to test

	// restore mode.
	iRIC_InitOption(IRIC_OPTION_STDSOLUTION);
}

} // extern "C"
