import iric

from . import util

def case_CheckCancel():
    canceled = iric.iRIC_Check_Cancel()
    util.verify_log("iRIC_Check_Cancel() checked .cancel, and it did not exist.", canceled == 0)
