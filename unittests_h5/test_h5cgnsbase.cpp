#include "macros.h"

#include "fs_copy.h"

#include <cgnslib.h>
#include <iriclib_h5.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace iRICLib;

void test_read_baseiterative()
{
	H5CgnsFile file("nays2dh.cgn", H5CgnsFile::Mode::OpenReadOnly);
	auto b = file.base();
	auto biter = b->biterData();
}

void test_h5cgnsbase()
{
	test_read_baseiterative();
}
