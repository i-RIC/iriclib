#include "macros.h"

#if defined(HAVE_QT)
#include <QFile>
#else
#include <fstream>
#endif

#include <cgnslib.h>
#include <iriclib.h>

#include <iostream>

extern "C" {

void case_InitReadSuccess()
{
	remove("case_initreadsuccess.cgn");
#if defined(HAVE_QT)
	QFile::copy("case_init.cgn", "case_initreadsuccess.cgn");
#else
        {
          std::ifstream ifs("case_init.cgn", std::ios_base::binary);
          std::ofstream ofs("case_initreadsuccess.cgn", std::ios_base::binary|std::ios_base::trunc);
          ofs << ifs.rdbuf();
        }
#endif

	int fid;
	int ier = cg_open("case_initreadsuccess.cgn", CG_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_open() ier == 0", ier == 0);
	VERIFY_LOG("cg_open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);

	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	cg_close(fid);

	remove("case_initreadsuccess.cgn");
}

void case_InitReadFail()
{
	int fid = 1;

	int ier = cg_iRIC_InitRead(fid);

	VERIFY_LOG("cg_iRIC_InitRead() ier != 0", ier != 0);
}

} // extern "C"
