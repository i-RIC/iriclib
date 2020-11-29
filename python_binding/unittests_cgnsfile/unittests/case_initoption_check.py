import os

import iric

from . import util

def case_InitOptionCheck():
    util.remove('.cancel_ok')

    iric.iRIC_InitOption(iric.IRIC_OPTION_CANCEL)

    util.verify_log('iRIC_InitOption(IRIC_OPTION_CANCEL) created .cancel_ok', os.path.exists('.cancel_ok'))

    util.remove('.cancel_ok')
