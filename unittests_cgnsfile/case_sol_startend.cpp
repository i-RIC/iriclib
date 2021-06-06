#include "macros.h"

#include <iriclib.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <vector>

extern "C" {

void case_SolStartEnd()
{
	int ier = iRIC_Write_Sol_Start("Case1.cgn");
	VERIFY_LOG("iRIC_Write_Sol_Start() ier == 0", ier == 0);

	// to test for Case1.cgn.lock creation this needs to be
	// multi-threaded or multi-process

	ier = iRIC_Write_Sol_End("Case1.cgn");
	VERIFY_LOG("iRIC_Write_Sol_End() ier == 0", ier == 0);

	FILE* f = fopen("Case1.cgn.lock", "r");
	VERIFY_LOG("iRIC_Write_Sol_End() removed Case1.cgn.lock", f == NULL);
}

} // extern "C"
