#include "iricsolverlib_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// 2D Grid related functions
int IRICSOLVERLIB_API iRIC_Solver_Grid2D_Open(int fin, int baseId, int zoneId, int gridId, int* handle);

int IRICSOLVERLIB_API iRIC_Solver_Grid2D_Read_CellCount(int gridHandle, int* cellCount);
int IRICSOLVERLIB_API iRIC_Solver_Grid2D_Read_CellNodeCount(int gridHandle, int cellId, int* nodeCount);
int IRICSOLVERLIB_API iRIC_Solver_Grid2D_Read_CellNodeIds(int gridHandle, int cellId, int* nodeIds);
int IRICSOLVERLIB_API iRIC_Solver_Grid2D_Read_CellArea(int gridHandle, int cellId, double* area);

int IRICSOLVERLIB_API iRIC_Solver_Grid2D_GetRegion(int gridHandle, double* xmin, double* xmax, double* ymin, double* ymax);
int IRICSOLVERLIB_API iRIC_Solver_Grid2D_Interpolate(int gridHandle, double x, double y, int* ok, int* count, size_t* nodeids, double* weights);

int IRICSOLVERLIB_API iRIC_Solver_Grid2D_Close(int gridHandle);

#ifdef __cplusplus
}
#endif
