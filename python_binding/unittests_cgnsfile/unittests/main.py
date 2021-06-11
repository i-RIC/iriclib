from . import case_bc
from . import case_calccond
from . import case_check
from . import case_complex
from . import case_grid
from . import case_init
from . import case_initread
from . import case_initoption_check
from . import case_sol_readwrite

def main():
    print('case_init.case_InitSuccess()')
    case_init.case_InitSuccess()

    print('case_initread.case_InitReadSuccess()')
    case_initread.case_InitReadSuccess()

    print('case_initoption_check.case_InitOptionCheck()')
    case_initoption_check.case_InitOptionCheck()

    # case_initcc.case_InitCC()

    print('case_check.case_CheckCancel()')
    case_check.case_CheckCancel()

    print('case_calccond.case_CalcCondRead()')
    case_calccond.case_CalcCondRead()
    print('case_calccond.case_CalcCondWrite()')
    case_calccond.case_CalcCondWrite()

    print('case_bc.case_BcRead()')
    case_bc.case_BcRead()
    print('case_bc.case_BcWrite()')
    case_bc.case_BcWrite()

    print('case_complex.case_Complex()')
    case_complex.case_Complex()

    print('case_grid.case_GridRead()')
    case_grid.case_GridRead()
    print('case_grid.case_GridReadUnstructured()')
    case_grid.case_GridReadUnstructured()
    print('case_grid.case_GridReadFunc()')
    case_grid.case_GridReadFunc()
    print('case_grid.case_GridWrite()')
    case_grid.case_GridWrite()

    # print('case_sol_readwrite.case_SolWriteStd_adf()')
    # case_sol_readwrite.case_SolWriteStd_adf()
    print('case_sol_readwrite.case_SolWriteStd_hdf5()')
    case_sol_readwrite.case_SolWriteStd_hdf5()
