#include "macros.h"

#include <cgnslib.h>
#include <iriclib.h>

#include <stdio.h>
#include <iostream>

extern "C" {

void case_CheckLock()
{
	// to test for Case1.cgn.lock creation this needs to be
	// multi-threaded or multi-process
}

void case_CheckCancel()
{
	int canceled = iRIC_Check_Cancel();
	VERIFY_LOG("iRIC_Check_Cancel() checked .cancel, and it did not exist.", canceled == 0);
}

} // extern "C"
