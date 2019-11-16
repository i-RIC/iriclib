#ifndef IRICLIB_INIT_H
#define IRICLIB_INIT_H

#include "iriclib_global.h"

#ifdef __cplusplus
extern "C" {
#endif

int IRICLIBDLL cg_iRIC_Open(const char* filename, int mode, int* fid);
int IRICLIBDLL cg_iRIC_Close(int fid);
int IRICLIBDLL cg_iRIC_Init(int fid);
int IRICLIBDLL cg_iRIC_InitRead(int fid);
int IRICLIBDLL iRIC_InitOption(int option);
int IRICLIBDLL cg_iRIC_Flush(const char* name, int fid);
int IRICLIBDLL cg_iRIC_GotoBase(int fid, int* B);
int IRICLIBDLL cg_iRIC_GotoCC(int fid);
int IRICLIBDLL cg_iRIC_GotoRawDataTop(int fid);

#ifdef __cplusplus
}
#endif

#endif // IRICLIB_INIT_H