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

void case_addGridAndResult()
{
	fs::copy("case_nogrid.cgn", "case_grid_result.cgn");

	int fid;
	int ier = cg_open("case_grid_result.cgn", CG_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	// This CGNS file contains no grid, so the returned value is 1.
	VERIFY_LOG("cg_iRIC_Init() ier == 1", ier == 1);

	cgsize_t isize, jsize;
	std::vector<double> x, y;

	isize = 10; jsize = 10;
	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);

	for (int j = 0; j < jsize; ++j) {
		for (int i = 0; i < isize; ++i) {
			x[i + isize * j] = i;
			y[i + isize * j] = j;
		}
	}
	ier = cg_iRIC_WriteGridCoord2d_Mul(fid, isize, jsize, x.data(), y.data());
	VERIFY_LOG("cg_iRIC_WriteGridCoord2d_Mul() ier == 0", ier == 0);

	double time = 1.0;
	std::vector<double> depth;
	depth.assign(isize * jsize, 4);
	std::vector<double> ccdepth;
	ccdepth.assign((isize-1) * (jsize-1), 4.1);
	std::vector<int> active;
	active.assign(isize * jsize, 1);
	std::vector<int> ccactive;
	ccactive.assign((isize - 1) * (jsize - 1), 1);

	ier = cg_iRIC_Write_Sol_Time(time);
	VERIFY_LOG("cg_iRIC_Write_Sol_Time() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_GridCoord2d(x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_GridCoord2d() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Real("Depth", depth.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Integer("Active", active.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Integer() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Cell_Real("CCDepth", ccdepth.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Cell_Integer("CCActive", ccactive.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Integer() ier == 0", ier == 0);

	time = 2.0;
	depth.assign(isize * jsize, 8);
	ccdepth.assign((isize - 1) * (jsize - 1), 8.1);
	active.assign(isize * jsize, 0);
	ccactive.assign((isize - 1) * (jsize - 1), 0);
	ier = cg_iRIC_Write_Sol_Time(time);
	VERIFY_LOG("cg_iRIC_Write_Sol_Time() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_GridCoord2d(x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_GridCoord2d() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Real("Depth", depth.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Integer("Active", active.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Integer() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Cell_Real("CCDepth", ccdepth.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Cell_Integer("CCActive", ccactive.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Integer() ier == 0", ier == 0);

	ier = cg_close(fid);
	VERIFY_LOG("cg_close() ier == 0", ier == 0);

	remove("case_grid_result.cgn");
}

} // extern "C"
