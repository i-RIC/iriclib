import shutil

import iric

from . import util

def case_InitSuccess():
	util.remove("data/case_initsuccess.cgn")
	shutil.copy('data/case_init_hdf5.cgn', 'data/case_initsuccess.cgn')

	fid = iric.cg_iRIC_Open("data/case_initsuccess.cgn", iric.IRIC_MODE_MODIFY)

	util.verify_log('cg_iRIC_Open() fid != 0', fid != 0)

	iric.cg_iRIC_Close(fid)

	util.remove("data/case_initsuccess.cgn")
