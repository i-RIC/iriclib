#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>

#include <iostream>

extern "C" {

void case_InitSuccess()
{
	remove("case_initsuccess.cgn");
	fs::copy("case_init_hdf5.cgn", "case_initsuccess.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_initsuccess.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	cg_iRIC_Close(fid);

	remove("case_initsuccess.cgn");
}

} // extern "C"
