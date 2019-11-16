#include "macros.h"

#include "fs_copy.h"

#include <cgnslib.h>
#include <iriclib_h5.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace iRICLib;

void test_create()
{
	try {
		std::remove("test.cgn");
		auto f = new H5CgnsFile("test.cgn", H5CgnsFile::Mode::Create);
		delete f;
		VERIFY_LOG("Creating Cgnsfile succeeds", true);

		int ier, fid;
		ier = cg_open("test.cgn", CG_MODE_READ, &fid);
		VERIFY_LOG("Created cgns file is a valid", ier == 0);
		ier = cg_close(fid);
	} catch (...) {
		VERIFY_LOG("Creating Cgnsfile succeeds", false);
	}
}

void test_open_readonly()
{
	try {
		auto f = new H5CgnsFile("test.cgn", H5CgnsFile::Mode::OpenReadOnly);
		delete f;
		VERIFY_LOG("Opening Cgnsfile in read only mode succeeds", true);
	} catch (...) {
		VERIFY_LOG("Opening Cgnsfile in read only mode succeeds", false);
	}
}

void test_open_readwrite()
{
	try {
		auto f = new H5CgnsFile("test.cgn", H5CgnsFile::Mode::OpenModify);
		delete f;
		VERIFY_LOG("Opening Cgnsfile in modify mode succeeds", true);
	} catch (...) {
		VERIFY_LOG("Opening Cgnsfile in modify mode succeeds", false);
	}
}

void test_h5cgnsfile()
{
	test_create();
	test_open_readonly();
	test_open_readwrite();
}
