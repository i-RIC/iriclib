#include <stdlib.h>
#include <string.h>

#include "iricsolverlib.h"
#include "iricsolverlib_api.h"

#include "fortran_macros.h"

#include <cgnslib.h>

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\
 *      Convert between Fortran and C strings                            *
\* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static void string_2_C_string(char *string, int string_length,
		char *c_string, int max_len, int *ierr) {
		int i, iend;

		if (string == NULL || c_string == NULL) {
//				cgi_error ("NULL string pointer");
				*ierr = CG_ERROR;
				return;
		}

		/** Skip and trailing blanks **/
		for (iend = string_length-1; iend >= 0; iend--) {
				if (string[iend] != ' ') break;
		}
		if (iend >= max_len) iend = max_len - 1;

		/** Copy the non-trailing blank portion of the string **/
		for (i = 0; i <= iend; i++)
				c_string[i] = string[i];

		/** NULL terminate the C string **/
		c_string[i] = '\0';
		*ierr = CG_OK;
}

static void string_2_F_string(char *c_string, char *string,
		int string_length, int *ierr) {
		int i;
		size_t len;

		if (c_string == NULL || string == NULL) {
//				cgi_error ("NULL string pointer");
				*ierr = CG_ERROR;
				return;
		}
		len = strlen(c_string);
		if (len > string_length) len = string_length;

		for (i = 0; i < len; i++)
				string[i] = c_string[i];
		while (i < string_length)
				string[i++] = ' ';
		*ierr = CG_OK;
}

void IRICSOLVERLIB_API FMNAME(iric_solver_grid2d_open_f, IRIC_SOLVER_GRID2D_OPEN_F) (int *fin, int *baseId, int *zoneId, int *gridId, int* handle, int *ier)
{
	*ier = iRIC_Solver_Grid2D_Open(*fin, *baseId, *zoneId, *gridId, handle);
}

void IRICSOLVERLIB_API FMNAME(iric_solver_grid2d_read_cellcount_f, IRIC_SOLVER_GRID2D_READ_CELLCOUNT_F) (int *gridHandle, int *cellCount, int *ier)
{
	*ier = iRIC_Solver_Grid2D_Read_CellCount(*gridHandle, cellCount);
}

void IRICSOLVERLIB_API FMNAME(iric_solver_grid2d_read_cellnodecount_f, IRIC_SOLVER_GRID2D_READ_CELLNODECOUNT_F) (int *gridHandle, int *cellId, int* nodeCount, int *ier)
{
	*ier = iRIC_Solver_Grid2D_Read_CellNodeCount(*gridHandle, *cellId, nodeCount);
}

void IRICSOLVERLIB_API FMNAME(iric_solver_grid2d_read_cellnodeids_f, IRIC_SOLVER_GRID2D_READ_CELLNODEIDS_F) (int *gridHandle, int *cellId, int* nodeIds, int *ier)
{
	*ier = iRIC_Solver_Grid2D_Read_CellNodeIds(*gridHandle, *cellId, nodeIds);
}

void IRICSOLVERLIB_API FMNAME(iric_solver_grid2d_read_cellarea_f, IRIC_SOLVER_GRID2D_READ_CELLAREA_F) (int *gridHandle, int *cellId, double* area, int *ier)
{
	*ier = iRIC_Solver_Grid2D_Read_CellArea(*gridHandle, *cellId, area);
}

void IRICSOLVERLIB_API FMNAME(iric_solver_grid2d_getregion_f, IRIC_SOLVER_GRID2D_GETREGION_F) (int *gridHandle, double *xmin, double *xmax, double *ymin, double *ymax, int *ier)
{
	*ier = iRIC_Solver_Grid2D_GetRegion(*gridHandle, xmin, xmax, ymin, ymax);
}

void IRICSOLVERLIB_API FMNAME(iric_solver_grid2d_interpolate_f, IRIC_SOLVER_GRID2D_INTERPOLATE_F) (int *gridHandle, double *x, double *y, int *ok, int *count, int* nodeids, double* weights, int *ier)
{
	int i;
	size_t tmpNodeIds[4];

	*ier = iRIC_Solver_Grid2D_Interpolate(*gridHandle, *x, *y, ok, count, &(tmpNodeIds[0]), weights);

	for (i = 0; i < *count; ++i) {
		*(nodeids + i) = (int) (tmpNodeIds[i]);
	}
}

void IRICSOLVERLIB_API FMNAME(iric_solver_grid2d_close_f, IRIC_SOLVER_GRID2D_CLOSE_F) (int *gridHandle, int *ier)
{
	*ier = iRIC_Solver_Grid2D_Close(*gridHandle);
}
