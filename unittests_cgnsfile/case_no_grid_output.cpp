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

void case_noGridOutput()
{
	fs::copy("case_nogrid.cgn", "case_nogrid_output.cgn");

	int fid;
	int ier = cg_open("case_nogrid_output.cgn", CG_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	double time = 0.0;
	double discharge = 0.1;

	ier = cg_iRIC_Write_Sol_Time(time);
	VERIFY_LOG("cg_iRIC_Write_Sol_Time() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_BaseIterative_Real("Discharge", discharge);
	VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Real() ier == 0", ier == 0);

	ier = cg_close(fid);
	VERIFY_LOG("cg_close() ier == 0", ier == 0);

	remove("case_nogrid_output.cgn");
}

} // extern "C"
