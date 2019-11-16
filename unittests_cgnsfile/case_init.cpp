#include "macros.h"

#include "fs_copy.h"

#include <cgnslib.h>
#include <iriclib.h>

#include <iostream>

extern "C" {

void case_InitSuccess()
{
	remove("case_initsuccess.cgn");
	fs::copy("case_init_hdf5.cgn", "case_initsuccess.cgn");

	int fid;
	int ier = cg_open("case_initsuccess.cgn", CG_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier == 0", ier == 0);

	cg_close(fid);

	remove("case_initsuccess.cgn");
}

void case_InitFail()
{
	int fid = 1;

	int ier = cg_iRIC_Init(fid);

	VERIFY_LOG("cg_iRIC_Init() ier != 0", ier != 0);
}

void case_gotoRawDataTop()
{
	remove("case_rawdatatop.cgn");
#if defined(HAVE_QT)
	QFile::copy("case_nogrid.cgn", "case_rawdatatop.cgn");
#else
	fs::copy("case_nogrid_hdf.cgn", "case_rawdatatop.cgn");
#endif

	int fid;
	int ier = cg_open("case_rawdatatop.cgn", CG_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_GotoRawDataTop(fid);

	VERIFY_LOG("cg_iRIC_GotoRawDataTop() ier == 0", ier == 0);

	cg_close(fid);

	remove("case_rawdatatop.cgn");
}

} // extern "C"
