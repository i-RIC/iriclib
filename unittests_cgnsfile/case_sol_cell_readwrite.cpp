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

void case_read_adf()
{
	int fid;
	int ier = cg_iRIC_Open("case_read_adf.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	int sol_count;
	ier = cg_iRIC_Read_Sol_Count_Mul(fid, &sol_count);
	VERIFY_LOG("cg_iRIC_Read_Sol_Count_Mul() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Sol_Count_Mul() sol_count == 3", sol_count == 3);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);
}

void case_read_hdf5()
{
	int fid;
	int ier = cg_iRIC_Open("case_read_hdf5.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == 0", ier == 0);

	int sol_count;
	ier = cg_iRIC_Read_Sol_Count_Mul(fid, &sol_count);
	VERIFY_LOG("cg_iRIC_Read_Sol_Count_Mul() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Sol_Count_Mul() sol_count == 3", sol_count == 3);

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);
}

void case_read_adf_no_results()
{
	int fid;
	int ier = cg_iRIC_Open("case_read_adf_no_sols.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == IRIC_NO_ERROR", ier == IRIC_NO_ERROR);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);


	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == IRIC_NO_ERROR", ier == IRIC_NO_ERROR);
	/*
	const char exp1[] = "index 1, label 'BaseIterativeData_t' not a child of 'CGNSBase_t'";
	const char *err1 = cg_get_error();
	char buffer[200];
	sprintf(buffer, "cg_get_error() == '%s'", exp1);
	VERIFY_LOG(buffer, strcmp(err1, exp1) == 0);
	*/


	// emulate PostTimeSteps::loadFromCgnsFile
	int B;
	char name[33];
	int nsteps;
	ier = cg_iRIC_GotoBase(fid, &B);
	VERIFY_LOG("cg_iRIC_GotoBase() ier == 0", ier == 0);
/*
	ier = cg_biter_read(fid, B, name, &nsteps);
	VERIFY_LOG("cg_biter_read() ier == CG_NODE_NOT_FOUND", ier == CG_NODE_NOT_FOUND);
	
	const char exp2[] = "BaseIterativeData_t node doesn't exist under CGNSBase 1";
	const char *err2 = cg_get_error();
	char buffer[200];
	sprintf(buffer, "cg_get_error() == '%s'", exp2);
	VERIFY_LOG(buffer, strcmp(err2, exp2) == 0);
*/

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);
}

void case_read_hdf5_no_results()
{
	int fid;
	int ier = cg_iRIC_Open("case_read_hdf5_no_sols.cgn", IRIC_MODE_READ, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == IRIC_NO_ERROR", ier == IRIC_NO_ERROR);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);


	ier = cg_iRIC_InitRead(fid);
	VERIFY_LOG("cg_iRIC_InitRead() ier == IRIC_NO_ERROR", ier == IRIC_NO_ERROR);
	/*
	const char exp1[] = "index 1, label 'BaseIterativeData_t' not a child of 'CGNSBase_t'";
	const char *err1 = cg_get_error();
	char buffer[200];
	sprintf(buffer, "cg_get_error() == '%s'", exp1);
	VERIFY_LOG(buffer, strcmp(err1, exp1) == 0);
	*/

	// emulate PostTimeSteps::loadFromCgnsFile
	int B;
	char name[33];
	int nsteps;
	ier = cg_iRIC_GotoBase(fid, &B);
	VERIFY_LOG("cg_iRIC_GotoBase() ier == 0", ier == 0);

	/*
	ier = cg_biter_read(fid, B, name, &nsteps);
	VERIFY_LOG("cg_biter_read() ier == CG_NODE_NOT_FOUND", ier == CG_NODE_NOT_FOUND);
	const char exp2[] = "BaseIterativeData_t node doesn't exist under CGNSBase 1";
	const char *err2 = cg_get_error();
	char buffer[200];
	sprintf(buffer, "cg_get_error() == '%s'", exp2);
	VERIFY_LOG(buffer, strcmp(err2, exp2) == 0);
*/

	ier = cg_iRIC_Close(fid);
	VERIFY_LOG("cg_iRIC_Close() ier == 0", ier == 0);
}


} // extern "C"
