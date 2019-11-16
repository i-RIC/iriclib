#include "cgnslib.h"

#include <iriclib.h>

int cg_open(const char * filename, int mode, int *fn)
{
    return cg_iRIC_Open(filename, mode, fn);
}

int cg_close(int fn)
{
    return cg_iRIC_Close(fn);
}
