import shutil
import numpy as np

import iric

from . import util

def case_BcRead():
    util.remove('data/case_bc.cgn')
    shutil.copy('data/case_init_hdf5.cgn', 'data/case_bc.cgn')

    fid = iric.cg_open("data/case_bc.cgn", iric.CG_MODE_MODIFY)
    util.verify_log("cg_open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    bc_count = iric.cg_iRIC_Read_BC_Count("bctest")
    util.verify_log("cg_iRIC_Read_BC_Count() bc_count == 2", bc_count == 2)

    indices = iric.cg_iRIC_Read_BC_Indices("bctest", 1)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[0] == 1", indices[0] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[1] == 1", indices[1] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[2] == 1", indices[2] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[3] == 2", indices[3] == 2)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[4] == 1", indices[4] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[5] == 3", indices[5] == 3)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[6] == 1", indices[6] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[7] == 4", indices[7] == 4)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[8] == 1", indices[8] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices() indices[9] == 5", indices[9] == 5)

    cond_int = iric.cg_iRIC_Read_BC_Integer("bctest", 1, "intparam")
    util.verify_log("cg_iRIC_Read_BC_Integer() val == 1", cond_int == 1)

    try:
        cond_int = iric.cg_iRIC_Read_BC_Integer("bctestaa", 1, "intparam")
        print('cg_iRIC_Read_BC_Integer() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_Integer() raise Exception for invalid name [OK]')

    try:
        cond_int = iric.cg_iRIC_Read_BC_Integer("bctest", 4, "intparam")
        print('cg_iRIC_Read_BC_Integer() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_Integer() raise Exception for invalid name [OK]')

    try:
        cond_int = iric.cg_iRIC_Read_BC_Integer("bctest", 1, "intparam2")
        print('cg_iRIC_Read_BC_Integer() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_Integer() raise Exception for invalid name [OK]')

    cond_double = iric.cg_iRIC_Read_BC_Real("bctest", 1, "realparam")
    util.verify_log("cg_iRIC_Read_BC_Real() val == 4.2", cond_double == 4.2)

    try:
        cond_double = iric.cg_iRIC_Read_BC_Real("bctest", 1, "realparam2")
        print('cg_iRIC_Read_BC_Real() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_Real() raise Exception for invalid name [OK]')

    strdata = iric.cg_iRIC_Read_BC_String("bctest", 1, "stringparam")
    util.verify_log("cg_iRIC_Read_BC_String() val == AAA", strdata == "AAA")

    try:
        strdata = iric.cg_iRIC_Read_BC_String("bctest_dummy", 1, "stringparam")
        print('cg_iRIC_Read_BC_String() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_String() raise Exception for invalid name [OK]')

    try:
        strdata = iric.cg_iRIC_Read_BC_String("bctest", 4, "stringparam")
        print('cg_iRIC_Read_BC_String() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_String() raise Exception for invalid name [OK]')

    try:
        strdata = iric.cg_iRIC_Read_BC_String("bctest", 1, "stringparam2")
        print('cg_iRIC_Read_BC_String() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_String() raise Exception for invalid name [OK]')

    try:
        strdata = iric.cg_iRIC_Read_BC_String("bctest", 1, "stringval2")
        print('cg_iRIC_Read_BC_String() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_String() raise Exception for invalid name [OK]')

    params, values = iric.cg_iRIC_Read_BC_Functional("bctest", 1, "funcparam")
    util.verify_log("cg_iRIC_Read_BC_Functional() param value[0]", params[0] == 0)
    util.verify_log("cg_iRIC_Read_BC_Functional() param value[1]", params[1] == 1)
    util.verify_log("cg_iRIC_Read_BC_Functional() param value[2]", params[2] == 2)
    util.verify_log("cg_iRIC_Read_BC_Functional() value value[0]", values[0] == 5)
    util.verify_log("cg_iRIC_Read_BC_Functional() value value[1]", values[1] == 4)
    util.verify_log("cg_iRIC_Read_BC_Functional() value value[2]", values[2] == 2)

    try:
        params, values = iric.cg_iRIC_Read_BC_Functional("bctest_dmmy", 1, "funcparam")
        print('cg_iRIC_Read_BC_Functional() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_Functional() raise Exception for invalid name [OK]')

    try:
        params, values = iric.cg_iRIC_Read_BC_Functional("bctest", 5, "funcparam")
        print('cg_iRIC_Read_BC_Functional() raise Exception for invalid num [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_Functional() raise Exception for invalid num [OK]')

    try:
        params, values = iric.cg_iRIC_Read_BC_Functional("bctest", 1, "funcpareem")
        print('cg_iRIC_Read_BC_Functional() raise Exception for invalid num [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_Functional() raise Exception for invalid num [OK]')

    try:
        params, values = iric.cg_iRIC_Read_BC_Functional("bctest", 1, "func100")
        print('cg_iRIC_Read_BC_Functional() raise Exception for invalid paramname [NG]')
    except Exception:
        print('cg_iRIC_Read_BC_Functional() raise Exception for invalid paramname [OK]')

    params = iric.cg_iRIC_Read_BC_FunctionalWithName("bctest", 1, "funcparam", "Param")
    values = iric.cg_iRIC_Read_BC_FunctionalWithName("bctest", 1, "funcparam", "Value")

    util.verify_log("cg_iRIC_Read_BC_FunctionalWithName() param value[0]", params[0] == 0)
    util.verify_log("cg_iRIC_Read_BC_FunctionalWithName() param value[1]", params[1] == 1)
    util.verify_log("cg_iRIC_Read_BC_FunctionalWithName() param value[2]", params[2] == 2)

    util.verify_log("cg_iRIC_Read_BC_FunctionalWithName() value value[0]", values[0] == 5)
    util.verify_log("cg_iRIC_Read_BC_FunctionalWithName() value value[1]", values[1] == 4)
    util.verify_log("cg_iRIC_Read_BC_FunctionalWithName() value value[2]", values[2] == 2)

    iric.cg_close(fid)

    util.remove('data/case_bc.cgn')

def case_BcWrite():
    shutil.copy("data/case_init_hdf5.cgn", "data/case_bcwrite.cgn")

    fid_wrong = 9999

    fid = iric.cg_open("data/case_bcwrite.cgn", iric.CG_MODE_MODIFY)
    util.verify_log("cg_open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    iric.cg_iRIC_Clear_BC_Mul(fid)

    indices = np.zeros(10, dtype=np.int32)
    for i in range(5):
        indices[i * 2 + 0] = 1
        indices[i * 2 + 1] = i + 3

    iric.cg_iRIC_Write_BC_Indices("testbc", 1, indices)

    write_int = 121
    iric.cg_iRIC_Write_BC_Integer("testbc", 1, "write_int", write_int)

    try:
        ier = iric.cg_iRIC_Write_BC_Integer_Mul(fid_wrong, "testbc", 1, "write_int", write_int)
        print('cg_iRIC_Write_BC_Integer() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_BC_Integer() raise Exception for invalid fid [OK]')

    write_double = 3.14159
    iric.cg_iRIC_Write_BC_Real("testbc", 1, "write_double", write_double)

    try:
        iric.cg_iRIC_Write_BC_Real_Mul(fid_wrong, "testbc", 1, "write_double", write_double)
        print('cg_iRIC_Write_BC_Real() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_BC_Real() raise Exception for invalid fid [OK]')

    write_str = "TEST_STRING_3.14"
    iric.cg_iRIC_Write_BC_String("testbc", 1, "write_string", write_str)

    try:
        iric.cg_iRIC_Write_BC_String_Mul(fid_wrong, "testbc", 1, "write_string", write_str)
        print('cg_iRIC_Write_BC_String() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_BC_String() raise Exception for invalid fid [OK]')

    params = np.zeros(5, dtype=np.float64)
    vals = np.zeros(5, dtype=np.float64)

    for i in range(5):
        params[i] = 2.3 * i + 1.2
        vals[i] = 5.1 * i + 0.8

    iric.cg_iRIC_Write_BC_Functional("testbc", 1, "write_func", params, vals)

    try:
        iric.cg_iRIC_Write_BC_Functional_Mul(fid_wrong, "testbc", 1, "write_func", params, vals)
        print('cg_iRIC_BC_Write_Functional() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_BC_Write_Functional() raise Exception for invalid fid [OK]')

    iric.cg_iRIC_Write_BC_FunctionalWithName("testbc", 1, "write_func_withname", "time", params)
    iric.cg_iRIC_Write_BC_FunctionalWithName("testbc", 1, "write_func_withname", "elev", vals)

    try:
        iric.cg_iRIC_Write_BC_FunctionalWithName_Mul(fid_wrong, "testbc", 1, "write_func_withname", "time", params)
        print('cg_iRIC_Write_BC_FunctionalWithName() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_BC_FunctionalWithName() raise Exception for invalid fid [OK]')

    iric.cg_iRIC_Write_BC_FunctionalWithName("testbc", 1, "write_func_withname_string", "time", params)
    iric.cg_iRIC_Write_BC_FunctionalWithName("testbc", 1, "write_func_withname_string", "elev", vals)

    iric.cg_iRIC_Write_BC_FunctionalWithName_String("testbc", 1, "write_func_withname_string", "_siteID", "01646500")
    iric.cg_iRIC_Write_BC_FunctionalWithName_String("testbc", 1, "write_func_withname_string", "_startDate", "2017-06-01T06:00")
    iric.cg_iRIC_Write_BC_FunctionalWithName_String("testbc", 1, "write_func_withname_string", "_endDate", "2017-06-01T10:00")

    read_num = iric.cg_iRIC_Read_BC_Count("testbc")
    util.verify_log("cg_iRIC_Read_BC_Count() read_num == 1", read_num == 1)

    size = iric.cg_iRIC_Read_BC_IndicesSize2("testbc", 1)
    util.verify_log("cg_iRIC_Read_BC_IndicesSize2() size == 10", size == 10)

    indices = iric.cg_iRIC_Read_BC_Indices("testbc", 1)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[0] == 1", indices[0] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[1] == 1", indices[1] == 3)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[2] == 1", indices[2] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[3] == 2", indices[3] == 4)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[4] == 1", indices[4] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[5] == 3", indices[5] == 5)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[6] == 1", indices[6] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[7] == 4", indices[7] == 6)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[8] == 1", indices[8] == 1)
    util.verify_log("cg_iRIC_Read_BC_Indices_Mul() indices[9] == 5", indices[9] == 7)

    read_int = iric.cg_iRIC_Read_BC_Integer("testbc", 1, "write_int")
    util.verify_log("cg_iRIC_Read_BC_Integer() value match", read_int == write_int)

    read_double = iric.cg_iRIC_Read_BC_Real("testbc", 1, "write_double")
    util.verify_log("cg_iRIC_Read_BC_Real() value match", read_double == read_double)

    read_str = iric.cg_iRIC_Read_BC_String("testbc", 1, "write_string")
    util.verify_log("cg_iRIC_Read_BC_String() value match", read_str == write_str)

    read_params, read_vals = iric.cg_iRIC_Read_BC_Functional("testbc", 1, "write_func")
    util.verify_log("cg_iRIC_Read_BC_Functional() param match", np.array_equal(params, read_params))
    util.verify_log("cg_iRIC_Read_BC_Functional() value match", np.array_equal(vals, read_vals))

    read_str = iric.cg_iRIC_Read_BC_FunctionalWithName_String("testbc", 1, "write_func_withname_string", "_siteID")
    util.verify_log("cg_iRIC_Read_FunctionalWithName_String() value match", read_str == "01646500")

    read_str = iric.cg_iRIC_Read_BC_FunctionalWithName_String("testbc", 1, "write_func_withname_string", "_startDate")
    util.verify_log("cg_iRIC_Read_BC_FunctionalWithName_String() value match", read_str == "2017-06-01T06:00")

    read_str = iric.cg_iRIC_Read_BC_FunctionalWithName_String("testbc", 1, "write_func_withname_string", "_endDate")
    util.verify_log("cg_iRIC_Read_BC_FunctionalWithName_String() value match", read_str == "2017-06-01T10:00")

    iric.cg_close(fid)

    util.remove("data/case_bcwrite.cgn")
