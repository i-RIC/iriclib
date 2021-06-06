#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

extern "C" {

void case_noGridOutput()
{
	fs::copy("case_nogrid_hdf5.cgn", "case_nogrid_output.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_nogrid_output.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	double time = 0.0;
	double discharge = 0.1;

	ier = cg_iRIC_Write_Sol_Time(time);
	VERIFY_LOG("cg_iRIC_Write_Sol_Time() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Sol_BaseIterative_Real("Discharge", discharge);
	VERIFY_LOG("cg_iRIC_Write_Sol_BaseIterative_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);

	remove("case_nogrid_output.cgn");
}

} // extern "C"
