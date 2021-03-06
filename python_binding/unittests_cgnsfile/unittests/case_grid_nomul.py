import shutil
import numpy as np

import iric

from . import util

def case_GridRead():
    shutil.copy("data/case_init.cgn", "data/case_grid.cgn")

    fid = iric.cg_open("data/case_grid.cgn", iric.CG_MODE_MODIFY)
    util.verify_log("cg_open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    isize, jsize = iric.cg_iRIC_GotoGridCoord2d()
    util.verify_log("cg_iRIC_GotoGridCoord2d() isize == 11", isize == 11)
    util.verify_log("cg_iRIC_GotoGridCoord2d() jsize == 11", jsize == 11)

    x, y = iric.cg_iRIC_GetGridCoord2d_Mul(fid)

    doubleArr = iric.cg_iRIC_Read_Grid_Real_Node("node_real")
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[0] == 2", doubleArr[0] == 2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[1] == 2", doubleArr[1] == 2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[2] == 2", doubleArr[2] == 2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[3] == 2", doubleArr[3] == 2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[4] == 2", doubleArr[4] == 2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[5] == 2", doubleArr[5] == 2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[6] == 2", doubleArr[6] == 2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[7] == 0", doubleArr[7] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[8] == 0", doubleArr[8] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Real_Node() value[9] == 0", doubleArr[9] == 0)

    intArr = iric.cg_iRIC_Read_Grid_Integer_Node("node_int")
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[0] == 0", intArr[0] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[1] == 0", intArr[1] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[2] == 0", intArr[2] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[3] == 0", intArr[3] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[4] == 0", intArr[4] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[5] == 1", intArr[5] == 1)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[6] == 1", intArr[6] == 1)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[7] == 1", intArr[7] == 1)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[8] == 1", intArr[8] == 1)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Node() value[9] == 1", intArr[9] == 1)

    doubleArr = iric.cg_iRIC_Read_Grid_Real_Cell("cell_real")
    util.verify_log("cg_iRIC_Read_Grid_Real_Cell() value[0] == 4.2", doubleArr[0] == 4.2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Cell() value[1] == 4.2", doubleArr[1] == 4.2)
    util.verify_log("cg_iRIC_Read_Grid_Real_Cell() value[2] == 0", doubleArr[2] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Real_Cell() value[3] == 0", doubleArr[3] == 0)

    intArr = iric.cg_iRIC_Read_Grid_Integer_Cell("cell_int")
    util.verify_log("cg_iRIC_Read_Grid_Integer_Cell() value[0] == 0", intArr[0] == 0)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Cell() value[15] == 1", intArr[15] == 1)
    util.verify_log("cg_iRIC_Read_Grid_Integer_Cell() value[16] == 0", intArr[16] == 0)

    iric.cg_close(fid)

    util.remove("data/case_grid.cgn")

def case_GridReadFunc():
    shutil.copy("data/case_gridfunc.cgn", "data/case_gridreadfunc.cgn")

    fid = iric.cg_open("data/case_gridreadfunc.cgn", iric.CG_MODE_MODIFY)
    util.verify_log("cg_open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    isize, jsize = iric.cg_iRIC_GotoGridCoord2d_Mul(fid)
    util.verify_log("cg_iRIC_GotoGridCoord2d() isize == 15", isize == 15)
    util.verify_log("cg_iRIC_GotoGridCoord2d() jsize == 15", jsize == 15)

    x, y = iric.cg_iRIC_GetGridCoord2d_Mul(fid)

    timeArr = iric.cg_iRIC_Read_Grid_FunctionalDimension_Real("Xrain", "Time")
    timeArr = iric.cg_iRIC_Read_Grid_FunctionalTime("Xrain")

    for i in range(timeArr.size):
        rain = iric.cg_iRIC_Read_Grid_Functional_Real_Node("Xrain", i + 1)

    iric.cg_close(fid)

    util.remove("data/case_gridreadfunc.cgn")

def case_GridWrite():
    shutil.copy("data/case_nogrid.cgn", "data/case_gridwrite1d.cgn")

    fid = iric.cg_open("data/case_gridwrite1d.cgn", iric.CG_MODE_MODIFY)
    util.verify_log("cg_open() fid != 0", fid != 0)

    try:
        iric.cg_iRIC_Init(fid)
        print('cg_iRIC_Init raise Exception for CGNS without grid [NG]')
    except Exception:
        print('cg_iRIC_Init raise Exception for CGNS without grid [OK]')

    isize = 10
    x = np.zeros(isize, dtype=np.float64)

    for i in range(isize):
        x[i] = i * 2

    iric.cg_iRIC_WriteGridCoord1d(isize, x)

    iric.cg_close(fid)

    """
    ier, fid = iric.cg_open("case_gridwrite1d.cgn", iric.CG_MODE_READ)
    util.verify_log("cg_open() ier == 0", ier == 0)
    util.verify_log("cg_open() fid != 0", fid != 0)

    ier = iric.cg_goto(fid, 2, "iRICZone", 0, "GridCoordinates", 0, NULL)
    util.verify_log("cg_goto() ier == 0", ier == 0)
    int dim
    char name[32]
    DataType_t datatype
    cgsize_t dimVec[12]
    ier = cg_array_info(1, name, &datatype, &dim, dimVec)
    util.verify_log("cg_array_info() ier == 0", ier == 0)
    util.verify_log("cg_array_info() name == CoordinateX", std::string("CoordinateX") == name)
    util.verify_log("cg_array_info() datatype == RealDouble", datatype == RealDouble)
    util.verify_log("cg_array_info() dim == 1", dim == 1)
    util.verify_log("cg_array_info() dimVec[0] == 10", dimVec[0] == 10)

    std::vector<double> read_x, read_y, read_z
    read_x.assign(dimVec[0], 0)
    ier = cg_array_read(1, read_x.data())
    util.verify_log("cg_array_read() ier == 0", ier == 0)
    util.verify_log("cg_array_read() value valid", x == read_x)

    cg_close(fid)
    """

    util.remove("data/case_gridwrite1d.cgn")

    shutil.copy("data/case_nogrid.cgn", "data/case_gridwrite2d.cgn")

    fid = iric.cg_open("data/case_gridwrite2d.cgn", iric.CG_MODE_MODIFY)
    util.verify_log("cg_open() fid != 0", fid != 0)

    try:
        iric.cg_iRIC_Init(fid)
        print('cg_iRIC_Init raise Exception for CGNS without grid [NG]')
    except Exception:
        print('cg_iRIC_Init raise Exception for CGNS without grid [OK]')

    isize = 10
    jsize = 8
    x = np.zeros(isize * jsize, dtype=np.float64)
    y = np.zeros(isize * jsize, dtype=np.float64)

    for j in range(jsize):
        for i in range(isize):
            idx = i + isize * j
            x[idx] = i
            y[idx] = j

    iric.cg_iRIC_WriteGridCoord2d(isize, jsize, x, y)

    real_node_write = np.zeros(isize * jsize, dtype=np.float64)
    int_node_write = np.zeros(isize * jsize, dtype=np.int32)
    real_cell_write = np.zeros((isize - 1) * (jsize - 1), dtype=np.float64)
    int_cell_write = np.zeros((isize - 1) * (jsize - 1), dtype=np.int32)

    for i in range(real_node_write.size):
        real_node_write[i] = 0.5 * i - 0.01 * i * (i - 50)

    for i in range(int_node_write.size):
        int_node_write[i] = i * i + i * 2 + 6

    for i in range(real_cell_write.size):
        real_cell_write[i] = 0.8 * i - 0.0005 * i * (i - 10)

    for i in range(int_cell_write.size):
        int_cell_write[i] = i * i - i * 4 + 414

    iric.cg_iRIC_Write_Grid_Real_Node("realnode_test", real_node_write)

    iric.cg_iRIC_Write_Grid_Integer_Node("intnode_test", int_node_write)

    iric.cg_iRIC_Write_Grid_Real_Cell("realcell_test", real_cell_write)

    iric.cg_iRIC_Write_Grid_Integer_Cell("intcell_test", int_cell_write)

    iric.cg_close(fid)

    """
    ier = cg_open("case_gridwrite2d.cgn", CG_MODE_READ, &fid)
    util.verify_log("cg_open() ier == 0", ier == 0)
    util.verify_log("cg_open() fid != 0", fid != 0)

    cgsize_t size[9]
    ier = cg_zone_read(fid, 1, 1, name, size)
    util.verify_log("cg_zone_read() ier == 0", ier == 0)
    util.verify_log("cg_zone_read() name == iRICZone", strcmp(name, "iRICZone") == 0)
    util.verify_log("cg_zone_read() size[0] == isize",   size[0] == isize)
    util.verify_log("cg_zone_read() size[1] == jsize",   size[1] == jsize)
    util.verify_log("cg_zone_read() size[2] == isize-1", size[2] == isize-1)
    util.verify_log("cg_zone_read() size[3] == jsize-1", size[3] == jsize-1)
    util.verify_log("cg_zone_read() size[4] == 0",       size[4] == 0)
    util.verify_log("cg_zone_read() size[5] == 0",       size[5] == 0)

    ier = cg_goto(fid, 1, "iRICZone", 0, "GridCoordinates", 0, NULL)
    util.verify_log("cg_goto() ier == 0", ier == 0)
    ier = cg_array_info(1, name, &datatype, &dim, dimVec)
    util.verify_log("cg_array_info() ier == 0", ier == 0)
    util.verify_log("cg_array_info() name == CoordinateX", std::string("CoordinateX") == name)
    util.verify_log("cg_array_info() datatype == RealDouble", datatype == RealDouble)

    read_x.assign(dimVec[0] * dimVec[1], 0)
    read_y.assign(dimVec[0] * dimVec[1], 0)

    ier = cg_array_read(1, read_x.data())
    util.verify_log("cg_array_read() ier == 0", ier == 0)
    util.verify_log("cg_array_read() value valid", x == read_x)

    ier = cg_array_read(2, read_y.data())
    util.verify_log("cg_array_read() ier == 0", ier == 0)
    util.verify_log("cg_array_read() value valid", y == read_y)

    ier = cg_goto(fid, 1, "iRICZone", 0, "GridConditions", 0, "realnode_test", 0, NULL)
    util.verify_log("cg_goto() for realnode_test ier == 0", ier == 0)
    ier = cg_array_info(1, name, &datatype, &dim, dimVec)
    std::vector<double> real_node_read
    real_node_read.assign(dimVec[0], 0)
    ier = cg_array_read(1, real_node_read.data())
    util.verify_log("cg_array_read() for realnode_test ier == 0", ier == 0)
    util.verify_log("realnode_test value check", real_node_read == real_node_write)

    ier = cg_goto(fid, 1, "iRICZone", 0, "GridConditions", 0, "intnode_test", 0, NULL)
    util.verify_log("cg_goto() for intnode_test ier == 0", ier == 0)
    ier = cg_array_info(1, name, &datatype, &dim, dimVec)
    std::vector<int> int_node_read
    int_node_read.assign(dimVec[0], 0)
    ier = cg_array_read(1, int_node_read.data())
    util.verify_log("cg_array_read() for intnode_test ier == 0", ier == 0)
    util.verify_log("intnode_test value check", int_node_read == int_node_write)

    ier = cg_goto(fid, 1, "iRICZone", 0, "GridConditions", 0, "realcell_test", 0, NULL)
    util.verify_log("cg_goto() for realcell_test ier == 0", ier == 0)
    ier = cg_array_info(1, name, &datatype, &dim, dimVec)
    std::vector<double> real_cell_read
    real_cell_read.assign(dimVec[0], 0)
    ier = cg_array_read(1, real_cell_read.data())
    util.verify_log("cg_array_read() for realcell_test ier == 0", ier == 0)
    util.verify_log("realcell_test value check", real_cell_read == real_cell_write)

    ier = cg_goto(fid, 1, "iRICZone", 0, "GridConditions", 0, "intcell_test", 0, NULL)
    util.verify_log("cg_goto() for intcell_test ier == 0", ier == 0)
    ier = cg_array_info(1, name, &datatype, &dim, dimVec)
    std::vector<int> int_cell_read
    int_cell_read.assign(dimVec[0], 0)
    ier = cg_array_read(1, int_cell_read.data())
    util.verify_log("cg_array_read() for intcell_test ier == 0", ier == 0)
    util.verify_log("intcell_test value check", int_cell_read == int_cell_write)

    cg_close(fid)
    """

    util.remove("data/case_gridwrite2d.cgn")

    shutil.copy("data/case_nogrid.cgn", "data/case_gridwrite3d.cgn")

    fid = iric.cg_open("data/case_gridwrite3d.cgn", iric.CG_MODE_MODIFY)

    util.verify_log("cg_open() fid != 0", fid != 0)
    
    try:
        iric.cg_iRIC_Init(fid)
        print('cg_iRIC_Init raise Exception for CGNS without grid [NG]')
    except Exception:
        print('cg_iRIC_Init raise Exception for CGNS without grid [OK]')

    isize = 11
    jsize = 9
    ksize = 5
    size = isize * jsize * ksize
    x = np.zeros(size, dtype=np.float64)
    y = np.zeros(size, dtype=np.float64)
    z = np.zeros(size, dtype=np.float64)

    for k in range(ksize):
        for j in range(jsize):
            for i in range(isize):
                idx = i + isize * j + isize * jsize * k
                x[idx] = i
                y[idx] = j
                z[idx] = k

    iric.cg_iRIC_WriteGridCoord3d(isize, jsize, ksize, x, y, z)

    iric.cg_close(fid)

    """
    ier = cg_open("case_gridwrite3d.cgn", CG_MODE_READ, &fid)
    util.verify_log("cg_open() ier == 0", ier == 0)
    util.verify_log("cg_open() fid != 0", fid != 0)

    ier = cg_zone_read(fid, 2, 1, name, size)
    util.verify_log("cg_zone_read() ier == 0", ier == 0)
    util.verify_log("cg_zone_read() name == iRICZone", strcmp(name, "iRICZone") == 0)
    util.verify_log("cg_zone_read() size[0] == isize",   size[0] == isize)
    util.verify_log("cg_zone_read() size[1] == jsize",   size[1] == jsize)
    util.verify_log("cg_zone_read() size[2] == ksize",   size[2] == ksize)
    util.verify_log("cg_zone_read() size[3] == isize-1", size[3] == isize-1)
    util.verify_log("cg_zone_read() size[4] == jsize-1", size[4] == jsize-1)
    util.verify_log("cg_zone_read() size[5] == ksize-1", size[5] == ksize-1)
    util.verify_log("cg_zone_read() size[6] == 0",       size[6] == 0)
    util.verify_log("cg_zone_read() size[7] == 0",       size[7] == 0)
    util.verify_log("cg_zone_read() size[8] == 0",       size[8] == 0)

    ier = cg_goto(fid, 2, "iRICZone", 0, "GridCoordinates", 0, NULL)
    util.verify_log("cg_goto() ier == 0", ier == 0)
    ier = cg_array_info(1, name, &datatype, &dim, dimVec)
    util.verify_log("cg_array_info() ier == 0", ier == 0)
    util.verify_log("cg_array_info() name == CoordinateX", std::string("CoordinateX") == name)
    util.verify_log("cg_array_info() datatype == RealDouble", datatype == RealDouble)

    read_x.assign(dimVec[0] * dimVec[1] * dimVec[2], 0)
    read_y.assign(dimVec[0] * dimVec[1] * dimVec[2], 0)
    read_z.assign(dimVec[0] * dimVec[1] * dimVec[2], 0)

    ier = cg_array_read(1, read_x.data())
    util.verify_log("cg_array_read() ier == 0", ier == 0)
    util.verify_log("cg_array_read() value valid", x == read_x)

    ier = cg_array_read(2, read_y.data())
    util.verify_log("cg_array_read() ier == 0", ier == 0)
    util.verify_log("cg_array_read() value valid", y == read_y)

    ier = cg_array_read(3, read_z.data())
    util.verify_log("cg_array_read() ier == 0", ier == 0)
    util.verify_log("cg_array_read() value valid", z == read_z)

    cg_close(fid)
    """

    util.remove("data/case_gridwrite3d.cgn")
