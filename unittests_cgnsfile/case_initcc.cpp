#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>

#include <iostream>

extern "C" {

void case_InitCC()
{
	remove("case_initcc.cgn");
	fs::copy("case_nogrid_hdf5.cgn", "case_initcc.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_initcc.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_GotoCC(fid);

	VERIFY_LOG("cg_iRIC_GotoCC() ier == 0", ier == 0);

	cg_iRIC_Close(fid);

	remove("case_initcc.cgn");
}

} // extern "C"
