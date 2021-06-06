import shutil

import iric

from . import util

def case_InitReadSuccess():
    util.remove("data/case_initreadsuccess.cgn")
    shutil.copy('data/case_init_hdf5.cgn', 'data/case_initreadsuccess.cgn')

    fid = iric.cg_iRIC_Open("data/case_initreadsuccess.cgn", iric.IRIC_MODE_MODIFY)
    util.verify_log('cg_iRIC_Open() fid != 0', fid != 0)

    iric.cg_iRIC_InitRead(fid)

    iric.cg_close(fid)

    util.remove("data/case_initreadsuccess.cgn")

def case_InitReadFail():
    fid = 1
    try:
        ier = iric.cg_iRIC_InitRead(fid)
    except Exception:
        print('cg_iRIC_InitRead() raise Exception for wrong fid [OK]')
