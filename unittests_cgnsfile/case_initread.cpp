#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>

#include <iostream>

extern "C" {

void case_InitReadSuccess()
{
	remove("case_initreadsuccess.cgn");
	fs::copy("case_initread_hdf.cgn", "case_initreadsuccess.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_initreadsuccess.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	cg_iRIC_Close(fid);

	remove("case_initreadsuccess.cgn");
}

} // extern "C"
