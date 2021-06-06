import shutil
import numpy as np

import iric

from . import util

def case_Complex():
    shutil.copy('data/case_init_hdf5.cgn', 'data/case_complex.cgn')
    fid = iric.cg_open("data/case_complex.cgn", iric.CG_MODE_MODIFY)
    util.verify_log("cg_open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    iric.cg_iRIC_Clear_Complex()

    intparam_write = 71
    iric.cg_iRIC_Write_Complex_Integer("cellparam", 1, "intparam", intparam_write)

    intparam2_write = 48
    iric.cg_iRIC_Write_Complex_Integer("cellparam", 2, "intparam", intparam2_write)

    realparam_write = 1.23
    iric.cg_iRIC_Write_Complex_Real("cellparam", 1, "realparam", realparam_write)

    realparam2_write = 8.92
    iric.cg_iRIC_Write_Complex_Real("cellparam", 2, "realparam", realparam2_write)

    isize, jsize = iric.cg_iRIC_Read_Grid2d_Str_Size()

    complex_cell = np.zeros((isize - 1) * (jsize - 1))
    complex_cell[:] = 1
    i = 3
    while i < complex_cell.size:
        complex_cell[i] = 2
        i += 4

    iric.cg_iRIC_Write_Grid_Complex_Cell("cellparam", complex_cell)

    strparam_write = "iriclib1"
    iric.cg_iRIC_Write_Complex_String("nodeparam", 1, "strparam", strparam_write)

    strparam2_write = "cgnslib2"
    iric.cg_iRIC_Write_Complex_String("nodeparam", 2, "strparam", strparam2_write)
 
    params_write = np.zeros(5, dtype=np.float64)
    vals_write = np.zeros(5, dtype=np.float64)

    for i in range(5):
        params_write[i] = 2.3 * i + 1.2
        vals_write[i] = 5.1 * i + 0.8

    iric.cg_iRIC_Write_Complex_Functional("nodeparam", 1, "funcparam", params_write, vals_write)

    iric.cg_iRIC_Write_Complex_FunctionalWithName("nodeparam", 2, "funcparam", "Time", params_write)
    iric.cg_iRIC_Write_Complex_FunctionalWithName("nodeparam", 2, "funcparam", "Elevation", vals_write)

    iric.cg_iRIC_Write_Complex_FunctionalWithName("nodeparam", 3, "funcparam", "Time", params_write)
    iric.cg_iRIC_Write_Complex_FunctionalWithName("nodeparam", 3, "funcparam", "Elevation", vals_write)

    iric.cg_iRIC_Write_Complex_FunctionalWithName_String("nodeparam", 3, "funcparam", "_siteID", "01646500")
    iric.cg_iRIC_Write_Complex_FunctionalWithName_String("nodeparam", 3, "funcparam", "_startDate", "2017-06-01T06:00")
    iric.cg_iRIC_Write_Complex_FunctionalWithName_String("nodeparam", 3, "funcparam", "_endDate", "2017-06-01T10:00")

    complex_node = np.zeros(isize * jsize, dtype=np.int64)
    complex_node[:] = 1
    i = 3
    while i < complex_node.size:
        complex_node[i] = 2
        i += 5

    iric.cg_iRIC_Write_Grid_Complex_Node("nodeparam", complex_node)

    iric.cg_close(fid)

    fid = iric.cg_open("data/case_complex.cgn", iric.CG_MODE_MODIFY)
    util.verify_log("cg_open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    cellnum = iric.cg_iRIC_Read_Complex_Count("cellparam")
    util.verify_log("cg_iRIC_Read_Complex_Count() cellnum == 2", cellnum == 2)

    try:
        cellnum = iric.cg_iRIC_Read_Complex_Count("dummy_param")
        print('cg_iRIC_Read_Complex_Count() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_Complex_Count() raise Exception for invalid name [OK]')

    intparam_read = iric.cg_iRIC_Read_Complex_Integer("cellparam", 1, "intparam")
    util.verify_log("cg_iRIC_Read_Complex_Integer() value valid", intparam_read == intparam_write)

    realparam_read = iric.cg_iRIC_Read_Complex_Real("cellparam", 1, "realparam")
    util.verify_log("cg_iRIC_Read_Complex_Real() value valid", realparam_read == realparam_write)

    complex_cell_read = iric.cg_iRIC_Read_Grid_Complex_Cell("cellparam")
    util.verify_log("cg_iRIC_Read_Grid_Complex_Cell() value valid", np.array_equal(complex_cell, complex_cell_read))

    strparam_read = iric.cg_iRIC_Read_Complex_String("nodeparam", 1, "strparam")
    util.verify_log("cg_iRIC_Read_Complex_String() string valid", strparam_read == strparam_write)

    params_read, vals_read = iric.cg_iRIC_Read_Complex_Functional("nodeparam", 1, "funcparam")
    util.verify_log("cg_iRIC_Read_Complex_Functional() params valid", np.array_equal(params_read, params_write))
    util.verify_log("cg_iRIC_Read_Complex_Functional() vals valid", np.array_equal(vals_read, vals_write))

    times_read = iric.cg_iRIC_Read_Complex_FunctionalWithName("nodeparam", 2, "funcparam", "Time")
    util.verify_log("cg_iRIC_Read_Complex_FunctionalWithName() Time valid", np.array_equal(times_read,params_write))

    elevs_read = iric.cg_iRIC_Read_Complex_FunctionalWithName("nodeparam", 2, "funcparam", "Elevation")
    util.verify_log("cg_iRIC_Read_Complex_FunctionalWithName() Elevation valid", np.array_equal(elevs_read, vals_write))

    read_str = iric.cg_iRIC_Read_Complex_FunctionalWithName_String("nodeparam", 3, "funcparam", "_siteID")
    util.verify_log("cg_iRIC_Read_Complex_FunctionalWithName_String() value match", read_str == "01646500")

    read_str = iric.cg_iRIC_Read_Complex_FunctionalWithName_String("nodeparam", 3, "funcparam", "_startDate")
    util.verify_log("cg_iRIC_Read_Complex_FunctionalWithName_String() value match", read_str == "2017-06-01T06:00")

    read_str = iric.cg_iRIC_Read_Complex_FunctionalWithName_String("nodeparam", 3, "funcparam", "_endDate")
    util.verify_log("cg_iRIC_Read_Complex_FunctionalWithName_String() value match", read_str == "2017-06-01T10:00")

    iric.cg_close(fid)

    util.remove('data/case_complex.cgn')
