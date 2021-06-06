import shutil
import numpy as np

import iric

from . import util

def writeSolution(filename, fid, iterMode):
    isize, jsize = iric.cg_iRIC_Read_Grid2d_Str_Size_Mul(fid)

    # fill iface
    iface_is_edge = np.zeros(isize * (jsize - 1), dtype=np.int32)
    iface_is_edge_reals = np.zeros(isize * (jsize - 1), dtype=np.float64)

    for j in range(jsize - 1):
        for i in range(isize):
            if j == 0 or j == (jsize - 2) or i == 0 or i == (isize - 1):
                iface_is_edge[j * isize + i] = 1
                iface_is_edge_reals[j * isize + i] = .1

    # fill jface
    jface_is_edge = np.zeros((isize - 1) * jsize, dtype=np.int32)
    jface_is_edge_reals = np.zeros((isize - 1) * jsize, dtype=np.float64)

    for j in range(jsize):
        for i in range(isize - 1):
            if j == 0 or j == (jsize - 1) or i == 0 or i == (isize - 2):
                jface_is_edge[j * (isize - 1) + i] = 2
                jface_is_edge_reals[j * (isize - 1) + i] = .2

    x, y = iric.cg_iRIC_Read_Grid2d_Coords_Mul(fid)

    vx = np.full(isize * jsize, 1, dtype=np.float64)
    vy = np.full(isize * jsize, 0.3, dtype=np.float64)
    depth = np.full(isize * jsize, 4, dtype=np.float64)
    wet = np.zeros(isize * jsize, dtype=np.int32)

    particle_num = 20
    particle_x = np.zeros(particle_num, dtype=np.float64)
    particle_y = np.zeros(particle_num, dtype=np.float64)
    particle_vx = np.full(particle_num, 2, dtype=np.float64)
    particle_vy = np.full(particle_num, 3, dtype=np.float64)
    particle_active = np.full(particle_num, 1, dtype=np.int32)

    for i in range(particle_num):
        particle_x[i] = i

    for i in range(5):
        if iterMode:
            IterVal = i
            iric.cg_iRIC_Write_Sol_Iteration_Mul(fid, IterVal)
        else:
            TimeVal = i * 2.13
            iric.cg_iRIC_Write_Sol_Time_Mul(fid, TimeVal)

        iric.cg_iRIC_Write_Sol_Grid2d_Coords_Mul(fid, x, y)

        # Vertex solutions

        depth[:] = i
        iric.cg_iRIC_Write_Sol_Node_Real_Mul(fid, "Depth", depth)
        iric.cg_iRIC_Write_Sol_Node_Real_Mul(fid, "VelocityX", vx)
        iric.cg_iRIC_Write_Sol_Node_Real_Mul(fid, "VelocityY", vy)

        wet[:] = i
        iric.cg_iRIC_Write_Sol_Node_Integer_Mul(fid, "IBC", wet)

        # CellCenter solutions

        ccdepth = np.full((isize - 1) * (jsize - 1), 0.2 + i, dtype=np.float64)
        iric.cg_iRIC_Write_Sol_Cell_Real_Mul(fid, "CCDepth", ccdepth)

        ccwet = np.full((isize - 1) * (jsize - 1), i + 1, dtype=np.int32)
        iric.cg_iRIC_Write_Sol_Cell_Integer_Mul(fid, "CCWet", ccwet)

        # IFaceCenter solutions

        iric.cg_iRIC_Write_Sol_IFace_Integer_Mul(fid, "IFaceIsEdge", iface_is_edge)
        iric.cg_iRIC_Write_Sol_IFace_Real_Mul(fid, "IFaceIsEdgeReals", iface_is_edge_reals)

        # JFaceCenter solutions

        iric.cg_iRIC_Write_Sol_JFace_Integer_Mul(fid, "JFaceIsEdge", jface_is_edge)
        iric.cg_iRIC_Write_Sol_JFace_Real_Mul(fid, "JFaceIsEdgeReals", jface_is_edge_reals)

        # BaseIterativeData

        Dist = i * - 0.2 + 20
        iric.cg_iRIC_Write_Sol_BaseIterative_Real_Mul(fid, "Discharge", Dist)
        DamOpen = i
        iric.cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(fid, "DamOpen", DamOpen)

        teststr = "Test{0}".format(i)
        iric.cg_iRIC_Write_Sol_BaseIterative_String_Mul(fid, "TestStr", teststr)

        # Particle solutions

        iric.cg_iRIC_Write_Sol_Particle_Pos2d_Mul(fid, particle_x, particle_y)
        iric.cg_iRIC_Write_Sol_Particle_Real_Mul(fid, "VelX", particle_vx)
        iric.cg_iRIC_Write_Sol_Particle_Real_Mul(fid, "VelY", particle_vy)
        iric.cg_iRIC_Write_Sol_Particle_Integer_Mul(fid, "Active", particle_active)

        # ParticleGroup solutions

        iric.cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(fid, "group1")
        for j in range(particle_num):
            iric.cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul(fid, particle_x[j], particle_y[j])
            iric.cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(fid, "VelX", particle_vx[j])
            iric.cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(fid, "VelY", particle_vy[j])
            iric.cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(fid, "Active", int(particle_active[j]))

        iric.cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(fid)

        iric.cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(fid, "group2")
        for j in range(particle_num):
            iric.cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul(fid, particle_x[j], 2)
            iric.cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(fid, "VelX", particle_vx[j] + 2)
            iric.cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(fid, "VelY", particle_vy[j] + 1)
            iric.cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(fid, "Active", int(particle_active[j]))

        iric.cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(fid)

        iric.cg_iRIC_Flush(filename, fid)

    return fid

def writeSolution3d(filename, fid):
    isize, jsize = iric.cg_iRIC_Read_Grid2d_Str_Size_Mul(fid)

    x, y = iric.cg_iRIC_Read_Grid2d_Coords_Mul(fid)
    z = np.zeros(isize * jsize, dtype=np.float64)

    iric.cg_iRIC_Write_Grid3d_Coords_Mul(fid, isize, jsize, 1, x, y, z)

    vx = np.full(isize * jsize, 1, dtype=np.float64)
    vy = np.full(isize * jsize, 0.3, dtype=np.float64)
    depth = np.full(isize * jsize, 4, dtype=np.float64)
    wet = np.zeros(isize * jsize, dtype=np.int32)

    particle_num = 20
    particle_x = np.zeros(particle_num, dtype=np.float64)
    particle_y = np.zeros(particle_num, dtype=np.float64)
    particle_z = np.zeros(particle_num, dtype=np.float64)
    particle_vx = np.full(particle_num, 2, dtype=np.float64)
    particle_vy = np.full(particle_num, 3, dtype=np.float64)
    particle_vz = np.full(particle_num, 1, dtype=np.float64)
    particle_active = np.full(particle_num, 1, dtype=np.int32)

    for i in range(particle_num):
        particle_x[i] = i

    for i in range(5):
        TimeVal = i * 2.13
        iric.cg_iRIC_Write_Sol_Time_Mul(fid, TimeVal)

        iric.cg_iRIC_Write_Sol_Grid3d_Coords_Mul(fid, x, y, z)
        iric.cg_iRIC_Write_Sol_Node_Real_Mul(fid, "Depth", depth)
        iric.cg_iRIC_Write_Sol_Node_Real_Mul(fid, "VelocityX", vx)
        iric.cg_iRIC_Write_Sol_Node_Real_Mul(fid, "VelocityY", vy)

        iric.cg_iRIC_Write_Sol_Node_Integer_Mul(fid, "IBC", wet)

        Dist = i * - 0.2 + 20
        iric.cg_iRIC_Write_Sol_BaseIterative_Real_Mul(fid, "Discharge", Dist)
        DamOpen = i
        iric.cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(fid, "DamOpen", DamOpen)
        iric.cg_iRIC_Write_Sol_Particle_Pos3d_Mul(fid, particle_x, particle_y, particle_z)
        iric.cg_iRIC_Write_Sol_Particle_Real_Mul(fid, "VelX", particle_vx)
        iric.cg_iRIC_Write_Sol_Particle_Real_Mul(fid, "VelY", particle_vy)
        iric.cg_iRIC_Write_Sol_Particle_Real_Mul(fid, "VelZ", particle_vz)
        iric.cg_iRIC_Write_Sol_Particle_Integer_Mul(fid, "Active", particle_active)

        iric.cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(fid, "group1")
        for j in range(particle_num):
            iric.cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul(fid, particle_x[j], particle_y[j], particle_z[j])
            iric.cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(fid, "VelX", particle_vx[j])
            iric.cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(fid, "VelY", particle_vy[j])
            iric.cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(fid, "Active", int(particle_active[j]))

        iric.cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(fid)

        iric.cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(fid, "group2")
        for j in range(particle_num):
            iric.cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul(fid, particle_x[j], particle_y[j], 2)
            iric.cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(fid, "VelX", particle_vx[j] + 1)
            iric.cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(fid, "VelY", particle_vy[j] + 2)
            iric.cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(fid, "Active", int(particle_active[j]))

        iric.cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(fid)

        iric.cg_iRIC_Flush(filename, fid)

    return fid

def readSolution(fid):
    sol_count = iric.cg_iRIC_Read_Sol_Count_Mul(fid)
    util.verify_log("cg_iRIC_Read_Sol_Count_Mul() sol_count == 5", sol_count == 5)

    isize, jsize = iric.cg_iRIC_Read_Grid2d_Str_Size_Mul(fid)

    for S in range(1, sol_count + 1):
        # GridCoord

        x, y = iric.cg_iRIC_Read_Sol_Grid2d_Coords_Mul(fid, S)

        # Vertex solutions

        real_sol = iric.cg_iRIC_Read_Sol_Node_Real_Mul(fid, S, "Depth")
        msg = "cg_iRIC_Read_Sol_Node_Real_Mul() real_sol[0] == {0}".format(S - 1)
        util.verify_log(msg, real_sol[0] == S - 1)
        msg = "cg_iRIC_Read_Sol_Node_Real_Mul() real_sol[{0}] == {1}".format(real_sol.size - 1, S - 1)
        util.verify_log(msg, real_sol[real_sol.size - 1] == S - 1)

        int_sol = iric.cg_iRIC_Read_Sol_Node_Integer_Mul(fid, S, "IBC")
        msg = "cg_iRIC_Read_Sol_Node_Integer_Mul() int_sol[0] == {0}".format(S - 1)
        util.verify_log(msg, int_sol[0] == S - 1)
        msg = "cg_iRIC_Read_Sol_Node_Integer_Mul() int_sol[{0}] == {1}".format(int_sol.size - 1, S - 1)
        util.verify_log(msg, int_sol[int_sol.size - 1] == S - 1)

        # CellCenter solutions

        real_ccsol = iric.cg_iRIC_Read_Sol_Cell_Real_Mul(fid, S, "CCDepth")
        msg = "cg_iRIC_Read_Sol_Cell_Real_Mul() real_ccsol[0] == {0}".format(0.2 + (S - 1))
        util.verify_log(msg, real_ccsol[0] == 0.2 + (S - 1))
        msg = "cg_iRIC_Read_Sol_Cell_Real_Mul() real_ccsol[{0}] == {1}".format(real_ccsol.size - 1, 0.2 + (S - 1))
        util.verify_log(msg, real_ccsol[real_ccsol.size - 1] == 0.2 + (S - 1))

        int_ccsol = iric.cg_iRIC_Read_Sol_Cell_Integer_Mul(fid, S, "CCWet")
        msg = "cg_iRIC_Read_Sol_Cell_Integer_Mul() int_ccsol[0] == {0}".format(S)
        util.verify_log(msg, int_ccsol[0] == S)
        msg = "cg_iRIC_Read_Sol_Cell_Integer_Mul() int_ccsol[{0}] == {1}".format(int_ccsol.size - 1, S)
        util.verify_log(msg, int_ccsol[int_ccsol.size - 1] == S)

        # IFaceCenter solutions

        iface_is_edge = iric.cg_iRIC_Read_Sol_IFace_Integer_Mul(fid, S, "IFaceIsEdge")
        iface_is_edge_reals = iric.cg_iRIC_Read_Sol_IFace_Real_Mul(fid, S, "IFaceIsEdgeReals")

        # verify iface
        for j in range(jsize - 1):
            for i in range(isize):
                if j == 0 or j == (jsize - 2) or i == 0 or i == (isize - 1):
                    msg = "cg_iRIC_Read_Sol_IFace_Integer_Mul() iface_is_edge[{0}] == {1}".format(j * isize + i, 1)
                    util.verify_log(msg, iface_is_edge[j * isize + i] == 1)
                    msg = "cg_iRIC_Read_Sol_IFace_Integer_Mul() iface_is_edge[{0}] == {1}".format(j * isize + i, .1)
                    util.verify_log(msg, iface_is_edge_reals[j * isize + i] == .1)

        # JFaceCenter solutions

        jface_is_edge = iric.cg_iRIC_Read_Sol_JFace_Integer_Mul(fid, S, "JFaceIsEdge")
        jface_is_edge_reals = iric.cg_iRIC_Read_Sol_JFace_Real_Mul(fid, S, "JFaceIsEdgeReals")

        # verify jface
        for j in range(jsize):
            for i in range(isize - 1):
                if j == 0 or j == (jsize - 1) or i == 0 or i == (isize - 2):
                    msg = "cg_iRIC_Read_Sol_JFace_Integer_Mul() jface_is_edge[{0}] == {1}".format(j * (isize - 1) + i, 2)
                    util.verify_log(msg, jface_is_edge[j * (isize - 1) + i] == 2)
                    msg = "cg_iRIC_Read_Sol_IFace_Integer_Mul() jface_is_edge_reals[{0}] == {1}".format(j * (isize - 1) + i, .2)
                    util.verify_log(msg, jface_is_edge_reals[j * (isize - 1) + i] == .2)

        # BaseIterativeData

        d = iric.cg_iRIC_Read_Sol_BaseIterative_Real_Mul(fid, S, "Discharge")
        Dist = (S - 1) * -0.2 + 20

        msg = "cg_iRIC_Read_Sol_BaseIterative_Real_Mul() for Discharge d == {0}".format(Dist)
        util.verify_log(msg, d == Dist)

        i = iric.cg_iRIC_Read_Sol_BaseIterative_Integer_Mul(fid, S, "DamOpen")
        DamOpen = (S - 1)
        msg = "cg_iRIC_Read_Sol_BaseIterative_Integer_Mul() for DamOpen i == {0}".format(DamOpen)
        util.verify_log(msg, i == DamOpen)

        validVal = "Test{0}".format(S - 1)
        retval = iric.cg_iRIC_Read_Sol_BaseIterative_String_Mul(fid, S, "TestStr")
        msg = "cg_iRIC_Read_Sol_BaseIterative_String_Mul() for TestStr s == {0}".format(validVal)
        util.verify_log(msg, validVal == retval)

def case_SolWriteStd(cgnsName):
    util.remove("data/case_solstd.cgn")

    shutil.copy(cgnsName, "data/case_solstd.cgn")

    # Test Writing

    fid = iric.cg_iRIC_Open("data/case_solstd.cgn", iric.IRIC_MODE_MODIFY)
    util.verify_log("cg_iRIC_Open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    fid = writeSolution("data/case_solstd.cgn", fid, False)

    iric.cg_close(fid)

    # Test Reading with times

    fid = iric.cg_iRIC_Open("data/case_solstd.cgn", iric.IRIC_MODE_READ)
    util.verify_log("cg_iRIC_Open() fid != 0", fid != 0)

    iric.cg_iRIC_InitRead(fid)

    readSolution(fid)

    iric.cg_close(fid)

    # Test Writing 3D Standard (IRIC_OPTION_STDSOLUTION) with times

    shutil.copy(cgnsName, "data/case_solstd3d.cgn")

    fid = iric.cg_iRIC_Open("data/case_solstd3d.cgn", iric.IRIC_MODE_MODIFY)
    util.verify_log("cg_iRIC_Open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    fid = writeSolution3d("data/case_solstd3d.cgn", fid)

    iric.cg_close(fid)

    # Test Writing Standard (IRIC_OPTION_STDSOLUTION) with iterations

    shutil.copy(cgnsName, "data/case_solstditer.cgn")

    fid = iric.cg_iRIC_Open("data/case_solstditer.cgn", iric.IRIC_MODE_MODIFY)
    util.verify_log("cg_iRIC_Open() fid != 0", fid != 0)

    iric.cg_iRIC_Init(fid)

    fid = writeSolution("data/case_solstditer.cgn", fid, True)

    iric.cg_close(fid)

    # Test Reading Standard (IRIC_OPTION_STDSOLUTION) with iterations

    fid = iric.cg_iRIC_Open("data/case_solstditer.cgn", iric.IRIC_MODE_READ)
    util.verify_log("cg_iRIC_Open() fid != 0", fid != 0)

    iric.cg_iRIC_InitRead(fid)

    readSolution(fid)
    iric.cg_close(fid)

    util.remove("data/case_solstditer.cgn")

def case_SolWriteStd_adf():
    case_SolWriteStd("data/case_init.cgn")

def case_SolWriteStd_hdf5():
    case_SolWriteStd("data/case_init_hdf5.cgn")
