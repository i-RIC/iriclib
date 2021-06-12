#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>
#include <vector>

extern "C" {

void case_GridRead()
{
	fs::copy("case_init_hdf5.cgn", "case_grid.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_grid.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	int isize, jsize;
	int count;
	std::vector<double> x, y;

	ier = cg_iRIC_Read_Grid2d_Str_Size(fid, &isize, &jsize);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() isize == 11", isize == 11);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() jsize == 11", jsize == 11);

	ier = cg_iRIC_Read_Grid_NodeCount(fid, &count);
	VERIFY_LOG("cg_iRIC_Read_Grid_NodeCount() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_NodeCount() count == 121", count == 121);

	ier = cg_iRIC_Read_Grid_CellCount(fid, &count);
	VERIFY_LOG("cg_iRIC_Read_Grid_CellCount() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_CellCount() count == 100", count == 100);

	ier = cg_iRIC_Read_Grid_IFaceCount(fid, &count);
	VERIFY_LOG("cg_iRIC_Read_Grid_IFaceCount() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_IFaceCount() count == 110", count == 110);

	ier = cg_iRIC_Read_Grid_JFaceCount(fid, &count);
	VERIFY_LOG("cg_iRIC_Read_Grid_JFaceCount() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_JFaceCount() count == 110", count == 110);

	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);

	ier = cg_iRIC_Read_Grid2d_Coords(fid, x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() ier == 0", ier == 0);

	std::vector<double> doubleArr;
	std::vector<int> intArr;

	doubleArr.assign(isize * jsize, 0);
	intArr.assign(isize * jsize, 0);

	ier = cg_iRIC_Read_Grid_Real_Node(fid, "node_real", doubleArr.data());
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[0] == 2", doubleArr[0] == 2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[1] == 2", doubleArr[1] == 2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[2] == 2", doubleArr[2] == 2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[3] == 2", doubleArr[3] == 2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[4] == 2", doubleArr[4] == 2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[5] == 2", doubleArr[5] == 2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[6] == 2", doubleArr[6] == 2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[7] == 0", doubleArr[7] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[8] == 0", doubleArr[8] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Node() value[9] == 0", doubleArr[9] == 0);

	ier = cg_iRIC_Read_Grid_Integer_Node(fid, "node_int", intArr.data());
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[0] == 0", intArr[0] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[1] == 0", intArr[1] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[2] == 0", intArr[2] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[3] == 0", intArr[3] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[4] == 0", intArr[4] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[5] == 1", intArr[5] == 1);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[6] == 1", intArr[6] == 1);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[7] == 1", intArr[7] == 1);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[8] == 1", intArr[8] == 1);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Node() value[9] == 1", intArr[9] == 1);

	doubleArr.assign((isize - 1) * (jsize - 1), 0);
	intArr.assign((isize - 1) * (jsize - 1), 0);

	ier = cg_iRIC_Read_Grid_Real_Cell(fid, "cell_real", doubleArr.data());
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Cell() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Cell() value[0] == 4.2", doubleArr[0] == 4.2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Cell() value[1] == 4.2", doubleArr[1] == 4.2);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Cell() value[2] == 0", doubleArr[2] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Real_Cell() value[3] == 0", doubleArr[3] == 0);

	ier = cg_iRIC_Read_Grid_Integer_Cell(fid, "cell_int", intArr.data());
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Cell() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Cell() value[0] == 0", intArr[0] == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Cell() value[15] == 1", intArr[15] == 1);
	VERIFY_LOG("cg_iRIC_Read_Grid_Integer_Cell() value[16] == 0", intArr[16] == 0);

	int grid_handle;
	ier = cg_iRIC_Read_Grid2d_Open(fid, &grid_handle);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Open() ier == 0", ier == 0);

	double area;
	ier = cg_iRIC_Read_Grid2d_CellArea(grid_handle, 1, &area);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_CellArea() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_CellArea() area == 0.017", std::abs(area - 0.0173) < 0.0001);

	int cellNodeCount;
	ier = cg_iRIC_Read_Grid2d_CellNodeCount(grid_handle, 1, &cellNodeCount);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_CellNodeCount() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_CellNodeCount() cellNodeCount == 4", cellNodeCount == 4);

	int nodeIds[4];
	double weights[4];
	int ok;
	int nodeCount;
	ier = cg_iRIC_Read_Grid2d_Interpolate(grid_handle, 0.0, 0.0, &ok, &nodeCount, nodeIds, weights);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() ok == 1", ok == 1);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeCount == 4", nodeCount == 4);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeIds[0] == 93", nodeIds[0] == 93);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeIds[1] == 94", nodeIds[1] == 94);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeIds[2] == 105", nodeIds[2] == 105);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeIds[3] == 104", nodeIds[3] == 104);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() weights[0] == 0.3863", std::abs(weights[0] - 0.3863) < 0.0001);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() weights[1] == 0.4012", std::abs(weights[1] - 0.4012) < 0.0001);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() weights[2] == 0.2123", std::abs(weights[2] - 0.2123) < 0.0001);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() weights[3] == 0", std::abs(weights[3] - 0) < 0.0001);

	ier = cg_iRIC_Read_Grid2d_Close(grid_handle);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Close() ier == 0", ier == 0);

	cg_iRIC_Close(fid);

	remove("case_grid.cgn");
}

void case_GridReadUnstructured()
{
	fs::copy("case_unst_hdf5.cgn", "case_grid_unstructured.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_grid_unstructured.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	int elem_size;
	int count;
	std::vector<double> x, y;
	std::vector<int> elems;

	ier = cg_iRIC_Read_Grid_TriangleElementsSize(fid, &elem_size);
	VERIFY_LOG("cg_iRIC_Read_Grid_TriangleElementsSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_TriangleElementsSize() elem_size == 3", elem_size == 3);

	ier = cg_iRIC_Read_Grid_NodeCount(fid, &count);
	VERIFY_LOG("cg_iRIC_Read_Grid_NodeCount() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_NodeCount() count == 5", count == 5);

	x.assign(count, 0);
	y.assign(count, 0);
	elems.assign(elem_size * 3, 0);

	ier = cg_iRIC_Read_Grid2d_Coords(fid, x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() ier == 0", ier == 0);

	ier = cg_iRIC_Read_Grid_TriangleElements(fid, elems.data());
	VERIFY_LOG("cg_iRIC_Read_Grid_TriangleElements() ier == 0", ier == 0);

	int grid_handle;
	ier = cg_iRIC_Read_Grid2d_Open(fid, &grid_handle);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Open() ier == 0", ier == 0);

	double area;
	ier = cg_iRIC_Read_Grid2d_CellArea(grid_handle, 1, &area);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_CellArea() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_CellArea() area == 0.2067", std::abs(area - 0.2067) < 0.0001);

	int cellNodeCount;
	ier = cg_iRIC_Read_Grid2d_CellNodeCount(grid_handle, 1, &cellNodeCount);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_CellNodeCount() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_CellNodeCount() cellNodeCount == 3", cellNodeCount == 3);

	int nodeIds[3];
	double weights[3];
	int ok;
	int nodeCount;
	ier = cg_iRIC_Read_Grid2d_Interpolate(grid_handle, 0.0, 0.0, &ok, &nodeCount, nodeIds, weights);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() ok == 1", ok == 1);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeCount == 3", nodeCount == 3);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeIds[0] == 4", nodeIds[0] == 4);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeIds[1] == 5", nodeIds[1] == 5);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() nodeIds[2] == 2", nodeIds[2] == 2);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() weights[0] == 0.5415", std::abs(weights[0] - 0.5415) < 0.0001);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() weights[1] == 0.0921", std::abs(weights[1] - 0.0921) < 0.0001);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Interpolate() weights[2] == 0.3663", std::abs(weights[2] - 0.3663) < 0.0001);

	ier = cg_iRIC_Read_Grid2d_Close(grid_handle);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Close() ier == 0", ier == 0);

	cg_iRIC_Close(fid);

	remove("case_grid_unstructured.cgn");
}

void case_GridReadFunc()
{
	fs::copy("case_gridfunc.cgn", "case_gridreadfunc.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_gridreadfunc.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	int isize, jsize;
	std::vector<double> x, y;

	ier = cg_iRIC_Read_Grid2d_Str_Size(fid, &isize, &jsize);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() isize == 15", isize == 15);
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() jsize == 15", jsize == 15);

	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);

	ier = cg_iRIC_Read_Grid2d_Coords(fid, x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Read_Grid2d_Str_Size() ier == 0", ier == 0);

	int time_count;
	ier = cg_iRIC_Read_Grid_FunctionalDimensionSize(fid, "Xrain", "Time", &time_count);
	VERIFY_LOG("cg_iRIC_Read_Grid_FunctionalDimensionSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Grid_FunctionalDimensionSize() time_count == 24", time_count == 24);

	std::vector<double> timeArr;
	timeArr.assign(time_count, 0);
	ier = cg_iRIC_Read_Grid_FunctionalDimension_Real(fid, "Xrain", "Time", timeArr.data());
	VERIFY_LOG("cg_iRIC_Read_Grid_FunctionalDimension_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Read_Grid_FunctionalTime(fid, "Xrain", timeArr.data());
	VERIFY_LOG("cg_iRIC_Read_Grid_FunctionalTime() ier == 0", ier == 0);

	std::vector<double> rain;
	rain.assign(isize * jsize, 0);

	for (int i = 0; i < timeArr.size(); ++i) {
		ier = cg_iRIC_Read_Grid_Functional_Real_Node(fid, "Xrain", i + 1, rain.data());
		VERIFY_LOG("cg_iRIC_Read_Grid_Functional_Real_Node() ier == 0", ier == 0);
	}

	cg_iRIC_Close(fid);

	remove("case_gridreadfunc.cgn");
}

void case_GridWrite()
{
	fs::copy("case_nogrid_hdf5.cgn", "case_gridwrite1d.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_gridwrite1d.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	int isize, jsize, ksize;
	std::vector<double> x, y, z;

	isize = 10;
	x.assign(isize, 0);

	for (int i = 0; i < isize; ++i) {
		x[i] = i * 2;
	}
	ier = cg_iRIC_Write_Grid1d_Coords(fid, isize, x.data());
	VERIFY_LOG("cg_iRIC_Write_Grid1d_Coords() ier == 0", ier == 0);

	cg_iRIC_Close(fid);

	ier = cg_iRIC_Open("case_gridwrite1d.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	/*
	ier = cg_goto(fid, 2, "iRICZone", 0, "GridCoordinates", 0, NULL);
	VERIFY_LOG("cg_goto() ier == 0", ier == 0);
	int dim;
	char name[32];
	DataType_t datatype;
	cgsize_t dimVec[12];
	ier = cg_array_info(1, name, &datatype, &dim, dimVec);
	VERIFY_LOG("cg_array_info() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_info() name == CoordinateX", std::string("CoordinateX") == name);
	VERIFY_LOG("cg_array_info() datatype == RealDouble", datatype == RealDouble);
	VERIFY_LOG("cg_array_info() dim == 1", dim == 1);
	VERIFY_LOG("cg_array_info() dimVec[0] == 10", dimVec[0] == 10);

	std::vector<double> read_x, read_y, read_z;
	read_x.assign(dimVec[0], 0);
	ier = cg_array_read(1, read_x.data());
	VERIFY_LOG("cg_array_read() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_read() value valid", x == read_x);
	*/

	cg_iRIC_Close(fid);

	remove("case_gridwrite1d.cgn");

	fs::copy("case_nogrid_hdf5.cgn", "case_gridwrite2d.cgn");

	ier = cg_iRIC_Open("case_gridwrite2d.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	isize = 10; jsize = 8;
	x.assign(isize * jsize, 0);
	y.assign(isize * jsize, 0);

	for (int j = 0; j < jsize; ++j) {
		for (int i = 0; i < isize; ++i) {
			x[i + isize * j] = i;
			y[i + isize * j] = j;
		}
	}
	ier = cg_iRIC_Write_Grid2d_Coords(fid, isize, jsize, x.data(), y.data());
	VERIFY_LOG("cg_iRIC_Write_Grid2d_Coords() ier == 0", ier == 0);

	std::vector<double> real_node_write, real_cell_write;
	std::vector<int> int_node_write, int_cell_write;

	real_node_write.assign(isize * jsize, 0);
	int_node_write.assign(isize * jsize, 0);
	real_cell_write.assign((isize - 1) * (jsize - 1), 0);
	int_cell_write.assign((isize - 1) * (jsize - 1), 0);

	for (int i = 0; i < real_node_write.size(); ++i) {
		real_node_write[i] = 0.5 * i - 0.001 * i * (i - 50);
	}

	for (int i = 0; i < int_node_write.size(); ++i) {
		int_node_write[i] = i * i + i * 2 + 6;
	}

	for (int i = 0; i < real_cell_write.size(); ++i) {
		real_cell_write[i] = 0.8 * i - 0.0005 * i * (i - 10);
	}

	for (int i = 0; i < int_cell_write.size(); ++i) {
		int_cell_write[i] = i * i - i * 4 + 414;
	}

	ier = cg_iRIC_Write_Grid_Real_Node(fid, "realnode_test", real_node_write.data());
	VERIFY_LOG("cg_iRIC_Write_Grid_Real_Node() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Grid_Integer_Node(fid, "intnode_test", int_node_write.data());
	VERIFY_LOG("cg_iRIC_Write_Grid_Integer_Node() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Grid_Real_Cell(fid, "realcell_test", real_cell_write.data());
	VERIFY_LOG("cg_iRIC_Write_Grid_Real_Cell() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Grid_Integer_Cell(fid, "intcell_test", int_cell_write.data());
	VERIFY_LOG("cg_iRIC_Write_Grid_Integer_Cell() ier == 0", ier == 0);

	cg_iRIC_Close(fid);

	ier = cg_iRIC_Open("case_gridwrite2d.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	/*
	cgsize_t size[9];
	ier = cg_zone_read(fid, 1, 1, name, size);
	VERIFY_LOG("cg_zone_read() ier == 0", ier == 0);
	VERIFY_LOG("cg_zone_read() name == iRICZone", strcmp(name, "iRICZone") == 0);
	VERIFY_LOG("cg_zone_read() size[0] == isize",   size[0] == isize);
	VERIFY_LOG("cg_zone_read() size[1] == jsize",   size[1] == jsize);
	VERIFY_LOG("cg_zone_read() size[2] == isize-1", size[2] == isize-1);
	VERIFY_LOG("cg_zone_read() size[3] == jsize-1", size[3] == jsize-1);
	VERIFY_LOG("cg_zone_read() size[4] == 0",       size[4] == 0);
	VERIFY_LOG("cg_zone_read() size[5] == 0",       size[5] == 0);

	ier = cg_goto(fid, 1, "iRICZone", 0, "GridCoordinates", 0, NULL);
	VERIFY_LOG("cg_goto() ier == 0", ier == 0);
	ier = cg_array_info(1, name, &datatype, &dim, dimVec);
	VERIFY_LOG("cg_array_info() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_info() name == CoordinateX", std::string("CoordinateX") == name);
	VERIFY_LOG("cg_array_info() datatype == RealDouble", datatype == RealDouble);

	read_x.assign(dimVec[0] * dimVec[1], 0);
	read_y.assign(dimVec[0] * dimVec[1], 0);

	ier = cg_array_read(1, read_x.data());
	VERIFY_LOG("cg_array_read() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_read() value valid", x == read_x);

	ier = cg_array_read(2, read_y.data());
	VERIFY_LOG("cg_array_read() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_read() value valid", y == read_y);

	ier = cg_goto(fid, 1, "iRICZone", 0, "GridConditions", 0, "realnode_test", 0, NULL);
	VERIFY_LOG("cg_goto() for realnode_test ier == 0", ier == 0);
	ier = cg_array_info(1, name, &datatype, &dim, dimVec);
	std::vector<double> real_node_read;
	real_node_read.assign(dimVec[0], 0);
	ier = cg_array_read(1, real_node_read.data());
	VERIFY_LOG("cg_array_read() for realnode_test ier == 0", ier == 0);
	VERIFY_LOG("realnode_test value check", real_node_read == real_node_write);

	ier = cg_goto(fid, 1, "iRICZone", 0, "GridConditions", 0, "intnode_test", 0, NULL);
	VERIFY_LOG("cg_goto() for intnode_test ier == 0", ier == 0);
	ier = cg_array_info(1, name, &datatype, &dim, dimVec);
	std::vector<int> int_node_read;
	int_node_read.assign(dimVec[0], 0);
	ier = cg_array_read(1, int_node_read.data());
	VERIFY_LOG("cg_array_read() for intnode_test ier == 0", ier == 0);
	VERIFY_LOG("intnode_test value check", int_node_read == int_node_write);

	ier = cg_goto(fid, 1, "iRICZone", 0, "GridConditions", 0, "realcell_test", 0, NULL);
	VERIFY_LOG("cg_goto() for realcell_test ier == 0", ier == 0);
	ier = cg_array_info(1, name, &datatype, &dim, dimVec);
	std::vector<double> real_cell_read;
	real_cell_read.assign(dimVec[0], 0);
	ier = cg_array_read(1, real_cell_read.data());
	VERIFY_LOG("cg_array_read() for realcell_test ier == 0", ier == 0);
	VERIFY_LOG("realcell_test value check", real_cell_read == real_cell_write);

	ier = cg_goto(fid, 1, "iRICZone", 0, "GridConditions", 0, "intcell_test", 0, NULL);
	VERIFY_LOG("cg_goto() for intcell_test ier == 0", ier == 0);
	ier = cg_array_info(1, name, &datatype, &dim, dimVec);
	std::vector<int> int_cell_read;
	int_cell_read.assign(dimVec[0], 0);
	ier = cg_array_read(1, int_cell_read.data());
	VERIFY_LOG("cg_array_read() for intcell_test ier == 0", ier == 0);
	VERIFY_LOG("intcell_test value check", int_cell_read == int_cell_write);
	*/

	cg_iRIC_Close(fid);

	remove("case_gridwrite2d.cgn");

	fs::copy("case_nogrid_hdf5.cgn", "case_gridwrite3d.cgn");

	ier = cg_iRIC_Open("case_gridwrite3d.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	isize = 11; jsize = 9; ksize = 5;
	x.assign(isize * jsize * ksize, 0);
	y.assign(isize * jsize * ksize, 0);
	z.assign(isize * jsize * ksize, 0);

	for (int k = 0; k < ksize; ++k) {
		for (int j = 0; j < jsize; ++j) {
			for (int i = 0; i < isize; ++i) {
				x[i + isize * j + isize * jsize * k] = i;
				y[i + isize * j + isize * jsize * k] = j;
				z[i + isize * j + isize * jsize * k] = k;
			}
		}
	}
	ier = cg_iRIC_Write_Grid3d_Coords(fid, isize, jsize, ksize, x.data(), y.data(), z.data());
	VERIFY_LOG("cg_iRIC_Write_Grid3d_Coords() ier == 0", ier == 0);

	cg_iRIC_Close(fid);

	ier = cg_iRIC_Open("case_gridwrite3d.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	/*
	ier = cg_zone_read(fid, 2, 1, name, size);
	VERIFY_LOG("cg_zone_read() ier == 0", ier == 0);
	VERIFY_LOG("cg_zone_read() name == iRICZone", strcmp(name, "iRICZone") == 0);
	VERIFY_LOG("cg_zone_read() size[0] == isize",   size[0] == isize);
	VERIFY_LOG("cg_zone_read() size[1] == jsize",   size[1] == jsize);
	VERIFY_LOG("cg_zone_read() size[2] == ksize",   size[2] == ksize);
	VERIFY_LOG("cg_zone_read() size[3] == isize-1", size[3] == isize-1);
	VERIFY_LOG("cg_zone_read() size[4] == jsize-1", size[4] == jsize-1);
	VERIFY_LOG("cg_zone_read() size[5] == ksize-1", size[5] == ksize-1);
	VERIFY_LOG("cg_zone_read() size[6] == 0",       size[6] == 0);
	VERIFY_LOG("cg_zone_read() size[7] == 0",       size[7] == 0);
	VERIFY_LOG("cg_zone_read() size[8] == 0",       size[8] == 0);

	ier = cg_goto(fid, 2, "iRICZone", 0, "GridCoordinates", 0, NULL);
	VERIFY_LOG("cg_goto() ier == 0", ier == 0);
	ier = cg_array_info(1, name, &datatype, &dim, dimVec);
	VERIFY_LOG("cg_array_info() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_info() name == CoordinateX", std::string("CoordinateX") == name);
	VERIFY_LOG("cg_array_info() datatype == RealDouble", datatype == RealDouble);

	read_x.assign(dimVec[0] * dimVec[1] * dimVec[2], 0);
	read_y.assign(dimVec[0] * dimVec[1] * dimVec[2], 0);
	read_z.assign(dimVec[0] * dimVec[1] * dimVec[2], 0);

	ier = cg_array_read(1, read_x.data());
	VERIFY_LOG("cg_array_read() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_read() value valid", x == read_x);

	ier = cg_array_read(2, read_y.data());
	VERIFY_LOG("cg_array_read() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_read() value valid", y == read_y);

	ier = cg_array_read(3, read_z.data());
	VERIFY_LOG("cg_array_read() ier == 0", ier == 0);
	VERIFY_LOG("cg_array_read() value valid", z == read_z);
	*/

	cg_iRIC_Close(fid);

	remove("case_gridwrite3d.cgn");
}

} // extern "C"
