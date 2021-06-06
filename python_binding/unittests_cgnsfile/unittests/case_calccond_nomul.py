import shutil
import numpy as np

import iric

from . import util

def case_CalcCondRead():
    util.remove("data/case_cc.cgn")
    shutil.copy("data/case_init_hdf5.cgn", "data/case_cc.cgn")

    fid = iric.cg_iRIC_Open("data/case_cc.cgn", iric.IRIC_MODE_MODIFY)
    util.verify_log("cg_iRIC_Open() fid != 0", fid != 0)

    cond_int = iric.cg_iRIC_Read_Integer("intval")
    util.verify_log("cg_iRIC_Read_Integer() val == 1", cond_int == 1)

    try:
        cond_int = iric.cg_iRIC_Read_Integer("intval2")
        print('cg_iRIC_Read_Integer() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_Integer() raise Exception for invalid name [OK]')

    cond_double = iric.cg_iRIC_Read_Real("doubleval")
    util.verify_log("cg_iRIC_Read_Real() val == 4.21", cond_double == 4.21)

    try:
        cond_double = iric.cg_iRIC_Read_Real("doubleval2")
        print('cg_iRIC_Read_Real() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_Real() raise Exception for invalid name [OK]')

    string = iric.cg_iRIC_Read_String("stringval")
    util.verify_log("cg_iRIC_Read_String() val == TESTSTRING", string == "TESTSTRING")

    try:
        string = iric.cg_iRIC_Read_String("stringval2")
        print('cg_iRIC_Read_String() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_String() raise Exception for invalid name [OK]')

    params, values = iric.cg_iRIC_Read_Functional("func1")
    util.verify_log("cg_iRIC_Read_Functional() param value[0]", params[0] == 0)
    util.verify_log("cg_iRIC_Read_Functional() param value[1]", params[1] == 1)
    util.verify_log("cg_iRIC_Read_Functional() param value[2]", params[2] == 2)
    util.verify_log("cg_iRIC_Read_Functional() param value[3]", params[3] == 3)
    util.verify_log("cg_iRIC_Read_Functional() value value[0]", values[0] == 0)
    util.verify_log("cg_iRIC_Read_Functional() value value[1]", values[1] == 3)
    util.verify_log("cg_iRIC_Read_Functional() value value[2]", values[2] == 4.5)
    util.verify_log("cg_iRIC_Read_Functional() value value[3]", values[3] == 2.8)

    try:
        params, values = iric.cg_iRIC_Read_Functional("func100")
        print('cg_iRIC_Read_Functional() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_Functional() raise Exception for invalid name [OK]')

    params = iric.cg_iRIC_Read_FunctionalWithName("func2", "time")
    values = iric.cg_iRIC_Read_FunctionalWithName("func2", "value2")

    util.verify_log("cg_iRIC_Read_FunctionalWithName() param value[0]", params[0] == 0)
    util.verify_log("cg_iRIC_Read_FunctionalWithName() param value[1]", params[1] == 3)
    util.verify_log("cg_iRIC_Read_FunctionalWithName() param value[2]", params[2] == 4)
    util.verify_log("cg_iRIC_Read_FunctionalWithName() param value[3]", params[3] == 6)
    util.verify_log("cg_iRIC_Read_FunctionalWithName() param value[4]", params[4] == 8)

    util.verify_log("cg_iRIC_Read_FunctionalWithName() value value[0]", values[0] == 4.5)
    util.verify_log("cg_iRIC_Read_FunctionalWithName() value value[1]", values[1] == 8)
    util.verify_log("cg_iRIC_Read_FunctionalWithName() value value[2]", values[2] == 5)
    util.verify_log("cg_iRIC_Read_FunctionalWithName() value value[3]", values[3] == 4)
    util.verify_log("cg_iRIC_Read_FunctionalWithName() value value[4]", values[4] == 4.2)

    try:
        params = iric.cg_iRIC_Read_FunctionalWithName("func200", "time")
        print('cg_iRIC_Read_FunctionalWithName() raise Exception for invalid name [NG]')
    except Exception:
        print('cg_iRIC_Read_FunctionalWithName() raise Exception for invalid name [OK]')

    iric.cg_iRIC_Close(fid)

    util.remove("data/case_cc.cgn")

def case_CalcCondWrite():
    shutil.copy('data/case_init_hdf5.cgn', 'data/case_ccwrite.cgn')

    fid = iric.cg_iRIC_Open("data/case_ccwrite.cgn", iric.IRIC_MODE_MODIFY)

    fid_wrong = 9999

    write_int = 121
    iric.cg_iRIC_Write_Integer("write_int", write_int)

    try:
        iric.cg_iRIC_Write_Integer_Mul(fid_wrong, "write_int", write_int)
        print('cg_iRIC_Write_Integer() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_Integer() raise Exception for invalid fid [OK]')

    write_double = 3.14159
    iric.cg_iRIC_Write_Real("write_double", write_double)

    try:
        iric.cg_iRIC_Write_Real_Mul(fid_wrong, "write_double", write_double)
        print('cg_iRIC_Write_Real() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_Real() raise Exception for invalid fid [OK]')

    write_str = "TEST_STRING_3.14"
    iric.cg_iRIC_Write_String("write_string", write_str)

    try:
        iric.cg_iRIC_Write_String_Mul(fid_wrong, "write_string", write_str)
        print('cg_iRIC_Write_String() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_String() raise Exception for invalid fid [OK]')

    params = np.zeros(5, dtype=np.float64)
    vals = np.zeros(5, dtype=np.float64)
    for i in range(5):
        params[i] = 2.3 * i + 1.2
        vals[i] = 5.1 * i + 0.8
    
    iric.cg_iRIC_Write_Functional("write_func", params, vals)

    try:
        iric.cg_iRIC_Write_Functional_Mul(fid_wrong, "write_func", params, vals)
        print('cg_iRIC_Write_Functional() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_Functional() raise Exception for invalid fid [OK]')

    iric.cg_iRIC_Write_FunctionalWithName("write_func_withname", "time", params)
    iric.cg_iRIC_Write_FunctionalWithName("write_func_withname", "elev", vals)

    try:
        iric.cg_iRIC_Write_FunctionalWithName_Mul(fid_wrong, "write_func_withname", "time", params)
        print('cg_iRIC_Write_FunctionalWithName() raise Exception for invalid fid [NG]')
    except Exception:
        print('cg_iRIC_Write_FunctionalWithName() raise Exception for invalid fid [OK]')

    iric.cg_iRIC_Write_FunctionalWithName("write_func_withname_string", "time", params)
    iric.cg_iRIC_Write_FunctionalWithName("write_func_withname_string", "discharge", vals)

    iric.cg_iRIC_Write_FunctionalWithName_String("write_func_withname_string", "_siteID", "01646500")
    iric.cg_iRIC_Write_FunctionalWithName_String("write_func_withname_string", "_startDate", "2017-06-01T06:00")
    iric.cg_iRIC_Write_FunctionalWithName_String("write_func_withname_string", "_endDate", "2017-06-01T10:00")

    read_int = iric.cg_iRIC_Read_Integer("write_int")
    util.verify_log("cg_iRIC_Read_Integer() value match", read_int == write_int)

    read_double = iric.cg_iRIC_Read_Real("write_double")
    util.verify_log("cg_iRIC_Read_Real() value match", read_double == read_double)

    read_str = iric.cg_iRIC_Read_String("write_string")
    util.verify_log("cg_iRIC_Read_String() value match", read_str == write_str)

    read_params, read_vals = iric.cg_iRIC_Read_Functional("write_func")
    util.verify_log("cg_iRIC_Read_Functional() param match", np.array_equal(params, read_params))
    util.verify_log("cg_iRIC_Read_Functional() value match", np.array_equal(vals, read_vals))

    read_str = iric.cg_iRIC_Read_FunctionalWithName_String("write_func_withname_string", "_siteID")
    util.verify_log("cg_iRIC_Read_FunctionalWithName_String() value match", read_str == "01646500")

    read_str = iric.cg_iRIC_Read_FunctionalWithName_String("write_func_withname_string", "_startDate")
    util.verify_log("cg_iRIC_Read_FunctionalWithName_String() value match", read_str == "2017-06-01T06:00")

    read_str = iric.cg_iRIC_Read_FunctionalWithName_String("write_func_withname_string", "_endDate")
    util.verify_log("cg_iRIC_Read_FunctionalWithName_String() value match", read_str == "2017-06-01T10:00")

    iric.cg_iRIC_Close(fid)

    util.remove("data/case_ccwrite.cgn")
