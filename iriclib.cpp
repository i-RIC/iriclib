#include "error_macros.h"
#include "filelocker.h"
#include "iriclib.h"
#include "iriclib_cgnsfile.h"
#include "iriclib_cgnsfiles.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#if defined(_MSC_VER)
#define unlink _unlink   // warning C4996
#else
#define _stat stat
#include <unistd.h>  // unlink
#endif

#define GET_F(id) if (id >= m_files.size()){return 98;};iRICLib::CgnsFile* f = m_files.at(id);if (f == nullptr){return 99;}
#define GET_F_VOID(id) iRICLib::CgnsFile* f = m_files.at(id);if (f == nullptr){return;}

extern "C" {

int lastfileid = 0;

} // extern "C"

namespace {

const int FILES_LEN_UNIT = 10;
iRICLib::CgnsFiles m_files;
std::map<std::string, FileLocker*> m_fileLockers;
bool m_divideSolutions = true;

const char* flush_filename() {
	return ".flush";
}

void initFilesFor(int fid)
{
	if (fid < m_files.size()) {
		return;
	}

	int newLength = (fid / FILES_LEN_UNIT + 1) * FILES_LEN_UNIT;
	std::vector<iRICLib::CgnsFile*> newFiles;
	newFiles.assign(newLength, nullptr);
	for (int i = 0; i < m_files.size(); ++i) {
		newFiles[i] = m_files[i];
	}
	m_files = newFiles;
}

iRICLib::CgnsFile* initCgnsFile(int fid)
{
	initFilesFor(fid);
	iRICLib::CgnsFile* f = m_files.at(fid);
	if (f != nullptr) {
		delete f;
	}
	f = new iRICLib::CgnsFile();
	f->setFileId(fid);
	if (m_divideSolutions) {
		f->OptionDivideSolutions();
	}
	m_files[fid] = f;

	lastfileid = fid;
	return f;
}

std::string lock_filename(const char* filename)
{
	std::string lockfilename(filename);
	lockfilename.append(".lock");

	return lockfilename;
}

FileLocker& getFileLocker(const char* cgnsFileName)
{
	std::string lockFileName = lock_filename(cgnsFileName);
	std::map<std::string, FileLocker*>::iterator it = m_fileLockers.find(lockFileName);
	if (it != m_fileLockers.end()) {
		return *(it->second);
	}
	FileLocker* newLocker = new FileLocker(lockFileName);
	std::pair<std::map<std::string, FileLocker*>::iterator, bool> result =
			m_fileLockers.insert({lockFileName, newLocker});
	it = result.first;
	return *(it->second);
}

int check_flush_request()
{
	int result;
	struct _stat buf;

	result = _stat(flush_filename(), &buf);

	if (result == 0){
		// Getting information. succeeded. flush file exist.
		std::ifstream f(flush_filename());
		int flushIndex;
		f >> flushIndex;

		return flushIndex;
	}
	return 0;
}

void update_flushfile()
{
	std::ofstream f(flush_filename());
	f << "copying" << std::endl;
	f.close();
}

void unlink_flushfile()
{
	unlink(flush_filename());
}

bool copy(const char* src, const char* dst)
{
	FILE *fpr = fopen(src, "rb");
	FILE *fpw = fopen(dst, "wb");

	std::vector<char> buffer( 1024*1024 );
	while(! feof(fpr))
	{
		size_t size = fread( &buffer[0], 1, buffer.size(), fpr );
		fwrite( &buffer[0], 1, size, fpw );
	}
	fclose(fpr);
	fclose(fpw);

	return true;
}

} // namespace

extern "C" {

int cg_iRIC_Init(int fid)
{
	iRICLib::CgnsFile* f = initCgnsFile(fid);
	return f->Init();
}

int cg_iRIC_WriteBase(int fid)
{
	iRICLib::CgnsFile* f = initCgnsFile(fid);
	return f->WriteBase();
}

int cg_iRIC_InitRead_Base(int fid, const char* bname)
{
	iRICLib::CgnsFile* f = initCgnsFile(fid);
	return f->InitRead_Base(bname);
}

int cg_iRIC_InitRead(int fid)
{
	iRICLib::CgnsFile* f = initCgnsFile(fid);
	return f->InitRead();
}

void cg_iRIC_SetFilename(int fid, const char* fname)
{
	GET_F_VOID(fid);
	f->setFileName(fname);
}

int iRIC_InitOption(int option)
{
	FILE* fp;
	if (option == IRIC_OPTION_CANCEL){
		// create ".cancel_ok"
		fp = fopen(".cancel_ok", "w");
		if (fp == NULL){
			// failed opening.
			return 1;
		}
		// close file.
		fclose(fp);
	} else if (option == IRIC_OPTION_DIVIDESOLUTIONS){
		m_divideSolutions = true;
	} else if (option == IRIC_OPTION_STDSOLUTION) {
		m_divideSolutions = false;
	}
	return 0;
}

int cg_iRIC_Flush(const char* filename, int* fid){
	GET_F(*fid);
	int ier = f->Flush();
	RETURN_IF_ERR;

	return 0;
/*
	int flushIndex = check_flush_request();
	if (flushIndex == 0) {
		// flushing is not requested
		return 0;
	}

	update_flushfile();

	// close the CGNS file first.
	ier = cg_close(*fid);
	RETURN_IF_ERR;

	m_files[*fid] = nullptr;

	// copy the CGNS file
	std::ostringstream oss;
	oss << "result/output.copy" << flushIndex << ".cgn";
	std::string copyedFile = oss.str();
	bool ok = copy(filename, copyedFile.c_str());
	if (! ok) {
		std::cout << "Copy operation in flushing failed" << std::endl;
	}

	// open the file again
	ier = cg_open(filename, CG_MODE_MODIFY, fid);
	RETURN_IF_ERR;

	lastfileid = *fid;

	initFilesFor(*fid);
	f->setFileId(*fid);
	m_files[*fid] = f;

	unlink_flushfile();
	return 0;
*/
}

int cg_iRIC_GotoBase(int fid, int* B){
	iRICLib::CgnsFile* f = initCgnsFile(fid);
	return f->GotoBase(B);
}

int cg_iRIC_GotoCC(int fid){
	iRICLib::CgnsFile* f = initCgnsFile(fid);
	return f->GotoCC();
}

int cg_iRIC_GotoRawDataTop(int fid)
{
	iRICLib::CgnsFile* f = initCgnsFile(fid);
	return f->GotoRawDataTop();
}

int cg_iRIC_Set_ZoneId_Mul(int fid, int zid)
{
	GET_F(fid);
	return f->Set_ZoneId(zid);
}

int iRIC_Write_Sol_Start(const char* filename)
{
	/*
	FileLocker& locker = getFileLocker(filename);

	bool result = locker.lock();
	if (! result) {return 1;}
	*/

	return 0;
}

int iRIC_Write_Sol_End(const char* filename)
{
	/*
	FileLocker& locker = getFileLocker(filename);

	locker.unlock();
	*/

	return 0;
}

int iRIC_Check_Lock(const char* filename)
{
	// iRIC_Check_Lock() do nothing now, because it does not need
	// to do any more.
	//
	// In the previous implementation, solver had to call iRIC_Check_Lock()
	// and if it returned IRIC_LOCKED, the solver needed to sleep manually,
	// until it returns 0.
	//
	// But in the new implementation of iRIC_Write_Sol_Start(), it
	// waits automatically until the GUI unlock the lock file,
	// so the solver do not need iRIC_Check_Lock for sleeping.

	return 0;
}

int iRIC_Check_Cancel()
{
	const char* cancelfilename = ".cancel";
	int result;
	struct _stat buf;

	result = _stat(cancelfilename, &buf);

	if (result == 0){
		// Getting information. succeeded. Cancel file exist. Exits running.
		std::cout << "Solver is stopped because the STOP button was clicked." << std::endl;
		exit(0);
	}

	// not canceled.
	return 0;
}

int cg_iRIC_Link_Solutions(int fid, int* progress, int* invaliddata_id)
{
	GET_F(fid);
	return f->LinkSolutions(progress, invaliddata_id);
}

int cg_iRIC_Combine_Solutions(int fid, int* progress, int* invaliddata_id, int maxid)
{
	GET_F(fid);
	return f->CombineSolutions(progress, invaliddata_id, maxid);
}

int cg_iRIC_Read_Integer_Mul(int fid, const char* name, int* intvalue){
	GET_F(fid);
	return f->CC_Read_Integer(name, intvalue);
}

int cg_iRIC_Read_Real_Mul(int fid, const char* name, double* realvalue){
	GET_F(fid);
	return f->CC_Read_Real(name, realvalue);
}

int cg_iRIC_Read_RealSingle_Mul(int fid, const char* name, float* realvalue){
	GET_F(fid);
	return f->CC_Read_RealSingle(name, realvalue);
}

int cg_iRIC_Read_StringLen_Mul(int fid, const char* name, int* length){
	GET_F(fid);
	return f->CC_Read_StringLen(name, length);
}

int cg_iRIC_Read_String_Mul(int fid, const char* name, char* strvalue){
	GET_F(fid);
	return f->CC_Read_String(name, strvalue);
}

int cg_iRIC_Read_FunctionalSize_Mul(int fid, const char* name, cgsize_t* size)
{
	GET_F(fid);
	return f->CC_Read_FunctionalSize(name, size);
}

int cg_iRIC_Read_Functional_Mul(int fid, const char* name, double* x, double* y){
	GET_F(fid);
	return f->CC_Read_Functional(name, x, y);
}

int cg_iRIC_Read_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, double* data)
{
	GET_F(fid);
	return f->CC_Read_FunctionalWithName(name, paramname, data);
}

int cg_iRIC_Read_Functional_RealSingle_Mul(int fid, const char* name, float* x, float* y){
	GET_F(fid);
	return f->CC_Read_Functional_RealSingle(name, x, y);
}

int cg_iRIC_Read_FunctionalWithName_RealSingle_Mul(int fid, const char* name, const char* paramname, float* data){
	GET_F(fid);
	return f->CC_Read_FunctionalWithName_RealSingle(name, paramname, data);
}

int cg_iRIC_Read_FunctionalWithName_String_Mul(int fid, const char* name, const char* paramname, char* strvalue){
	GET_F(fid);
	return f->CC_Read_FunctionalWithName_String(name, paramname, strvalue);
}

int cg_iRIC_Read_FunctionalWithName_StringLen_Mul(int fid, const char* name, const char* paramname, int* length){
	GET_F(fid);
	return f->CC_Read_FunctionalWithName_StringLen(name, paramname, length);
}

int cg_iRIC_Write_Integer_Mul(int fid, const char* name, int intvalue){
	GET_F(fid);
	return f->CC_Write_Integer(name, intvalue);
}

int cg_iRIC_Write_Real_Mul(int fid, const char* name, double realvalue){
	GET_F(fid);
	return f->CC_Write_Real(name, realvalue);
}

int cg_iRIC_Write_String_Mul(int fid, const char* name, const char* strvalue){
	GET_F(fid);
	return f->CC_Write_String(name, strvalue);
}

int cg_iRIC_Write_Functional_Mul(int fid, const char* name, int length, double* realarray_x, double* realarray_y){
	GET_F(fid);
	return f->CC_Write_Functional(name, length, realarray_x, realarray_y);
}

int cg_iRIC_Write_FunctionalWithName_Mul(int fid, const char* name, const char* paramname, int length, double* data)
{
	GET_F(fid);
	return f->CC_Write_FunctionalWithName(name, paramname, length, data);
}

int cg_iRIC_Write_FunctionalWithName_String_Mul(int fid, const char* name, const char* paramname, const char* strvalue)
{
	GET_F(fid);
	return f->CC_Write_FunctionalWithName_String(name, paramname, strvalue);
}

int cg_iRIC_Read_Complex_Count_Mul(int fid, const char* groupname, int* count)
{
	GET_F(fid);
	return f->Complex_CC_Read_Count(groupname, count);
}

int cg_iRIC_Read_Complex_Integer_Mul(int fid, const char* groupname, int num, const char* name, int* intvalue)
{
	GET_F(fid);
	return f->Complex_CC_Read_Integer(groupname, num, name, intvalue);
}

int cg_iRIC_Read_Complex_Real_Mul(int fid, const char* groupname, int num, const char* name, double* realvalue)
{
	GET_F(fid);
	return f->Complex_CC_Read_Real(groupname, num, name, realvalue);
}

int cg_iRIC_Read_Complex_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, float* realvalue)
{
	GET_F(fid);
	return f->Complex_CC_Read_RealSingle(groupname, num, name, realvalue);
}

int cg_iRIC_Read_Complex_StringLen_Mul(int fid, const char* groupname, int num, const char* name, int* length)
{
	GET_F(fid);
	return f->Complex_CC_Read_StringLen(groupname, num, name, length);
}

int cg_iRIC_Read_Complex_String_Mul(int fid, const char* groupname, int num, const char* name, char* strvalue)
{
	GET_F(fid);
	return f->Complex_CC_Read_String(groupname, num, name, strvalue);
}

int cg_iRIC_Read_Complex_FunctionalSize_Mul(int fid, const char* groupname, int num, const char* name, cgsize_t* size)
{
	GET_F(fid);
	return f->Complex_CC_Read_FunctionalSize(groupname, num, name, size);
}

int cg_iRIC_Read_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, double* x, double* y)
{
	GET_F(fid);
	return f->Complex_CC_Read_Functional(groupname, num, name, x, y);
}

int cg_iRIC_Read_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, double* data)
{
	GET_F(fid);
	return f->Complex_CC_Read_FunctionalWithName(groupname, num, name, paramname, data);
}

int cg_iRIC_Read_Complex_Functional_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, float* x, float* y)
{
	GET_F(fid);
	return f->Complex_CC_Read_Functional_RealSingle(groupname, num, name, x, y);
}

int cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, float* data)
{
	GET_F(fid);
	return f->Complex_CC_Read_FunctionalWithName_RealSingle(groupname, num, name, paramname, data);
}

int cg_iRIC_Read_Complex_FunctionalWithName_StringLen_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, int* length)
{
	GET_F(fid);
	return f->Complex_CC_Read_FunctionalWithName_StringLen(groupname, num, name, paramname, length);
}

int cg_iRIC_Read_Complex_FunctionalWithName_String_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, char* strvalue)
{
	GET_F(fid);
	return f->Complex_CC_Read_FunctionalWithName_String(groupname, num, name, paramname, strvalue);
}

int cg_iRIC_Read_Grid_Complex_Node_Mul(int fid, const char* groupname, int* values)
{
	GET_F(fid);
	return f->Complex_CC_Read_Grid_Node(groupname, values);
}

int cg_iRIC_Read_Grid_Complex_Cell_Mul(int fid, const char *groupname, int* values)
{
	GET_F(fid);
	return f->Complex_CC_Read_Grid_Cell(groupname, values);
}

int cg_iRIC_Clear_Complex_Mul(int fid)
{
	GET_F(fid);
	return f->Complex_CC_Clear_Complex();
}

int cg_iRIC_Write_Complex_Integer_Mul(int fid, const char* groupname, int num, const char* name, int intvalue)
{
	GET_F(fid);
	return f->Complex_CC_Write_Integer(groupname, num, name, intvalue);
}

int cg_iRIC_Write_Complex_Real_Mul(int fid, const char* groupname, int num, const char* name, double realvalue)
{
	GET_F(fid);
	return f->Complex_CC_Write_Real(groupname, num, name, realvalue);
}

int cg_iRIC_Write_Complex_String_Mul(int fid, const char* groupname, int num, const char* name, const char* strvalue)
{
	GET_F(fid);
	return f->Complex_CC_Write_String(groupname, num, name, strvalue);
}

int cg_iRIC_Write_Complex_Functional_Mul(int fid, const char* groupname, int num, const char* name, int length, double* realarray_x, double* realarray_y)
{
	GET_F(fid);
	return f->Complex_CC_Write_Functional(groupname, num, name, length, realarray_x, realarray_y);
}

int cg_iRIC_Write_Complex_FunctionalWithName_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, int length, double* data)
{
	GET_F(fid);
	return f->Complex_CC_Write_FunctionalWithName(groupname, num, name, paramname, length, data);
}

int cg_iRIC_Write_Complex_FunctionalWithName_String_Mul(int fid, const char* groupname, int num, const char* name, const char* paramname, const char* strvalue)
{
	GET_F(fid);
	return f->Complex_CC_Write_FunctionalWithName_String(groupname, num, name, paramname, strvalue);
}

int cg_iRIC_Write_Grid_Complex_Node_Mul(int fid, const char* groupname, int* values)
{
	GET_F(fid);
	return f->Complex_CC_Write_Grid_Node(groupname, values);
}

int cg_iRIC_Write_Grid_Complex_Cell_Mul(int fid, const char *groupname, int* values)
{
	GET_F(fid);
	return f->Complex_CC_Write_Grid_Cell(groupname, values);
}

int cg_iRIC_GotoGridCoord2d_Mul(int fid, cgsize_t* isize, cgsize_t* jsize)
{
	GET_F(fid);
	return f->Grid_GotoCoord2d(isize, jsize);
}

int cg_iRIC_GetGridCoord2d_Mul(int fid, double *x, double *y)
{
	GET_F(fid);
	return f->Grid_GetCoord2d(x, y);
}

int cg_iRIC_GotoGridCoord3d_Mul(int fid, cgsize_t* isize, cgsize_t* jsize, cgsize_t* ksize)
{
	GET_F(fid);
	return f->Grid_GotoCoord3d(isize, jsize, ksize);
}

int cg_iRIC_GetGridCoord3d_Mul(int fid, double *x, double *y, double *z)
{
	GET_F(fid);
	return f->Grid_GetCoord3d(x, y, z);
}

int cg_iRIC_Read_Grid_Real_Node_Mul(int fid, const char* name, double* values)
{
	GET_F(fid);
	return f->Grid_Read_Real_Node(name, values);
}

int cg_iRIC_Read_Grid_Integer_Node_Mul(int fid, const char* name, int* values)
{
	GET_F(fid);
	return f->Grid_Read_Integer_Node(name, values);
}

int cg_iRIC_Read_Grid_Real_Cell_Mul(int fid, const char *name, double* values)
{
	GET_F(fid);
	return f->Grid_Read_Real_Cell(name, values);
}

int cg_iRIC_Read_Grid_Integer_Cell_Mul(int fid, const char *name, int* values)
{
	GET_F(fid);
	return f->Grid_Read_Integer_Cell(name, values);
}

int cg_iRIC_Read_Grid_FunctionalDimensionSize_Mul(int fid, const char* name, const char* dimname, cgsize_t* count)
{
	GET_F(fid);
	return f->Grid_Read_FunctionalDimensionSize(name, dimname, count);
}

int cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(int fid, const char* name, const char* dimname, int* value)
{
	GET_F(fid);
	return f->Grid_Read_FunctionalDimension_Integer(name, dimname, value);
}

int cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(int fid, const char* name, const char* dimname, double* value)
{
	GET_F(fid);
	return f->Grid_Read_FunctionalDimension_Real(name, dimname, value);
}

int cg_iRIC_Read_Grid_FunctionalTimeSize_Mul(int fid, const char* name, cgsize_t* count)
{
	GET_F(fid);
	return f->Grid_Read_FunctionalTimeSize(name, count);
}

int cg_iRIC_Read_Grid_FunctionalTime_Mul(int fid, const char* name, double* time)
{
	GET_F(fid);
	return f->Grid_Read_FunctionalTime(name, time);
}

int cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(int fid, const char* name, int dimid, int* value)
{
	GET_F(fid);
	return f->Grid_Read_Functional_Integer_Node(name, dimid, value);
}

int cg_iRIC_Read_Grid_Functional_Real_Node_Mul(int fid, const char* name, int dimid, double* value)
{
	GET_F(fid);
	return f->Grid_Read_Functional_Real_Node(name, dimid, value);
}

int cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(int fid, const char* name, int dimid, int* value)
{
	GET_F(fid);
	return f->Grid_Read_Functional_Integer_Cell(name, dimid, value);
}

int cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(int fid, const char* name, int dimid, double* value)
{
	GET_F(fid);
	return f->Grid_Read_Functional_Real_Cell(name, dimid, value);
}

int cg_iRIC_WriteGridCoord1d_Mul(int fid, cgsize_t isize, double* x)
{
	GET_F(fid);
	return f->Grid_WriteGridCoord1d(isize, x);
}

int cg_iRIC_WriteGridCoord2d_Mul(int fid, cgsize_t isize, cgsize_t jsize, double* x, double* y)
{
	GET_F(fid);
	return f->Grid_WriteGridCoord2d(isize, jsize, x, y);
}

int cg_iRIC_WriteGridCoord3d_Mul(int fid, cgsize_t isize, cgsize_t jsize, cgsize_t ksize, double* x, double* y, double* z)
{
	GET_F(fid);
	return f->Grid_WriteGridCoord3d(isize, jsize, ksize, x, y, z);
}

int cg_iRIC_InitGrid_Mul(int fid, int zoneId)
{
	GET_F(fid);
	return f->Grid_Init(zoneId);
}

int cg_iRIC_Write_Grid_Real_Node_Mul(int fid, const char* name, double* values)
{
	GET_F(fid);
	return f->Grid_Write_Real_Node(name, values);
}

int cg_iRIC_Write_Grid_Integer_Node_Mul(int fid, const char* name, int* values)
{
	GET_F(fid);
	return f->Grid_Write_Integer_Node(name, values);
}

int cg_iRIC_Write_Grid_Real_Cell_Mul(int fid, const char* name, double* values)
{
	GET_F(fid);
	return f->Grid_Write_Real_Cell(name, values);
}

int cg_iRIC_Write_Grid_Integer_Cell_Mul(int fid, const char* name, int* values)
{
	GET_F(fid);
	return f->Grid_Write_Integer_Cell(name, values);
}

int cg_iRIC_Read_Sol_Count_Mul(int fid, int* count)
{
	GET_F(fid);
	return f->Sol_Read_Count(count);
}

int cg_iRIC_Read_Sol_Time_Mul(int fid, int step, double* time){
	GET_F(fid);
	return f->Sol_Read_Time(step, time);
}

int cg_iRIC_Read_Sol_Iteration_Mul(int fid, int step, int* index){
	GET_F(fid);
	return f->Sol_Read_Iteration(step, index);
}

int cg_iRIC_Read_Sol_BaseIterative_Integer_Mul(int fid, int step, const char* name, int* value)
{
	GET_F(fid);
	return f->Sol_Read_BaseIterative_Integer(step, name, value);
}

int cg_iRIC_Read_Sol_BaseIterative_Real_Mul(int fid, int step, const char* name, double* value)
{
	GET_F(fid);
	return f->Sol_Read_BaseIterative_Real(step, name, value);
}

int cg_iRIC_Read_Sol_GridCoord2d_Mul(int fid, int step, double* x, double* y)
{
	GET_F(fid);
	return f->Sol_Read_GridCoord2d(step, x, y);
}

int cg_iRIC_Read_Sol_GridCoord3d_Mul(int fid, int step, double* x, double* y, double* z)
{
	GET_F(fid);
	return f->Sol_Read_GridCoord3d(step, x, y, z);
}

int cg_iRIC_Read_Sol_Integer_Mul(int fid, int step, const char *name, int* data)
{
	GET_F(fid);
	return f->Sol_Read_Integer(step, name, data);
}

int cg_iRIC_Read_Sol_Cell_Integer_Mul(int fid, int step, const char *name, int* data)
{
	GET_F(fid);
	return f->Sol_Read_Cell_Integer(step, name, data);
}

int cg_iRIC_Read_Sol_IFace_Integer_Mul(int fid, int step, const char *name, int* data)
{
	GET_F(fid);
	return f->Sol_Read_IFace_Integer(step, name, data);
}

int cg_iRIC_Read_Sol_JFace_Integer_Mul(int fid, int step, const char *name, int* data)
{
	GET_F(fid);
	return f->Sol_Read_JFace_Integer(step, name, data);
}

int cg_iRIC_Read_Sol_Real_Mul(int fid, int step, const char *name, double* data)
{
	GET_F(fid);
	return f->Sol_Read_Real(step, name, data);
}

int cg_iRIC_Read_Sol_Cell_Real_Mul(int fid, int step, const char *name, double* data)
{
	GET_F(fid);
	return f->Sol_Read_Cell_Real(step, name, data);
}

int cg_iRIC_Read_Sol_IFace_Real_Mul(int fid, int step, const char *name, double* data)
{
	GET_F(fid);
	return f->Sol_Read_IFace_Real(step, name, data);
}

int cg_iRIC_Read_Sol_JFace_Real_Mul(int fid, int step, const char *name, double* data)
{
	GET_F(fid);
	return f->Sol_Read_JFace_Real(step, name, data);
}

int cg_iRIC_Write_Sol_Time_Mul(int fid, double time){
	GET_F(fid);
	return f->Sol_Write_Time(time);
}

int cg_iRIC_Write_Sol_Iteration_Mul(int fid, int index){
	GET_F(fid);
	return f->Sol_Write_Iteration(index);
}

int cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(int fid, const char *name, int value){
	GET_F(fid);
	return f->Sol_Write_BaseIterative_Integer(name, value);
}

int cg_iRIC_Write_Sol_BaseIterative_Real_Mul(int fid, const char *name, double value){
	GET_F(fid);
	return f->Sol_Write_BaseIterative_Real(name, value);
}

int cg_iRIC_Write_Sol_GridCoord2d_Mul(int fid, double *x, double *y)
{
	GET_F(fid);
	return f->Sol_Write_GridCoord2d(x, y);
}

int cg_iRIC_Write_Sol_GridCoord3d_Mul(int fid, double *x, double *y, double *z)
{
	GET_F(fid);
	return f->Sol_Write_GridCoord3d(x, y, z);
}

int cg_iRIC_Write_Sol_Integer_Mul(int fid, const char *name, int* data)
{
	GET_F(fid);
	return f->Sol_Write_Integer(name, data);
}

int cg_iRIC_Write_Sol_Cell_Integer_Mul(int fid, const char *name, int* data)
{
	GET_F(fid);
	return f->Sol_Write_Cell_Integer(name, data);
}

int cg_iRIC_Write_Sol_IFace_Integer_Mul(int fid, const char *name, int* data)
{
	GET_F(fid);
	return f->Sol_Write_IFace_Integer(name, data);
}

int cg_iRIC_Write_Sol_JFace_Integer_Mul(int fid, const char *name, int* data)
{
	GET_F(fid);
	return f->Sol_Write_JFace_Integer(name, data);
}

int cg_iRIC_Write_Sol_Real_Mul(int fid, const char *name, double* data)
{
	GET_F(fid);
	return f->Sol_Write_Real(name, data);
}

int cg_iRIC_Write_Sol_Cell_Real_Mul(int fid, const char *name, double* data)
{
	GET_F(fid);
	return f->Sol_Write_Cell_Real(name, data);
}

int cg_iRIC_Write_Sol_IFace_Real_Mul(int fid, const char *name, double* data)
{
	GET_F(fid);
	return f->Sol_Write_IFace_Real(name, data);
}

int cg_iRIC_Write_Sol_JFace_Real_Mul(int fid, const char *name, double* data)
{
	GET_F(fid);
	return f->Sol_Write_JFace_Real(name, data);
}

int cg_iRIC_Write_ErrorCode_Mul(int fid, int errorcode)
{
	GET_F(fid);
	return f->ErrorCode_Write(errorcode);
}

void cg_iRIC_Init_BC_Names_Mul(int fid)
{
	GET_F_VOID(fid);
	f->BC_Init_Names();
}

void cg_iRIC_Read_BC_Count_Mul(int fid, const char* type, int* num)
{
	GET_F_VOID(fid);
	return f->BC_Read_Count(type, num);
}

int cg_iRIC_Read_BC_IndicesSize_Mul(int fid, const char* type, int num, cgsize_t* size)
{
	GET_F(fid);
	return f->BC_Read_IndicesSize(type, num, size);
}

int cg_iRIC_Read_BC_Indices_Mul(int fid, const char* type, int num, cgsize_t* indices)
{
	GET_F(fid);
	return f->BC_Read_Indices(type, num, indices);
}

int cg_iRIC_Read_BC_Integer_Mul(int fid, const char* type, int num, const char* name, int* intvalue)
{
	GET_F(fid);
	return f->BC_Read_Integer(type, num, name, intvalue);
}

int cg_iRIC_Read_BC_Real_Mul(int fid, const char* type, int num, const char* name, double* realvalue){
	GET_F(fid);
	return f->BC_Read_Real(type, num, name, realvalue);
}

int cg_iRIC_Read_BC_RealSingle_Mul(int fid, const char* type, int num, const char* name, float* realvalue){
	GET_F(fid);
	return f->BC_Read_RealSingle(type, num, name, realvalue);
}

int cg_iRIC_Read_BC_StringLen_Mul(int fid, const char* type, int num, const char* name, int* length){
	GET_F(fid);
	return f->BC_Read_StringLen(type, num, name, length);
}

int cg_iRIC_Read_BC_String_Mul(int fid, const char* type, int num, const char* name, char* strvalue){
	GET_F(fid);
	return f->BC_Read_String(type, num, name, strvalue);
}

int cg_iRIC_Read_BC_FunctionalSize_Mul(int fid, const char* type, int num, const char* name, cgsize_t* size){
	GET_F(fid);
	return f->BC_Read_FunctionalSize(type, num, name, size);
}

int cg_iRIC_Read_BC_Functional_Mul(int fid, const char* type, int num, const char* name, double* x, double* y){
	GET_F(fid);
	return f->BC_Read_Functional(type, num, name, x, y);
}

int cg_iRIC_Read_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, double* data){
	GET_F(fid);
	return f->BC_Read_FunctionalWithName(type, num, name, paramname, data);
}

int cg_iRIC_Read_BC_Functional_RealSingle_Mul(int fid, const char* type, int num, const char* name, float* x, float* y){
	GET_F(fid);
	return f->BC_Read_Functional_RealSingle(type, num, name, x, y);
}

int cg_iRIC_Read_BC_FunctionalWithName_RealSingle_Mul(int fid, const char* type, int num, const char* name, const char* paramname, float* data){
	GET_F(fid);
	return f->BC_Read_FunctionalWithName_RealSingle(type, num, name, paramname, data);
}

int cg_iRIC_Read_BC_FunctionalWithName_StringLen_Mul(int fid, const char* type, int num, const char* name, const char* paramname, int* length){
	GET_F(fid);
	return f->BC_Read_FunctionalWithName_StringLen(type, num, name, paramname, length);
}

int cg_iRIC_Read_BC_FunctionalWithName_String_Mul(int fid, const char* type, int num, const char* name, const char* paramname, char* strvalue){
	GET_F(fid);
	return f->BC_Read_FunctionalWithName_String(type, num, name, paramname, strvalue);
}

int cg_iRIC_Clear_BC_Mul(int fid){
	GET_F(fid);
	return f->BC_Clear();
}

int cg_iRIC_Write_BC_Indices_Mul(int fid, const char* type, int num, cgsize_t size, cgsize_t* indices){
	GET_F(fid);
	return f->BC_Write_Indices(type, num, size, indices);
}

int cg_iRIC_Write_BC_Integer_Mul(int fid, const char* type, int num, const char* name, int intvalue){
	GET_F(fid);
	return f->BC_Write_Integer(type, num, name, intvalue);
}

int cg_iRIC_Write_BC_Real_Mul(int fid, const char* type, int num, const char* name, double realvalue)
{
	GET_F(fid);
	return f->BC_Write_Real(type, num, name, realvalue);
}

int cg_iRIC_Write_BC_String_Mul(int fid, const char* type, int num, const char* name, const char* strvalue)
{
	GET_F(fid);
	return f->BC_Write_String(type, num, name, strvalue);
}

int cg_iRIC_Write_BC_Functional_Mul(int fid, const char* type, int num, const char* name, int length, double* realarray_x, double* realarray_y){
	GET_F(fid);
	return f->BC_Write_Functional(type, num, name, length, realarray_x, realarray_y);
}

int cg_iRIC_Write_BC_FunctionalWithName_Mul(int fid, const char* type, int num, const char* name, const char* paramname, int length, double* data){
	GET_F(fid);
	return f->BC_Write_FunctionalWithName(type, num, name, paramname, length, data);
}

int cg_iRIC_Write_BC_FunctionalWithName_String_Mul(int fid, const char* type, int num, const char* name, const char* paramname, const char* strvalue){
	GET_F(fid);
	return f->BC_Write_FunctionalWithName_String(type, num, name, paramname, strvalue);
}

int cg_iRIC_Read_Geo_Count_Mul(int fid, const char* name, int* count)
{
	GET_F(fid);
	return f->Geo_Count(name, count);
}

int cg_iRIC_Read_Geo_Filename_Mul(int fid, const char* name, int geoid, char* filename, int* type)
{
	GET_F(fid);
	return f->Geo_Filename(name, geoid, filename, type);
}

int cg_iRIC_Write_Sol_Particle_Pos2d_Mul(int fid, cgsize_t count, double* x, double* y)
{
	GET_F(fid);
	return f->Sol_Particle_Write_Pos2d(count, x, y);
}

int cg_iRIC_Write_Sol_Particle_Pos3d_Mul(int fid, cgsize_t count, double* x, double* y, double* z)
{
	GET_F(fid);
	return f->Sol_Particle_Write_Pos3d(count, x, y, z);
}

int cg_iRIC_Write_Sol_Particle_Real_Mul(int fid, const char* name, double* value)
{
	GET_F(fid);
	return f->Sol_Particle_Write_Real(name, value);
}

int cg_iRIC_Write_Sol_Particle_Integer_Mul(int fid, const char* name, int* value)
{
	GET_F(fid);
	return f->Sol_Particle_Write_Integer(name, value);
}

int cg_iRIC_Write_Sol_PolyData_GroupBegin_Mul(int fid, const char* name)
{
	GET_F(fid);
	return f->Sol_PolyData_Write_GroupBegin(name);
}

int cg_iRIC_Write_Sol_PolyData_GroupEnd_Mul(int fid)
{
	GET_F(fid);
	return f->Sol_PolyData_Write_GroupEnd();
}

int cg_iRIC_Write_Sol_PolyData_Polygon_Mul(int fid, int numPoints, double* x, double* y)
{
	GET_F(fid);
	return f->Sol_PolyData_Write_Polygon(numPoints, x, y);
}

int cg_iRIC_Write_Sol_PolyData_Polyline_Mul(int fid, int numPoints, double* x, double* y)
{
	GET_F(fid);
	return f->Sol_PolyData_Write_Polyline(numPoints, x, y);
}

int cg_iRIC_Write_Sol_PolyData_Integer_Mul(int fid, const char* name, int value)
{
	GET_F(fid);
	return f->Sol_PolyData_Write_Integer(name, value);
}

int cg_iRIC_Write_Sol_PolyData_Real_Mul(int fid, const char* name, double value)
{
	GET_F(fid);
	return f->Sol_PolyData_Write_Real(name, value);
}

} // extern "C"
