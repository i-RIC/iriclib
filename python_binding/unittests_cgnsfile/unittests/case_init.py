import shutil

import iric

from . import util

def case_InitSuccess():
	util.remove("data/case_initsuccess.cgn")
	shutil.copy('data/case_init_hdf5.cgn', 'data/case_initsuccess.cgn')

	fid = iric.cg_open("data/case_initsuccess.cgn", iric.CG_MODE_MODIFY)

	util.verify_log('cg_open() fid != 0', fid != 0)

	iric.cg_iRIC_Init(fid)

	iric.cg_close(fid)

	util.remove("data/case_initsuccess.cgn")

def case_InitFail():
	fid = 1
	try:
		iric.cg_iRIC_Init(fid)
	except Exception:
		print('cg_iRIC_Init() raise exception for wrong fid [OK]')
