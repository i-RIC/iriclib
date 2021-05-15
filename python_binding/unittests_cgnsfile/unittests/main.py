from . import case_bc
from . import case_bc_nomul
from . import case_calccond
from . import case_calccond_nomul
from . import case_check
from . import case_complex
from . import case_complex_nomul
from . import case_grid
from . import case_grid_nomul
from . import case_init
from . import case_initread
from . import case_initoption_check
from . import case_sol_readwrite
from . import case_sol_readwrite_nomul

def main():
    print('case_init.case_InitSuccess()')
    case_init.case_InitSuccess()
    print('case_init.case_InitFail()')
    case_init.case_InitFail()

    print('case_initread.case_InitReadSuccess()')
    case_initread.case_InitReadSuccess()
    print('case_initread.case_InitReadFail()')
    case_initread.case_InitReadFail()

    print('case_initoption_check.case_InitOptionCheck()')
    case_initoption_check.case_InitOptionCheck()

    # case_initcc.case_InitCC()

    print('case_check.case_CheckCancel()')
    case_check.case_CheckCancel()

    print('case_calccond.case_CalcCondRead()')
    case_calccond.case_CalcCondRead()
    print('case_calccond.case_CalcCondWrite()')
    case_calccond.case_CalcCondWrite()
    print('case_calccond_nomul.case_CalcCondRead()')
    case_calccond_nomul.case_CalcCondRead()
    print('case_calccond_nomul.case_CalcCondWrite()')
    case_calccond_nomul.case_CalcCondWrite()

    print('case_bc.case_BcRead()')
    case_bc.case_BcRead()
    print('case_bc.case_BcWrite()')
    case_bc.case_BcWrite()
    print('case_bc_nomul.case_BcRead()')
    case_bc_nomul.case_BcRead()
    print('case_bc_nomul.case_BcWrite()')
    case_bc_nomul.case_BcWrite()

    print('case_complex.case_Complex()')
    case_complex.case_Complex()
    print('case_complex_nomul.case_Complex()')
    case_complex_nomul.case_Complex()

    print('case_grid.case_GridRead()')
    case_grid.case_GridRead()
    print('case_grid.case_GridReadUnstructured()')
    case_grid.case_GridReadUnstructured()
    print('case_grid.case_GridReadFunc()')
    case_grid.case_GridReadFunc()
    print('case_grid.case_GridWrite()')
    case_grid.case_GridWrite()
    print('case_grid_nomul.case_GridRead()')
    case_grid_nomul.case_GridRead()
    print('case_grid_nomul.case_GridReadUnstructured()')
    case_grid_nomul.case_GridReadUnstructured()
    print('case_grid_nomul.case_GridReadFunc()')
    case_grid_nomul.case_GridReadFunc()
    print('case_grid_nomul.case_GridWrite()')
    case_grid_nomul.case_GridWrite()

    # print('case_sol_readwrite.case_SolWriteStd_adf()')
    # case_sol_readwrite.case_SolWriteStd_adf()
    print('case_sol_readwrite.case_SolWriteStd_hdf5()')
    case_sol_readwrite.case_SolWriteStd_hdf5()
    # print('case_sol_readwrite_nomul.case_SolWriteStd_adf()')
    # case_sol_readwrite_nomul.case_SolWriteStd_adf()
    print('case_sol_readwrite_nomul.case_SolWriteStd_hdf5()')
    case_sol_readwrite_nomul.case_SolWriteStd_hdf5()
