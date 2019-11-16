#include "iriclib.h"
#include "iriclib_errorcodes.h"

#include <Poco/File.h>

#include <iostream>
#include <cstdlib>

int iRIC_Write_Sol_Start(const char* /*fname*/)
{
	return IRIC_NO_ERROR;
}

int iRIC_Write_Sol_End(const char* /*fname*/)
{
	return IRIC_NO_ERROR;
}

int iRIC_Check_Lock(const char* /*fname*/)
{
	return IRIC_NO_ERROR;
}

int iRIC_Check_Cancel()
{
	Poco::File f(".cancel");

	if (f.exists()) {
		std::cout << "Solver is stopped because the STOP button was clicked." << std::endl;
		exit(0);
	}

	return IRIC_NO_ERROR;
}
