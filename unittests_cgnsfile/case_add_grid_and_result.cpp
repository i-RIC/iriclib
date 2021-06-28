#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

extern "C" {

void case_addGridAndResult()
{
	fs::copy("case_nogrid_hdf5.cgn", "case_grid_result.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_grid_result.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	int isize, jsize;
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
	ier = cg_iRIC_Write_Grid2d_Coords(fid, isize, jsize, x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Write_Grid2d_Coords() ier == 0", ier == 0);

	double time = 1.0;
	std::vector<double> depth;
	depth.assign(isize * jsize, 4);
	std::vector<double> ccdepth;
	ccdepth.assign((isize-1) * (jsize-1), 4.1);
	std::vector<int> active;
	active.assign(isize * jsize, 1);
	std::vector<int> ccactive;
	ccactive.assign((isize - 1) * (jsize - 1), 1);

	ier = cg_iRIC_Write_Sol_Time(fid, time);
	VERIFY_LOG("cg_iRIC_Write_Sol_Time() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Grid2d_Coords(fid, x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Grid2d_Coords() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Node_Real(fid, "Depth", depth.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Node_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Node_Integer(fid, "Active", active.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Node_Integer() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Cell_Real(fid, "CCDepth", ccdepth.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Cell_Integer(fid, "CCActive", ccactive.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Integer() ier == 0", ier == 0);

	time = 2.0;
	depth.assign(isize * jsize, 8);
	ccdepth.assign((isize - 1) * (jsize - 1), 8.1);
	active.assign(isize * jsize, 0);
	ccactive.assign((isize - 1) * (jsize - 1), 0);
	ier = cg_iRIC_Write_Sol_Time(fid, time);
	VERIFY_LOG("cg_iRIC_Write_Sol_Time() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Grid2d_Coords(fid, x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Grid2d_Coords() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Node_Real(fid, "Depth", depth.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Node_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Node_Integer(fid, "Active", active.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Node_Integer() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Cell_Real(fid, "CCDepth", ccdepth.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_Cell_Integer(fid, "CCActive", ccactive.data());
	VERIFY_LOG("cg_iRIC_Write_Sol_Cell_Integer() ier == 0", ier == 0);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	remove("case_grid_result.cgn");
}

} // extern "C"
