//#define NAME_MAXLENGTH 200
#include "fortran_macros.h"
#include <string.h>

#include "iriclib.h"
#include "iriclib_errorcodes.h"

#define STRINGMAXLEN 2048

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - *\
 *      Convert between Fortran and C strings                            *
\* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

static void string_2_C_string(char *string, int string_length,
    char *c_string, int max_len, int *ierr) {
    int i, iend;

    if (string == nullptr || c_string == nullptr) {
        *ierr = IRIC_WRONG_POINTER;
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
    *ierr = IRIC_NO_ERROR;
}

static void string_2_F_string(char *c_string, char *string,
    int string_length, int *ierr) {
    int i;
    size_t len;

    if (c_string == nullptr || string == nullptr) {
        *ierr = IRIC_WRONG_POINTER;
        return;
    }
    len = strlen(c_string);
    if (len > string_length) len = string_length;

    for (i = 0; i < len; i++)
        string[i] = c_string[i];
    while (i < string_length)
        string[i++] = ' ';
    *ierr = IRIC_NO_ERROR;
}

extern "C" {
// from iriclib_bc.h
void IRICLIBDLL FMNAME(cg_iric_read_bc_count_withgridid_f, CG_IRIC_READ_BC_COUNT_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num STR_PLEN(type)) {
	int ier;

	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, &ier);
	if (ier != 0) return;

	cg_iRIC_Read_BC_Count_WithGridId(*fid, *gid, c_type, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indicessize_withgridid_f, CG_IRIC_READ_BC_INDICESSIZE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, int* size, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_IndicesSize_WithGridId(*fid, *gid, c_type, *num, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indices_withgridid_f, CG_IRIC_READ_BC_INDICES_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Indices_WithGridId(*fid, *gid, c_type, *num, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_integer_withgridid_f, CG_IRIC_READ_BC_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Integer_WithGridId(*fid, *gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_real_withgridid_f, CG_IRIC_READ_BC_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Real_WithGridId(*fid, *gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_realsingle_withgridid_f, CG_IRIC_READ_BC_REALSINGLE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_RealSingle_WithGridId(*fid, *gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_stringlen_withgridid_f, CG_IRIC_READ_BC_STRINGLEN_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_StringLen_WithGridId(*fid, *gid, c_type, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_string_withgridid_f, CG_IRIC_READ_BC_STRING_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_String_WithGridId(*fid, *gid, c_type, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalsize_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALSIZE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalSize_WithGridId(*fid, *gid, c_type, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_withgridid_f, CG_IRIC_READ_BC_FUNCTIONAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_WithGridId(*fid, *gid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_WithGridId(*fid, *gid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_realsingle_withgridid_f, CG_IRIC_READ_BC_FUNCTIONAL_REALSINGLE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_RealSingle_WithGridId(*fid, *gid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_realsingle_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_REALSINGLE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_RealSingle_WithGridId(*fid, *gid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_stringlen_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRINGLEN_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen_WithGridId(*fid, *gid, c_type, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_string_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRING_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_String_WithGridId(*fid, *gid, c_type, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_bc_withgridid_f, CG_IRIC_CLEAR_BC_WITHGRIDID_F) (int* fid, int* gid, int *ier) {
	*ier = cg_iRIC_Clear_BC_WithGridId(*fid, *gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices_withgridid_f, CG_IRIC_WRITE_BC_INDICES_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices_WithGridId(*fid, *gid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices2_withgridid_f, CG_IRIC_WRITE_BC_INDICES2_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices2_WithGridId(*fid, *gid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_integer_withgridid_f, CG_IRIC_WRITE_BC_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Integer_WithGridId(*fid, *gid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_real_withgridid_f, CG_IRIC_WRITE_BC_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Real_WithGridId(*fid, *gid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_string_withgridid_f, CG_IRIC_WRITE_BC_STRING_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(value)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_String_WithGridId(*fid, *gid, c_type, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functional_withgridid_f, CG_IRIC_WRITE_BC_FUNCTIONAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Functional_WithGridId(*fid, *gid, c_type, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_withgridid_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_FunctionalWithName_WithGridId(*fid, *gid, c_type, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_string_withgridid_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_STRING_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_FunctionalWithName_String_WithGridId(*fid, *gid, c_type, *num, c_name, c_paramname, c_value);
}


// from iriclib_cc.h
void IRICLIBDLL FMNAME(cg_iric_read_integer_f, CG_IRIC_READ_INTEGER_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Integer(*fid, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_real_f, CG_IRIC_READ_REAL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Real(*fid, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_realsingle_f, CG_IRIC_READ_REALSINGLE_F) (int* fid, STR_PSTR(name), float* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_RealSingle(*fid, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_stringlen_f, CG_IRIC_READ_STRINGLEN_F) (int* fid, STR_PSTR(name), int* length, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_StringLen(*fid, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_string_f, CG_IRIC_READ_STRING_F) (int* fid, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_String(*fid, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalsize_f, CG_IRIC_READ_FUNCTIONALSIZE_F) (int* fid, STR_PSTR(name), int* size, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalSize(*fid, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_functional_f, CG_IRIC_READ_FUNCTIONAL_F) (int* fid, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Functional(*fid, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_f, CG_IRIC_READ_FUNCTIONALWITHNAME_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName(*fid, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functional_realsingle_f, CG_IRIC_READ_FUNCTIONAL_REALSINGLE_F) (int* fid, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Functional_RealSingle(*fid, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_realsingle_f, CG_IRIC_READ_FUNCTIONALWITHNAME_REALSINGLE_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_RealSingle(*fid, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_string_f, CG_IRIC_READ_FUNCTIONALWITHNAME_STRING_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_String(*fid, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_stringlen_f, CG_IRIC_READ_FUNCTIONALWITHNAME_STRINGLEN_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_StringLen(*fid, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_write_integer_f, CG_IRIC_WRITE_INTEGER_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Integer(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_real_f, CG_IRIC_WRITE_REAL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Real(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_string_f, CG_IRIC_WRITE_STRING_F) (int* fid, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_String(*fid, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_functional_f, CG_IRIC_WRITE_FUNCTIONAL_F) (int* fid, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Functional(*fid, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_functionalwithname_f, CG_IRIC_WRITE_FUNCTIONALWITHNAME_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_FunctionalWithName(*fid, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_functionalwithname_string_f, CG_IRIC_WRITE_FUNCTIONALWITHNAME_STRING_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_FunctionalWithName_String(*fid, c_name, c_paramname, c_value);
}


// from iriclib_complex.h
void IRICLIBDLL FMNAME(cg_iric_read_complex_count_withbaseid_f, CG_IRIC_READ_COMPLEX_COUNT_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Count_WithBaseId(*fid, *bid, c_groupname, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_integer_withbaseid_f, CG_IRIC_READ_COMPLEX_INTEGER_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Integer_WithBaseId(*fid, *bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_real_withbaseid_f, CG_IRIC_READ_COMPLEX_REAL_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Real_WithBaseId(*fid, *bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_realsingle_withbaseid_f, CG_IRIC_READ_COMPLEX_REALSINGLE_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_RealSingle_WithBaseId(*fid, *bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_stringlen_withbaseid_f, CG_IRIC_READ_COMPLEX_STRINGLEN_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_StringLen_WithBaseId(*fid, *bid, c_groupname, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_string_withbaseid_f, CG_IRIC_READ_COMPLEX_STRING_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_String_WithBaseId(*fid, *bid, c_groupname, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalsize_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALSIZE_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalSize_WithBaseId(*fid, *bid, c_groupname, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_WithBaseId(*fid, *bid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId(*fid, *bid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_realsingle_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_REALSINGLE_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_RealSingle_WithBaseId(*fid, *bid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_realsingle_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_REALSINGLE_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_WithBaseId(*fid, *bid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_stringlen_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRINGLEN_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_StringLen_WithBaseId(*fid, *bid, c_groupname, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_string_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRING_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_String_WithBaseId(*fid, *bid, c_groupname, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_node_withgridid_f, CG_IRIC_READ_GRID_COMPLEX_NODE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Node_WithGridId(*fid, *gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_cell_withgridid_f, CG_IRIC_READ_GRID_COMPLEX_CELL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Cell_WithGridId(*fid, *gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_clear_complex_withbaseid_f, CG_IRIC_CLEAR_COMPLEX_WITHBASEID_F) (int* fid, int* bid, int *ier) {
	*ier = cg_iRIC_Clear_Complex_WithBaseId(*fid, *bid);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_integer_withbaseid_f, CG_IRIC_WRITE_COMPLEX_INTEGER_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Integer_WithBaseId(*fid, *bid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_real_withbaseid_f, CG_IRIC_WRITE_COMPLEX_REAL_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Real_WithBaseId(*fid, *bid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_string_withbaseid_f, CG_IRIC_WRITE_COMPLEX_STRING_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(value)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_String_WithBaseId(*fid, *bid, c_groupname, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functional_withbaseid_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONAL_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Functional_WithBaseId(*fid, *bid, c_groupname, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_withbaseid_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId(*fid, *bid, c_groupname, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_string_withbaseid_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_STRING_WITHBASEID_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_String_WithBaseId(*fid, *bid, c_groupname, *num, c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_node_withgridid_f, CG_IRIC_WRITE_GRID_COMPLEX_NODE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Node_WithGridId(*fid, *gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_cell_withgridid_f, CG_IRIC_WRITE_GRID_COMPLEX_CELL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Cell_WithGridId(*fid, *gid, c_groupname, v_arr);
}


// from iriclib_geo.h
void IRICLIBDLL FMNAME(iric_geo_polygon_open_f, IRIC_GEO_POLYGON_OPEN_F) (STR_PSTR(filename), int* id, int *ier STR_PLEN(filename)) {
	char c_filename[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(filename), STR_LEN(filename), c_filename, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = iRIC_Geo_Polygon_Open(c_filename, id);
}

void IRICLIBDLL FMNAME(iric_geo_polygon_read_integervalue_f, IRIC_GEO_POLYGON_READ_INTEGERVALUE_F) (int* id, int* value, int *ier) {
	*ier = iRIC_Geo_Polygon_Read_IntegerValue(*id, value);
}

void IRICLIBDLL FMNAME(iric_geo_polygon_read_realvalue_f, IRIC_GEO_POLYGON_READ_REALVALUE_F) (int* id, double* value, int *ier) {
	*ier = iRIC_Geo_Polygon_Read_RealValue(*id, value);
}

void IRICLIBDLL FMNAME(iric_geo_polygon_read_pointcount_f, IRIC_GEO_POLYGON_READ_POINTCOUNT_F) (int* id, int* size, int *ier) {
	*ier = iRIC_Geo_Polygon_Read_PointCount(*id, size);
}

void IRICLIBDLL FMNAME(iric_geo_polygon_read_points_f, IRIC_GEO_POLYGON_READ_POINTS_F) (int* id, double* x_arr, double* y_arr, int *ier) {
	*ier = iRIC_Geo_Polygon_Read_Points(*id, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(iric_geo_polygon_read_holecount_f, IRIC_GEO_POLYGON_READ_HOLECOUNT_F) (int* id, int* count, int *ier) {
	*ier = iRIC_Geo_Polygon_Read_HoleCount(*id, count);
}

void IRICLIBDLL FMNAME(iric_geo_polygon_read_holepointcount_f, IRIC_GEO_POLYGON_READ_HOLEPOINTCOUNT_F) (int* id, int* holeid, int* count, int *ier) {
	*ier = iRIC_Geo_Polygon_Read_HolePointCount(*id, *holeid, count);
}

void IRICLIBDLL FMNAME(iric_geo_polygon_read_holepoints_f, IRIC_GEO_POLYGON_READ_HOLEPOINTS_F) (int* id, int* holeid, double* x_arr, double* y_arr, int *ier) {
	*ier = iRIC_Geo_Polygon_Read_HolePoints(*id, *holeid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(iric_geo_polygon_close_f, IRIC_GEO_POLYGON_CLOSE_F) (int* id, int *ier) {
	*ier = iRIC_Geo_Polygon_Close(*id);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_open_f, IRIC_GEO_RIVERSURVEY_OPEN_F) (STR_PSTR(filename), int* id, int *ier STR_PLEN(filename)) {
	char c_filename[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(filename), STR_LEN(filename), c_filename, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = iRIC_Geo_RiverSurvey_Open(c_filename, id);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_count_f, IRIC_GEO_RIVERSURVEY_READ_COUNT_F) (int* id, int* count, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_Count(*id, count);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_position_f, IRIC_GEO_RIVERSURVEY_READ_POSITION_F) (int* id, int* pointid, double* x, double* y, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_Position(*id, *pointid, x, y);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_direction_f, IRIC_GEO_RIVERSURVEY_READ_DIRECTION_F) (int* id, int* pointid, double* vx, double* vy, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_Direction(*id, *pointid, vx, vy);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_name_f, IRIC_GEO_RIVERSURVEY_READ_NAME_F) (int* id, int* pointid, STR_PSTR(strvalue), int *ier STR_PLEN(strvalue)) {
	char c_strvalue[STRINGMAXLEN + 1];
	*ier = iRIC_Geo_RiverSurvey_Read_Name(*id, *pointid, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_realname_f, IRIC_GEO_RIVERSURVEY_READ_REALNAME_F) (int* id, int* pointid, double* name, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_RealName(*id, *pointid, name);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_leftshift_f, IRIC_GEO_RIVERSURVEY_READ_LEFTSHIFT_F) (int* id, int* pointid, double* shift, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_LeftShift(*id, *pointid, shift);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_altitudecount_f, IRIC_GEO_RIVERSURVEY_READ_ALTITUDECOUNT_F) (int* id, int* pointid, int* count, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_AltitudeCount(*id, *pointid, count);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_altitudes_f, IRIC_GEO_RIVERSURVEY_READ_ALTITUDES_F) (int* id, int* pointid, double* position_arr, double* height_arr, int* active_arr, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_Altitudes(*id, *pointid, position_arr, height_arr, active_arr);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_fixedpointl_f, IRIC_GEO_RIVERSURVEY_READ_FIXEDPOINTL_F) (int* id, int* pointid, int* set, double* directionX, double* directionY, int* index, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_FixedPointL(*id, *pointid, set, directionX, directionY, index);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_fixedpointr_f, IRIC_GEO_RIVERSURVEY_READ_FIXEDPOINTR_F) (int* id, int* pointid, int* set, double* directionX, double* directionY, int* index, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_FixedPointR(*id, *pointid, set, directionX, directionY, index);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_read_watersurfaceelevation_f, IRIC_GEO_RIVERSURVEY_READ_WATERSURFACEELEVATION_F) (int* id, int* pointid, int* set, double* value, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Read_WaterSurfaceElevation(*id, *pointid, set, value);
}

void IRICLIBDLL FMNAME(iric_geo_riversurvey_close_f, IRIC_GEO_RIVERSURVEY_CLOSE_F) (int* id, int *ier) {
	*ier = iRIC_Geo_RiverSurvey_Close(*id);
}


// from iriclib_geoutil.h
void IRICLIBDLL FMNAME(cg_iric_read_geo_count_f, CG_IRIC_READ_GEO_COUNT_F) (int* fid, STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Geo_Count(*fid, c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_geo_filename_f, CG_IRIC_READ_GEO_FILENAME_F) (int* fid, STR_PSTR(name), int* geoid, STR_PSTR(strvalue), int* type, int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Geo_Filename(*fid, c_name, *geoid, c_strvalue, type);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}


// from iriclib_grid.h
void IRICLIBDLL FMNAME(cg_iric_read_grid2d_str_size_withgridid_f, CG_IRIC_READ_GRID2D_STR_SIZE_WITHGRIDID_F) (int* fid, int* gid, int* isize, int* jsize, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Str_Size_WithGridId(*fid, *gid, isize, jsize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_coords_withgridid_f, CG_IRIC_READ_GRID2D_COORDS_WITHGRIDID_F) (int* fid, int* gid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Coords_WithGridId(*fid, *gid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_str_size_withgridid_f, CG_IRIC_READ_GRID3D_STR_SIZE_WITHGRIDID_F) (int* fid, int* gid, int* isize, int* jsize, int* ksize, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Str_Size_WithGridId(*fid, *gid, isize, jsize, ksize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_coords_withgridid_f, CG_IRIC_READ_GRID3D_COORDS_WITHGRIDID_F) (int* fid, int* gid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Coords_WithGridId(*fid, *gid, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_triangleelementssize_withgridid_f, CG_IRIC_READ_GRID_TRIANGLEELEMENTSSIZE_WITHGRIDID_F) (int* fid, int* gid, int* size, int *ier) {
	*ier = cg_iRIC_Read_Grid_TriangleElementsSize_WithGridId(*fid, *gid, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_triangleelements_withgridid_f, CG_IRIC_READ_GRID_TRIANGLEELEMENTS_WITHGRIDID_F) (int* fid, int* gid, int* id_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid_TriangleElements_WithGridId(*fid, *gid, id_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_nodecount_withgridid_f, CG_IRIC_READ_GRID_NODECOUNT_WITHGRIDID_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_NodeCount_WithGridId(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_cellcount_withgridid_f, CG_IRIC_READ_GRID_CELLCOUNT_WITHGRIDID_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_CellCount_WithGridId(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_ifacecount_withgridid_f, CG_IRIC_READ_GRID_IFACECOUNT_WITHGRIDID_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_IFaceCount_WithGridId(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_jfacecount_withgridid_f, CG_IRIC_READ_GRID_JFACECOUNT_WITHGRIDID_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_JFaceCount_WithGridId(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_kfacecount_withgridid_f, CG_IRIC_READ_GRID_KFACECOUNT_WITHGRIDID_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_KFaceCount_WithGridId(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_node_withgridid_f, CG_IRIC_READ_GRID_REAL_NODE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Node_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_node_withgridid_f, CG_IRIC_READ_GRID_INTEGER_NODE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Node_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_cell_withgridid_f, CG_IRIC_READ_GRID_REAL_CELL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Cell_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_cell_withgridid_f, CG_IRIC_READ_GRID_INTEGER_CELL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Cell_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimensionsize_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSIONSIZE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), STR_PSTR(dimname), int* count, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimensionSize_WithGridId(*fid, *gid, c_name, c_dimname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_integer_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), STR_PSTR(dimname), int* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId(*fid, *gid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_real_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), STR_PSTR(dimname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId(*fid, *gid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltimesize_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALTIMESIZE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTimeSize_WithGridId(*fid, *gid, c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltime_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALTIME_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* time_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTime_WithGridId(*fid, *gid, c_name, time_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_node_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_NODE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId(*fid, *gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_node_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_NODE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId(*fid, *gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_cell_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_CELL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId(*fid, *gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_cell_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_CELL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId(*fid, *gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid1d_coords_withgridid_f, CG_IRIC_WRITE_GRID1D_COORDS_WITHGRIDID_F) (int* fid, int* isize, double* x_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid1d_Coords_WithGridId(*fid, *isize, x_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid2d_coords_withgridid_f, CG_IRIC_WRITE_GRID2D_COORDS_WITHGRIDID_F) (int* fid, int* isize, int* jsize, double* x_arr, double* y_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid2d_Coords_WithGridId(*fid, *isize, *jsize, x_arr, y_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid3d_coords_withgridid_f, CG_IRIC_WRITE_GRID3D_COORDS_WITHGRIDID_F) (int* fid, int* isize, int* jsize, int* ksize, double* x_arr, double* y_arr, double* z_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid3d_Coords_WithGridId(*fid, *isize, *jsize, *ksize, x_arr, y_arr, z_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_node_withgridid_f, CG_IRIC_WRITE_GRID_REAL_NODE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Node_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_node_withgridid_f, CG_IRIC_WRITE_GRID_INTEGER_NODE_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Node_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_cell_withgridid_f, CG_IRIC_WRITE_GRID_REAL_CELL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Cell_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_cell_withgridid_f, CG_IRIC_WRITE_GRID_INTEGER_CELL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Cell_WithGridId(*fid, *gid, c_name, v_arr);
}


// from iriclib_gui_coorp.h
void IRICLIBDLL FMNAME(iric_check_cancel_f, IRIC_CHECK_CANCEL_F) (int *ier) {
	*ier = iRIC_Check_Cancel();
}


// from iriclib_init.h
void IRICLIBDLL FMNAME(cg_iric_open_f, CG_IRIC_OPEN_F) (STR_PSTR(filename), int* mode, int* fid, int *ier STR_PLEN(filename)) {
	char c_filename[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(filename), STR_LEN(filename), c_filename, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Open(c_filename, *mode, fid);
}

void IRICLIBDLL FMNAME(cg_iric_close_f, CG_IRIC_CLOSE_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Close(*fid);
}

void IRICLIBDLL FMNAME(iric_initoption_f, IRIC_INITOPTION_F) (int* option, int *ier) {
	*ier = iRIC_InitOption(*option);
}

void IRICLIBDLL FMNAME(cg_iric_flush_f, CG_IRIC_FLUSH_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Flush(*fid);
}


// from iriclib_not_withbaseid.h
void IRICLIBDLL FMNAME(cg_iric_read_complex_count_f, CG_IRIC_READ_COMPLEX_COUNT_F) (int* fid, STR_PSTR(groupname), int* num, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Count(*fid, c_groupname, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_integer_f, CG_IRIC_READ_COMPLEX_INTEGER_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Integer(*fid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_real_f, CG_IRIC_READ_COMPLEX_REAL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Real(*fid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_realsingle_f, CG_IRIC_READ_COMPLEX_REALSINGLE_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_RealSingle(*fid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_stringlen_f, CG_IRIC_READ_COMPLEX_STRINGLEN_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_StringLen(*fid, c_groupname, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_string_f, CG_IRIC_READ_COMPLEX_STRING_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_String(*fid, c_groupname, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalsize_f, CG_IRIC_READ_COMPLEX_FUNCTIONALSIZE_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalSize(*fid, c_groupname, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional(*fid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName(*fid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_realsingle_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_REALSINGLE_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_RealSingle(*fid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_realsingle_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_REALSINGLE_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_RealSingle(*fid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_stringlen_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRINGLEN_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_StringLen(*fid, c_groupname, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_string_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRING_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_String(*fid, c_groupname, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_complex_f, CG_IRIC_CLEAR_COMPLEX_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Clear_Complex(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_integer_f, CG_IRIC_WRITE_COMPLEX_INTEGER_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Integer(*fid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_real_f, CG_IRIC_WRITE_COMPLEX_REAL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Real(*fid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_string_f, CG_IRIC_WRITE_COMPLEX_STRING_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(value)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_String(*fid, c_groupname, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functional_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONAL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Functional(*fid, c_groupname, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_FunctionalWithName(*fid, c_groupname, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_string_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_STRING_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_String(*fid, c_groupname, *num, c_name, c_paramname, c_value);
}


// from iriclib_not_withgridid.h
void IRICLIBDLL FMNAME(cg_iric_read_bc_count_f, CG_IRIC_READ_BC_COUNT_F) (int* fid, STR_PSTR(type), int* num STR_PLEN(type)) {
	int ier;

	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, &ier);
	if (ier != 0) return;

	cg_iRIC_Read_BC_Count(*fid, c_type, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indicessize_f, CG_IRIC_READ_BC_INDICESSIZE_F) (int* fid, STR_PSTR(type), int* num, int* size, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_IndicesSize(*fid, c_type, *num, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indices_f, CG_IRIC_READ_BC_INDICES_F) (int* fid, STR_PSTR(type), int* num, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Indices(*fid, c_type, *num, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_integer_f, CG_IRIC_READ_BC_INTEGER_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Integer(*fid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_real_f, CG_IRIC_READ_BC_REAL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Real(*fid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_realsingle_f, CG_IRIC_READ_BC_REALSINGLE_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_RealSingle(*fid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_stringlen_f, CG_IRIC_READ_BC_STRINGLEN_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_StringLen(*fid, c_type, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_string_f, CG_IRIC_READ_BC_STRING_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_String(*fid, c_type, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalsize_f, CG_IRIC_READ_BC_FUNCTIONALSIZE_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalSize(*fid, c_type, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_f, CG_IRIC_READ_BC_FUNCTIONAL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional(*fid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName(*fid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_realsingle_f, CG_IRIC_READ_BC_FUNCTIONAL_REALSINGLE_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_RealSingle(*fid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_realsingle_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_REALSINGLE_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_RealSingle(*fid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_stringlen_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRINGLEN_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen(*fid, c_type, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_string_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRING_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_String(*fid, c_type, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_bc_f, CG_IRIC_CLEAR_BC_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Clear_BC(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices_f, CG_IRIC_WRITE_BC_INDICES_F) (int* fid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices(*fid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices2_f, CG_IRIC_WRITE_BC_INDICES2_F) (int* fid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices2(*fid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_integer_f, CG_IRIC_WRITE_BC_INTEGER_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Integer(*fid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_real_f, CG_IRIC_WRITE_BC_REAL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Real(*fid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_string_f, CG_IRIC_WRITE_BC_STRING_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(value)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_String(*fid, c_type, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functional_f, CG_IRIC_WRITE_BC_FUNCTIONAL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Functional(*fid, c_type, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_FunctionalWithName(*fid, c_type, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_string_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_STRING_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_FunctionalWithName_String(*fid, c_type, *num, c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_node_f, CG_IRIC_READ_GRID_COMPLEX_NODE_F) (int* fid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Node(*fid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_cell_f, CG_IRIC_READ_GRID_COMPLEX_CELL_F) (int* fid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Cell(*fid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_node_f, CG_IRIC_WRITE_GRID_COMPLEX_NODE_F) (int* fid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Node(*fid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_cell_f, CG_IRIC_WRITE_GRID_COMPLEX_CELL_F) (int* fid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Cell(*fid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_str_size_f, CG_IRIC_READ_GRID2D_STR_SIZE_F) (int* fid, int* isize, int* jsize, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Str_Size(*fid, isize, jsize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_coords_f, CG_IRIC_READ_GRID2D_COORDS_F) (int* fid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Coords(*fid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_str_size_f, CG_IRIC_READ_GRID3D_STR_SIZE_F) (int* fid, int* isize, int* jsize, int* ksize, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Str_Size(*fid, isize, jsize, ksize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_coords_f, CG_IRIC_READ_GRID3D_COORDS_F) (int* fid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Coords(*fid, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_triangleelementssize_f, CG_IRIC_READ_GRID_TRIANGLEELEMENTSSIZE_F) (int* fid, int* size, int *ier) {
	*ier = cg_iRIC_Read_Grid_TriangleElementsSize(*fid, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_triangleelements_f, CG_IRIC_READ_GRID_TRIANGLEELEMENTS_F) (int* fid, int* id_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid_TriangleElements(*fid, id_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_nodecount_f, CG_IRIC_READ_GRID_NODECOUNT_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_NodeCount(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_cellcount_f, CG_IRIC_READ_GRID_CELLCOUNT_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_CellCount(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_ifacecount_f, CG_IRIC_READ_GRID_IFACECOUNT_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_IFaceCount(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_jfacecount_f, CG_IRIC_READ_GRID_JFACECOUNT_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_JFaceCount(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_kfacecount_f, CG_IRIC_READ_GRID_KFACECOUNT_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_KFaceCount(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_node_f, CG_IRIC_READ_GRID_REAL_NODE_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Node(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_node_f, CG_IRIC_READ_GRID_INTEGER_NODE_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Node(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_cell_f, CG_IRIC_READ_GRID_REAL_CELL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Cell(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_cell_f, CG_IRIC_READ_GRID_INTEGER_CELL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Cell(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimensionsize_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSIONSIZE_F) (int* fid, STR_PSTR(name), STR_PSTR(dimname), int* count, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimensionSize(*fid, c_name, c_dimname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_integer_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_INTEGER_F) (int* fid, STR_PSTR(name), STR_PSTR(dimname), int* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Integer(*fid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_real_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_REAL_F) (int* fid, STR_PSTR(name), STR_PSTR(dimname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Real(*fid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltimesize_f, CG_IRIC_READ_GRID_FUNCTIONALTIMESIZE_F) (int* fid, STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTimeSize(*fid, c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltime_f, CG_IRIC_READ_GRID_FUNCTIONALTIME_F) (int* fid, STR_PSTR(name), double* time_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTime(*fid, c_name, time_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_node_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_NODE_F) (int* fid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Node(*fid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_node_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_NODE_F) (int* fid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Node(*fid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_cell_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_CELL_F) (int* fid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Cell(*fid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_cell_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_CELL_F) (int* fid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Cell(*fid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid1d_coords_f, CG_IRIC_WRITE_GRID1D_COORDS_F) (int* fid, int* isize, double* x_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid1d_Coords(*fid, *isize, x_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid2d_coords_f, CG_IRIC_WRITE_GRID2D_COORDS_F) (int* fid, int* isize, int* jsize, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid2d_Coords(*fid, *isize, *jsize, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid3d_coords_f, CG_IRIC_WRITE_GRID3D_COORDS_F) (int* fid, int* isize, int* jsize, int* ksize, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid3d_Coords(*fid, *isize, *jsize, *ksize, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_node_f, CG_IRIC_WRITE_GRID_REAL_NODE_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Node(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_node_f, CG_IRIC_WRITE_GRID_INTEGER_NODE_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Node(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_cell_f, CG_IRIC_WRITE_GRID_REAL_CELL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Cell(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_cell_f, CG_IRIC_WRITE_GRID_INTEGER_CELL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Cell(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_integer_f, CG_IRIC_READ_SOL_CELL_INTEGER_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Integer(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_real_f, CG_IRIC_READ_SOL_CELL_REAL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Real(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_integer_f, CG_IRIC_WRITE_SOL_CELL_INTEGER_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Integer(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_real_f, CG_IRIC_WRITE_SOL_CELL_REAL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Real(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid2d_coords_f, CG_IRIC_READ_SOL_GRID2D_COORDS_F) (int* fid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid2d_Coords(*fid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid3d_coords_f, CG_IRIC_READ_SOL_GRID3D_COORDS_F) (int* fid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid3d_Coords(*fid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid2d_coords_f, CG_IRIC_WRITE_SOL_GRID2D_COORDS_F) (int* fid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid2d_Coords(*fid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid3d_coords_f, CG_IRIC_WRITE_SOL_GRID3D_COORDS_F) (int* fid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid3d_Coords(*fid, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_integer_f, CG_IRIC_READ_SOL_IFACE_INTEGER_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Integer(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_real_f, CG_IRIC_READ_SOL_IFACE_REAL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Real(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_integer_f, CG_IRIC_WRITE_SOL_IFACE_INTEGER_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Integer(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_real_f, CG_IRIC_WRITE_SOL_IFACE_REAL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Real(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_integer_f, CG_IRIC_READ_SOL_JFACE_INTEGER_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Integer(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_real_f, CG_IRIC_READ_SOL_JFACE_REAL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Real(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_integer_f, CG_IRIC_WRITE_SOL_JFACE_INTEGER_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Integer(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_real_f, CG_IRIC_WRITE_SOL_JFACE_REAL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Real(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_integer_f, CG_IRIC_READ_SOL_KFACE_INTEGER_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Integer(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_real_f, CG_IRIC_READ_SOL_KFACE_REAL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Real(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_integer_f, CG_IRIC_WRITE_SOL_KFACE_INTEGER_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Integer(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_real_f, CG_IRIC_WRITE_SOL_KFACE_REAL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Real(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_integer_f, CG_IRIC_READ_SOL_NODE_INTEGER_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Integer(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_real_f, CG_IRIC_READ_SOL_NODE_REAL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Real(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_integer_f, CG_IRIC_WRITE_SOL_NODE_INTEGER_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Integer(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_real_f, CG_IRIC_WRITE_SOL_NODE_REAL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Real(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_count_f, CG_IRIC_READ_SOL_PARTICLE_COUNT_F) (int* fid, int* step, int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Count(*fid, *step, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos2d_f, CG_IRIC_READ_SOL_PARTICLE_POS2D_F) (int* fid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos2d(*fid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos3d_f, CG_IRIC_READ_SOL_PARTICLE_POS3D_F) (int* fid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos3d(*fid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_real_f, CG_IRIC_READ_SOL_PARTICLE_REAL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Real(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_integer_f, CG_IRIC_READ_SOL_PARTICLE_INTEGER_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Integer(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos2d_f, CG_IRIC_WRITE_SOL_PARTICLE_POS2D_F) (int* fid, int* count, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos2d(*fid, *count, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos3d_f, CG_IRIC_WRITE_SOL_PARTICLE_POS3D_F) (int* fid, int* count, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos3d(*fid, *count, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_real_f, CG_IRIC_WRITE_SOL_PARTICLE_REAL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Real(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_integer_f, CG_IRIC_WRITE_SOL_PARTICLE_INTEGER_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Integer(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_count_f, CG_IRIC_READ_SOL_PARTICLEGROUP_COUNT_F) (int* fid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Count(*fid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos2d_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS2D_F) (int* fid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos2d(*fid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos3d_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS3D_F) (int* fid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, double* z_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos3d(*fid, *step, c_groupname, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_real_f, CG_IRIC_READ_SOL_PARTICLEGROUP_REAL_F) (int* fid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Real(*fid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_integer_f, CG_IRIC_READ_SOL_PARTICLEGROUP_INTEGER_F) (int* fid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Integer(*fid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupbegin_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPBEGIN_F) (int* fid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin(*fid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupend_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPEND_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos2d_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS2D_F) (int* fid, double* x, double* y, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos2d(*fid, *x, *y);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos3d_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS3D_F) (int* fid, double* x, double* y, double* z, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos3d(*fid, *x, *y, *z);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_integer_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_INTEGER_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Integer(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_real_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_REAL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Real(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_datacount_f, CG_IRIC_READ_SOL_POLYDATA_DATACOUNT_F) (int* fid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_DataCount(*fid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_coordinatecount_f, CG_IRIC_READ_SOL_POLYDATA_COORDINATECOUNT_F) (int* fid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_CoordinateCount(*fid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_pos2d_f, CG_IRIC_READ_SOL_POLYDATA_POS2D_F) (int* fid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Pos2d(*fid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_type_f, CG_IRIC_READ_SOL_POLYDATA_TYPE_F) (int* fid, int* step, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Type(*fid, *step, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_real_f, CG_IRIC_READ_SOL_POLYDATA_REAL_F) (int* fid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Real(*fid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_integer_f, CG_IRIC_READ_SOL_POLYDATA_INTEGER_F) (int* fid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Integer(*fid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupbegin_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPBEGIN_F) (int* fid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_GroupBegin(*fid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupend_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPEND_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_GroupEnd(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polygon_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYGON_F) (int* fid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polygon(*fid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polyline_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYLINE_F) (int* fid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polyline(*fid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_integer_f, CG_IRIC_WRITE_SOL_POLYDATA_INTEGER_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Integer(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_real_f, CG_IRIC_WRITE_SOL_POLYDATA_REAL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Real(*fid, c_name, *value);
}


// from iriclib_solution.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_count_f, CG_IRIC_READ_SOL_COUNT_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Count(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_time_f, CG_IRIC_READ_SOL_TIME_F) (int* fid, int* step, double* time, int *ier) {
	*ier = cg_iRIC_Read_Sol_Time(*fid, *step, time);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iteration_f, CG_IRIC_READ_SOL_ITERATION_F) (int* fid, int* step, int* index, int *ier) {
	*ier = cg_iRIC_Read_Sol_Iteration(*fid, *step, index);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_integer_f, CG_IRIC_READ_SOL_BASEITERATIVE_INTEGER_F) (int* fid, int* step, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_Integer(*fid, *step, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_real_f, CG_IRIC_READ_SOL_BASEITERATIVE_REAL_F) (int* fid, int* step, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_Real(*fid, *step, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_stringlen_f, CG_IRIC_READ_SOL_BASEITERATIVE_STRINGLEN_F) (int* fid, int* step, STR_PSTR(name), int* length, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_StringLen(*fid, *step, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_string_f, CG_IRIC_READ_SOL_BASEITERATIVE_STRING_F) (int* fid, int* step, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_String(*fid, *step, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_time_f, CG_IRIC_WRITE_SOL_TIME_F) (int* fid, double* time, int *ier) {
	*ier = cg_iRIC_Write_Sol_Time(*fid, *time);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iteration_f, CG_IRIC_WRITE_SOL_ITERATION_F) (int* fid, int* index, int *ier) {
	*ier = cg_iRIC_Write_Sol_Iteration(*fid, *index);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_integer_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_INTEGER_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_Integer(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_real_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_REAL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_Real(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_string_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_STRING_F) (int* fid, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_String(*fid, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_errorcode_f, CG_IRIC_WRITE_ERRORCODE_F) (int* fid, int* errorcode, int *ier) {
	*ier = cg_iRIC_Write_ErrorCode(*fid, *errorcode);
}


// from iriclib_sol_cell.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_integer_withgridid_f, CG_IRIC_READ_SOL_CELL_INTEGER_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Integer_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_real_withgridid_f, CG_IRIC_READ_SOL_CELL_REAL_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Real_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_integer_withgridid_f, CG_IRIC_WRITE_SOL_CELL_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Integer_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_real_withgridid_f, CG_IRIC_WRITE_SOL_CELL_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Real_WithGridId(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_gridcoord.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_grid2d_coords_withgridid_f, CG_IRIC_READ_SOL_GRID2D_COORDS_WITHGRIDID_F) (int* fid, int* gid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid2d_Coords_WithGridId(*fid, *gid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid3d_coords_withgridid_f, CG_IRIC_READ_SOL_GRID3D_COORDS_WITHGRIDID_F) (int* fid, int* gid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid3d_Coords_WithGridId(*fid, *gid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid2d_coords_withgridid_f, CG_IRIC_WRITE_SOL_GRID2D_COORDS_WITHGRIDID_F) (int* fid, int* gid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid2d_Coords_WithGridId(*fid, *gid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid3d_coords_withgridid_f, CG_IRIC_WRITE_SOL_GRID3D_COORDS_WITHGRIDID_F) (int* fid, int* gid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid3d_Coords_WithGridId(*fid, *gid, x_arr, y_arr, z_arr);
}


// from iriclib_sol_iface.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_integer_withgridid_f, CG_IRIC_READ_SOL_IFACE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Integer_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_real_withgridid_f, CG_IRIC_READ_SOL_IFACE_REAL_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Real_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_integer_withgridid_f, CG_IRIC_WRITE_SOL_IFACE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Integer_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_real_withgridid_f, CG_IRIC_WRITE_SOL_IFACE_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Real_WithGridId(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_jface.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_integer_withgridid_f, CG_IRIC_READ_SOL_JFACE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Integer_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_real_withgridid_f, CG_IRIC_READ_SOL_JFACE_REAL_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Real_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_integer_withgridid_f, CG_IRIC_WRITE_SOL_JFACE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Integer_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_real_withgridid_f, CG_IRIC_WRITE_SOL_JFACE_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Real_WithGridId(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_kface.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_integer_withgridid_f, CG_IRIC_READ_SOL_KFACE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Integer_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_real_withgridid_f, CG_IRIC_READ_SOL_KFACE_REAL_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Real_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_integer_withgridid_f, CG_IRIC_WRITE_SOL_KFACE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Integer_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_real_withgridid_f, CG_IRIC_WRITE_SOL_KFACE_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Real_WithGridId(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_node.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_node_integer_withgridid_f, CG_IRIC_READ_SOL_NODE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Integer_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_real_withgridid_f, CG_IRIC_READ_SOL_NODE_REAL_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Real_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_integer_withgridid_f, CG_IRIC_WRITE_SOL_NODE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Integer_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_real_withgridid_f, CG_IRIC_WRITE_SOL_NODE_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Real_WithGridId(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_particle.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_count_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_COUNT_WITHGRIDID_F) (int* fid, int* gid, int* step, int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Count_WithGridId(*fid, *gid, *step, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos2d_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_POS2D_WITHGRIDID_F) (int* fid, int* gid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(*fid, *gid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos3d_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_POS3D_WITHGRIDID_F) (int* fid, int* gid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(*fid, *gid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_real_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_REAL_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Real_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_integer_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Integer_WithGridId(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos2d_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLE_POS2D_WITHGRIDID_F) (int* fid, int* gid, int* count, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(*fid, *gid, *count, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos3d_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLE_POS3D_WITHGRIDID_F) (int* fid, int* gid, int* count, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(*fid, *gid, *count, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_real_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLE_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Real_WithGridId(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_integer_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLE_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Integer_WithGridId(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_particlegroup.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_count_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_COUNT_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Count_WithGridId(*fid, *gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos2d_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS2D_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId(*fid, *gid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos3d_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS3D_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, double* z_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId(*fid, *gid, *step, c_groupname, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_real_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_REAL_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId(*fid, *gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_integer_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_INTEGER_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId(*fid, *gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupbegin_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPBEGIN_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_WithGridId(*fid, *gid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupend_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPEND_WITHGRIDID_F) (int* fid, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_WithGridId(*fid, *gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos2d_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS2D_WITHGRIDID_F) (int* fid, int* gid, double* x, double* y, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos2d_WithGridId(*fid, *gid, *x, *y);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos3d_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS3D_WITHGRIDID_F) (int* fid, int* gid, double* x, double* y, double* z, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos3d_WithGridId(*fid, *gid, *x, *y, *z);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_integer_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Integer_WithGridId(*fid, *gid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_real_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Real_WithGridId(*fid, *gid, c_name, *value);
}


// from iriclib_sol_polydata.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_datacount_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_DATACOUNT_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_DataCount_WithGridId(*fid, *gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_coordinatecount_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_COORDINATECOUNT_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_CoordinateCount_WithGridId(*fid, *gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_pos2d_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_POS2D_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(*fid, *gid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_type_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_TYPE_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Type_WithGridId(*fid, *gid, *step, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_real_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_REAL_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Real_WithGridId(*fid, *gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_integer_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_INTEGER_WITHGRIDID_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(*fid, *gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupbegin_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPBEGIN_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_GroupBegin_WithGridId(*fid, *gid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupend_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPEND_WITHGRIDID_F) (int* fid, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_GroupEnd_WithGridId(*fid, *gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polygon_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYGON_WITHGRIDID_F) (int* fid, int* gid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(*fid, *gid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polyline_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYLINE_WITHGRIDID_F) (int* fid, int* gid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(*fid, *gid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_integer_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_INTEGER_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Integer_WithGridId(*fid, *gid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_real_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_REAL_WITHGRIDID_F) (int* fid, int* gid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Real_WithGridId(*fid, *gid, c_name, *value);
}


} // extern "C"
