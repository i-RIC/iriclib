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
void IRICLIBDLL FMNAME(cg_iric_read_bc_count_withgridid_mul_f, CG_IRIC_READ_BC_COUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num STR_PLEN(type)) {
	int ier;

	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, &ier);
	if (ier != 0) return;

	cg_iRIC_Read_BC_Count_WithGridId_Mul(*fid, *gid, c_type, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indicessize_withgridid_mul_f, CG_IRIC_READ_BC_INDICESSIZE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, int* size, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_IndicesSize_WithGridId_Mul(*fid, *gid, c_type, *num, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indices_withgridid_mul_f, CG_IRIC_READ_BC_INDICES_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Indices_WithGridId_Mul(*fid, *gid, c_type, *num, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_integer_withgridid_mul_f, CG_IRIC_READ_BC_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Integer_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_real_withgridid_mul_f, CG_IRIC_READ_BC_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Real_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_realsingle_withgridid_mul_f, CG_IRIC_READ_BC_REALSINGLE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_RealSingle_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_stringlen_withgridid_mul_f, CG_IRIC_READ_BC_STRINGLEN_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_StringLen_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_string_withgridid_mul_f, CG_IRIC_READ_BC_STRING_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_String_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalsize_withgridid_mul_f, CG_IRIC_READ_BC_FUNCTIONALSIZE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalSize_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_withgridid_mul_f, CG_IRIC_READ_BC_FUNCTIONAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_withgridid_mul_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_realsingle_withgridid_mul_f, CG_IRIC_READ_BC_FUNCTIONAL_REALSINGLE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_RealSingle_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_realsingle_withgridid_mul_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_REALSINGLE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_RealSingle_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_stringlen_withgridid_mul_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRINGLEN_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_string_withgridid_mul_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRING_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
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

	*ier = cg_iRIC_Read_BC_FunctionalWithName_String_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_bc_withgridid_mul_f, CG_IRIC_CLEAR_BC_WITHGRIDID_MUL_F) (int* fid, int* gid, int *ier) {
	*ier = cg_iRIC_Clear_BC_WithGridId_Mul(*fid, *gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices_withgridid_mul_f, CG_IRIC_WRITE_BC_INDICES_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices_WithGridId_Mul(*fid, *gid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices2_withgridid_mul_f, CG_IRIC_WRITE_BC_INDICES2_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices2_WithGridId_Mul(*fid, *gid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_integer_withgridid_mul_f, CG_IRIC_WRITE_BC_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Integer_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_real_withgridid_mul_f, CG_IRIC_WRITE_BC_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Real_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_string_withgridid_mul_f, CG_IRIC_WRITE_BC_STRING_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(value)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_String_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functional_withgridid_mul_f, CG_IRIC_WRITE_BC_FUNCTIONAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Functional_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_withgridid_mul_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_FunctionalWithName_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_string_withgridid_mul_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_STRING_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
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

	*ier = cg_iRIC_Write_BC_FunctionalWithName_String_WithGridId_Mul(*fid, *gid, c_type, *num, c_name, c_paramname, c_value);
}


// from iriclib_cc.h
void IRICLIBDLL FMNAME(cg_iric_read_integer_mul_f, CG_IRIC_READ_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Integer_Mul(*fid, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_real_mul_f, CG_IRIC_READ_REAL_MUL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Real_Mul(*fid, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_realsingle_mul_f, CG_IRIC_READ_REALSINGLE_MUL_F) (int* fid, STR_PSTR(name), float* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_RealSingle_Mul(*fid, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_stringlen_mul_f, CG_IRIC_READ_STRINGLEN_MUL_F) (int* fid, STR_PSTR(name), int* length, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_StringLen_Mul(*fid, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_string_mul_f, CG_IRIC_READ_STRING_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_String_Mul(*fid, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalsize_mul_f, CG_IRIC_READ_FUNCTIONALSIZE_MUL_F) (int* fid, STR_PSTR(name), int* size, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalSize_Mul(*fid, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_functional_mul_f, CG_IRIC_READ_FUNCTIONAL_MUL_F) (int* fid, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Functional_Mul(*fid, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_mul_f, CG_IRIC_READ_FUNCTIONALWITHNAME_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_Mul(*fid, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functional_realsingle_mul_f, CG_IRIC_READ_FUNCTIONAL_REALSINGLE_MUL_F) (int* fid, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Functional_RealSingle_Mul(*fid, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_realsingle_mul_f, CG_IRIC_READ_FUNCTIONALWITHNAME_REALSINGLE_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_RealSingle_Mul(*fid, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_string_mul_f, CG_IRIC_READ_FUNCTIONALWITHNAME_STRING_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_String_Mul(*fid, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_stringlen_mul_f, CG_IRIC_READ_FUNCTIONALWITHNAME_STRINGLEN_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_StringLen_Mul(*fid, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_write_integer_mul_f, CG_IRIC_WRITE_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Integer_Mul(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_real_mul_f, CG_IRIC_WRITE_REAL_MUL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Real_Mul(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_string_mul_f, CG_IRIC_WRITE_STRING_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_String_Mul(*fid, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_functional_mul_f, CG_IRIC_WRITE_FUNCTIONAL_MUL_F) (int* fid, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Functional_Mul(*fid, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_functionalwithname_mul_f, CG_IRIC_WRITE_FUNCTIONALWITHNAME_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_FunctionalWithName_Mul(*fid, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_functionalwithname_string_mul_f, CG_IRIC_WRITE_FUNCTIONALWITHNAME_STRING_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_FunctionalWithName_String_Mul(*fid, c_name, c_paramname, c_value);
}


// from iriclib_complex.h
void IRICLIBDLL FMNAME(cg_iric_read_complex_count_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_COUNT_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Count_WithBaseId_Mul(*fid, *bid, c_groupname, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_integer_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_INTEGER_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Integer_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_real_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_REAL_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Real_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_realsingle_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_REALSINGLE_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_RealSingle_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_stringlen_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_STRINGLEN_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_StringLen_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_string_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_STRING_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_String_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalsize_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALSIZE_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalSize_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_realsingle_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_REALSINGLE_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_RealSingle_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_realsingle_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_REALSINGLE_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_stringlen_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRINGLEN_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_StringLen_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_string_withbaseid_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRING_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
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

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_String_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_node_withgridid_mul_f, CG_IRIC_READ_GRID_COMPLEX_NODE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Node_WithGridId_Mul(*fid, *gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_cell_withgridid_mul_f, CG_IRIC_READ_GRID_COMPLEX_CELL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Cell_WithGridId_Mul(*fid, *gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_clear_complex_withbaseid_mul_f, CG_IRIC_CLEAR_COMPLEX_WITHBASEID_MUL_F) (int* fid, int* bid, int *ier) {
	*ier = cg_iRIC_Clear_Complex_WithBaseId_Mul(*fid, *bid);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_integer_withbaseid_mul_f, CG_IRIC_WRITE_COMPLEX_INTEGER_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Integer_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_real_withbaseid_mul_f, CG_IRIC_WRITE_COMPLEX_REAL_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Real_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_string_withbaseid_mul_f, CG_IRIC_WRITE_COMPLEX_STRING_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(value)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_String_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functional_withbaseid_mul_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONAL_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Functional_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_withbaseid_mul_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_string_withbaseid_mul_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_STRING_WITHBASEID_MUL_F) (int* fid, int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
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

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_String_WithBaseId_Mul(*fid, *bid, c_groupname, *num, c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_node_withgridid_mul_f, CG_IRIC_WRITE_GRID_COMPLEX_NODE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Node_WithGridId_Mul(*fid, *gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_cell_withgridid_mul_f, CG_IRIC_WRITE_GRID_COMPLEX_CELL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Cell_WithGridId_Mul(*fid, *gid, c_groupname, v_arr);
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
void IRICLIBDLL FMNAME(cg_iric_read_geo_count_mul_f, CG_IRIC_READ_GEO_COUNT_MUL_F) (int* fid, STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Geo_Count_Mul(*fid, c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_geo_filename_mul_f, CG_IRIC_READ_GEO_FILENAME_MUL_F) (int* fid, STR_PSTR(name), int* geoid, STR_PSTR(strvalue), int* type, int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Geo_Filename_Mul(*fid, c_name, *geoid, c_strvalue, type);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}


// from iriclib_grid.h
void IRICLIBDLL FMNAME(cg_iric_read_grid2d_str_size_withgridid_mul_f, CG_IRIC_READ_GRID2D_STR_SIZE_WITHGRIDID_MUL_F) (int* fid, int* gid, int* isize, int* jsize, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Str_Size_WithGridId_Mul(*fid, *gid, isize, jsize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_coords_withgridid_mul_f, CG_IRIC_READ_GRID2D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* gid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Coords_WithGridId_Mul(*fid, *gid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_str_size_withgridid_mul_f, CG_IRIC_READ_GRID3D_STR_SIZE_WITHGRIDID_MUL_F) (int* fid, int* gid, int* isize, int* jsize, int* ksize, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Str_Size_WithGridId_Mul(*fid, *gid, isize, jsize, ksize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_coords_withgridid_mul_f, CG_IRIC_READ_GRID3D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* gid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Coords_WithGridId_Mul(*fid, *gid, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_gettriangleelementssize_withgridid_mul_f, CG_IRIC_GETTRIANGLEELEMENTSSIZE_WITHGRIDID_MUL_F) (int* fid, int* gid, int* size, int *ier) {
	*ier = cg_iRIC_GetTriangleElementsSize_WithGridId_Mul(*fid, *gid, size);
}

void IRICLIBDLL FMNAME(cg_iric_gettriangleelements_withgridid_mul_f, CG_IRIC_GETTRIANGLEELEMENTS_WITHGRIDID_MUL_F) (int* fid, int* gid, int* id_arr, int *ier) {
	*ier = cg_iRIC_GetTriangleElements_WithGridId_Mul(*fid, *gid, id_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_nodecount_withgridid_mul_f, CG_IRIC_READ_GRID_NODECOUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_NodeCount_WithGridId_Mul(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_cellcount_withgridid_mul_f, CG_IRIC_READ_GRID_CELLCOUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_CellCount_WithGridId_Mul(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_ifacecount_withgridid_mul_f, CG_IRIC_READ_GRID_IFACECOUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_IFaceCount_WithGridId_Mul(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_jfacecount_withgridid_mul_f, CG_IRIC_READ_GRID_JFACECOUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_JFaceCount_WithGridId_Mul(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_kfacecount_withgridid_mul_f, CG_IRIC_READ_GRID_KFACECOUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_KFaceCount_WithGridId_Mul(*fid, *gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_node_withgridid_mul_f, CG_IRIC_READ_GRID_REAL_NODE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Node_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_node_withgridid_mul_f, CG_IRIC_READ_GRID_INTEGER_NODE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Node_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_cell_withgridid_mul_f, CG_IRIC_READ_GRID_REAL_CELL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Cell_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_cell_withgridid_mul_f, CG_IRIC_READ_GRID_INTEGER_CELL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Cell_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimensionsize_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSIONSIZE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), STR_PSTR(dimname), int* count, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimensionSize_WithGridId_Mul(*fid, *gid, c_name, c_dimname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_integer_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), STR_PSTR(dimname), int* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId_Mul(*fid, *gid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_real_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), STR_PSTR(dimname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId_Mul(*fid, *gid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltimesize_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONALTIMESIZE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTimeSize_WithGridId_Mul(*fid, *gid, c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltime_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONALTIME_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* time_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTime_WithGridId_Mul(*fid, *gid, c_name, time_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_node_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_NODE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId_Mul(*fid, *gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_node_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_NODE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId_Mul(*fid, *gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_cell_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_CELL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId_Mul(*fid, *gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_cell_withgridid_mul_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_CELL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId_Mul(*fid, *gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid1d_coords_withgridid_mul_f, CG_IRIC_WRITE_GRID1D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* isize, double* x_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid1d_Coords_WithGridId_Mul(*fid, *isize, x_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid2d_coords_withgridid_mul_f, CG_IRIC_WRITE_GRID2D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* isize, int* jsize, double* x_arr, double* y_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid2d_Coords_WithGridId_Mul(*fid, *isize, *jsize, x_arr, y_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid3d_coords_withgridid_mul_f, CG_IRIC_WRITE_GRID3D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* isize, int* jsize, int* ksize, double* x_arr, double* y_arr, double* z_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid3d_Coords_WithGridId_Mul(*fid, *isize, *jsize, *ksize, x_arr, y_arr, z_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_node_withgridid_mul_f, CG_IRIC_WRITE_GRID_REAL_NODE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Node_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_node_withgridid_mul_f, CG_IRIC_WRITE_GRID_INTEGER_NODE_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Node_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_cell_withgridid_mul_f, CG_IRIC_WRITE_GRID_REAL_CELL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Cell_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_cell_withgridid_mul_f, CG_IRIC_WRITE_GRID_INTEGER_CELL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Cell_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}


// from iriclib_gui_coorp.h
void IRICLIBDLL FMNAME(iric_write_sol_start_f, IRIC_WRITE_SOL_START_F) (STR_PSTR(fname), int *ier STR_PLEN(fname)) {
	char c_fname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(fname), STR_LEN(fname), c_fname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = iRIC_Write_Sol_Start(c_fname);
}

void IRICLIBDLL FMNAME(iric_write_sol_end_f, IRIC_WRITE_SOL_END_F) (STR_PSTR(fname), int *ier STR_PLEN(fname)) {
	char c_fname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(fname), STR_LEN(fname), c_fname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = iRIC_Write_Sol_End(c_fname);
}

void IRICLIBDLL FMNAME(iric_check_lock_f, IRIC_CHECK_LOCK_F) (STR_PSTR(fname), int *ier STR_PLEN(fname)) {
	char c_fname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(fname), STR_LEN(fname), c_fname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = iRIC_Check_Lock(c_fname);
}

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

void IRICLIBDLL FMNAME(cg_iric_init_f, CG_IRIC_INIT_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Init(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_initread_f, CG_IRIC_INITREAD_F) (int* fid, int *ier) {
	*ier = cg_iRIC_InitRead(*fid);
}

void IRICLIBDLL FMNAME(iric_initoption_f, IRIC_INITOPTION_F) (int* option, int *ier) {
	*ier = iRIC_InitOption(*option);
}

void IRICLIBDLL FMNAME(cg_iric_flush_f, CG_IRIC_FLUSH_F) (STR_PSTR(name), int* fid, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Flush(c_name, *fid);
}

void IRICLIBDLL FMNAME(cg_iric_gotobase_f, CG_IRIC_GOTOBASE_F) (int* fid, int* B, int *ier) {
	*ier = cg_iRIC_GotoBase(*fid, B);
}

void IRICLIBDLL FMNAME(cg_iric_gotocc_f, CG_IRIC_GOTOCC_F) (int* fid, int *ier) {
	*ier = cg_iRIC_GotoCC(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_gotorawdatatop_f, CG_IRIC_GOTORAWDATATOP_F) (int* fid, int *ier) {
	*ier = cg_iRIC_GotoRawDataTop(*fid);
}


// from iriclib_not_mul.h
void IRICLIBDLL FMNAME(cg_iric_read_bc_count_withgridid_f, CG_IRIC_READ_BC_COUNT_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num STR_PLEN(type)) {
	int ier;

	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, &ier);
	if (ier != 0) return;

	cg_iRIC_Read_BC_Count_WithGridId(*gid, c_type, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indicessize_withgridid_f, CG_IRIC_READ_BC_INDICESSIZE_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, int* size, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_IndicesSize_WithGridId(*gid, c_type, *num, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indices_withgridid_f, CG_IRIC_READ_BC_INDICES_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Indices_WithGridId(*gid, c_type, *num, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_integer_withgridid_f, CG_IRIC_READ_BC_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Integer_WithGridId(*gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_real_withgridid_f, CG_IRIC_READ_BC_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Real_WithGridId(*gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_realsingle_withgridid_f, CG_IRIC_READ_BC_REALSINGLE_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_RealSingle_WithGridId(*gid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_stringlen_withgridid_f, CG_IRIC_READ_BC_STRINGLEN_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_StringLen_WithGridId(*gid, c_type, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_string_withgridid_f, CG_IRIC_READ_BC_STRING_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_String_WithGridId(*gid, c_type, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalsize_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALSIZE_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalSize_WithGridId(*gid, c_type, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_withgridid_f, CG_IRIC_READ_BC_FUNCTIONAL_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_WithGridId(*gid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_WithGridId(*gid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_realsingle_withgridid_f, CG_IRIC_READ_BC_FUNCTIONAL_REALSINGLE_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_RealSingle_WithGridId(*gid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_realsingle_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_REALSINGLE_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_RealSingle_WithGridId(*gid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_stringlen_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRINGLEN_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen_WithGridId(*gid, c_type, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_string_withgridid_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRING_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
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

	*ier = cg_iRIC_Read_BC_FunctionalWithName_String_WithGridId(*gid, c_type, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_bc_withgridid_f, CG_IRIC_CLEAR_BC_WITHGRIDID_F) (int* gid, int *ier) {
	*ier = cg_iRIC_Clear_BC_WithGridId(*gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices_withgridid_f, CG_IRIC_WRITE_BC_INDICES_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices_WithGridId(*gid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices2_withgridid_f, CG_IRIC_WRITE_BC_INDICES2_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices2_WithGridId(*gid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_integer_withgridid_f, CG_IRIC_WRITE_BC_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Integer_WithGridId(*gid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_real_withgridid_f, CG_IRIC_WRITE_BC_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Real_WithGridId(*gid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_string_withgridid_f, CG_IRIC_WRITE_BC_STRING_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(value)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_String_WithGridId(*gid, c_type, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functional_withgridid_f, CG_IRIC_WRITE_BC_FUNCTIONAL_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Functional_WithGridId(*gid, c_type, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_withgridid_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_FunctionalWithName_WithGridId(*gid, c_type, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_string_withgridid_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_STRING_WITHGRIDID_F) (int* gid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
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

	*ier = cg_iRIC_Write_BC_FunctionalWithName_String_WithGridId(*gid, c_type, *num, c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_read_integer_f, CG_IRIC_READ_INTEGER_F) (STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Integer(c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_real_f, CG_IRIC_READ_REAL_F) (STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Real(c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_realsingle_f, CG_IRIC_READ_REALSINGLE_F) (STR_PSTR(name), float* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_RealSingle(c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_stringlen_f, CG_IRIC_READ_STRINGLEN_F) (STR_PSTR(name), int* length, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_StringLen(c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_string_f, CG_IRIC_READ_STRING_F) (STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_String(c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalsize_f, CG_IRIC_READ_FUNCTIONALSIZE_F) (STR_PSTR(name), int* size, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalSize(c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_functional_f, CG_IRIC_READ_FUNCTIONAL_F) (STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Functional(c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_f, CG_IRIC_READ_FUNCTIONALWITHNAME_F) (STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName(c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functional_realsingle_f, CG_IRIC_READ_FUNCTIONAL_REALSINGLE_F) (STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Functional_RealSingle(c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_realsingle_f, CG_IRIC_READ_FUNCTIONALWITHNAME_REALSINGLE_F) (STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_RealSingle(c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_string_f, CG_IRIC_READ_FUNCTIONALWITHNAME_STRING_F) (STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_String(c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_functionalwithname_stringlen_f, CG_IRIC_READ_FUNCTIONALWITHNAME_STRINGLEN_F) (STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_FunctionalWithName_StringLen(c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_write_integer_f, CG_IRIC_WRITE_INTEGER_F) (STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Integer(c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_real_f, CG_IRIC_WRITE_REAL_F) (STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Real(c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_string_f, CG_IRIC_WRITE_STRING_F) (STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_String(c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_functional_f, CG_IRIC_WRITE_FUNCTIONAL_F) (STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Functional(c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_functionalwithname_f, CG_IRIC_WRITE_FUNCTIONALWITHNAME_F) (STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(name) STR_PLEN(paramname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_FunctionalWithName(c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_functionalwithname_string_f, CG_IRIC_WRITE_FUNCTIONALWITHNAME_STRING_F) (STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_FunctionalWithName_String(c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_count_withbaseid_f, CG_IRIC_READ_COMPLEX_COUNT_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Count_WithBaseId(*bid, c_groupname, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_integer_withbaseid_f, CG_IRIC_READ_COMPLEX_INTEGER_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Integer_WithBaseId(*bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_real_withbaseid_f, CG_IRIC_READ_COMPLEX_REAL_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Real_WithBaseId(*bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_realsingle_withbaseid_f, CG_IRIC_READ_COMPLEX_REALSINGLE_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_RealSingle_WithBaseId(*bid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_stringlen_withbaseid_f, CG_IRIC_READ_COMPLEX_STRINGLEN_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_StringLen_WithBaseId(*bid, c_groupname, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_string_withbaseid_f, CG_IRIC_READ_COMPLEX_STRING_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_String_WithBaseId(*bid, c_groupname, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalsize_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALSIZE_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalSize_WithBaseId(*bid, c_groupname, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_WithBaseId(*bid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_WithBaseId(*bid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_realsingle_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_REALSINGLE_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_RealSingle_WithBaseId(*bid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_realsingle_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_REALSINGLE_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_WithBaseId(*bid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_stringlen_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRINGLEN_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_StringLen_WithBaseId(*bid, c_groupname, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_string_withbaseid_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRING_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
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

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_String_WithBaseId(*bid, c_groupname, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_node_withgridid_f, CG_IRIC_READ_GRID_COMPLEX_NODE_WITHGRIDID_F) (int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Node_WithGridId(*gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_cell_withgridid_f, CG_IRIC_READ_GRID_COMPLEX_CELL_WITHGRIDID_F) (int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Cell_WithGridId(*gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_clear_complex_withbaseid_f, CG_IRIC_CLEAR_COMPLEX_WITHBASEID_F) (int* bid, int *ier) {
	*ier = cg_iRIC_Clear_Complex_WithBaseId(*bid);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_integer_withbaseid_f, CG_IRIC_WRITE_COMPLEX_INTEGER_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Integer_WithBaseId(*bid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_real_withbaseid_f, CG_IRIC_WRITE_COMPLEX_REAL_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Real_WithBaseId(*bid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_string_withbaseid_f, CG_IRIC_WRITE_COMPLEX_STRING_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(value)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_String_WithBaseId(*bid, c_groupname, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functional_withbaseid_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONAL_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Functional_WithBaseId(*bid, c_groupname, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_withbaseid_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_WithBaseId(*bid, c_groupname, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_string_withbaseid_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_STRING_WITHBASEID_F) (int* bid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
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

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_String_WithBaseId(*bid, c_groupname, *num, c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_node_withgridid_f, CG_IRIC_WRITE_GRID_COMPLEX_NODE_WITHGRIDID_F) (int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Node_WithGridId(*gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_cell_withgridid_f, CG_IRIC_WRITE_GRID_COMPLEX_CELL_WITHGRIDID_F) (int* gid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Cell_WithGridId(*gid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_geo_count_f, CG_IRIC_READ_GEO_COUNT_F) (STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Geo_Count(c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_geo_filename_f, CG_IRIC_READ_GEO_FILENAME_F) (STR_PSTR(name), int* geoid, STR_PSTR(strvalue), int* type, int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Geo_Filename(c_name, *geoid, c_strvalue, type);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_str_size_withgridid_f, CG_IRIC_READ_GRID2D_STR_SIZE_WITHGRIDID_F) (int* gid, int* isize, int* jsize, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Str_Size_WithGridId(*gid, isize, jsize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_coords_withgridid_f, CG_IRIC_READ_GRID2D_COORDS_WITHGRIDID_F) (int* gid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Coords_WithGridId(*gid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_str_size_withgridid_f, CG_IRIC_READ_GRID3D_STR_SIZE_WITHGRIDID_F) (int* gid, int* isize, int* jsize, int* ksize, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Str_Size_WithGridId(*gid, isize, jsize, ksize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_coords_withgridid_f, CG_IRIC_READ_GRID3D_COORDS_WITHGRIDID_F) (int* gid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Coords_WithGridId(*gid, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_gettriangleelementssize_withgridid_f, CG_IRIC_GETTRIANGLEELEMENTSSIZE_WITHGRIDID_F) (int* gid, int* size, int *ier) {
	*ier = cg_iRIC_GetTriangleElementsSize_WithGridId(*gid, size);
}

void IRICLIBDLL FMNAME(cg_iric_gettriangleelements_withgridid_f, CG_IRIC_GETTRIANGLEELEMENTS_WITHGRIDID_F) (int* gid, int* id_arr, int *ier) {
	*ier = cg_iRIC_GetTriangleElements_WithGridId(*gid, id_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_nodecount_withgridid_f, CG_IRIC_READ_GRID_NODECOUNT_WITHGRIDID_F) (int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_NodeCount_WithGridId(*gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_cellcount_withgridid_f, CG_IRIC_READ_GRID_CELLCOUNT_WITHGRIDID_F) (int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_CellCount_WithGridId(*gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_ifacecount_withgridid_f, CG_IRIC_READ_GRID_IFACECOUNT_WITHGRIDID_F) (int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_IFaceCount_WithGridId(*gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_jfacecount_withgridid_f, CG_IRIC_READ_GRID_JFACECOUNT_WITHGRIDID_F) (int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_JFaceCount_WithGridId(*gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_kfacecount_withgridid_f, CG_IRIC_READ_GRID_KFACECOUNT_WITHGRIDID_F) (int* gid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_KFaceCount_WithGridId(*gid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_node_withgridid_f, CG_IRIC_READ_GRID_REAL_NODE_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Node_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_node_withgridid_f, CG_IRIC_READ_GRID_INTEGER_NODE_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Node_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_cell_withgridid_f, CG_IRIC_READ_GRID_REAL_CELL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Cell_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_cell_withgridid_f, CG_IRIC_READ_GRID_INTEGER_CELL_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Cell_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimensionsize_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSIONSIZE_WITHGRIDID_F) (int* gid, STR_PSTR(name), STR_PSTR(dimname), int* count, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimensionSize_WithGridId(*gid, c_name, c_dimname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_integer_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), STR_PSTR(dimname), int* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Integer_WithGridId(*gid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_real_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), STR_PSTR(dimname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Real_WithGridId(*gid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltimesize_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALTIMESIZE_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTimeSize_WithGridId(*gid, c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltime_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONALTIME_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* time_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTime_WithGridId(*gid, c_name, time_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_node_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_NODE_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Node_WithGridId(*gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_node_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_NODE_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Node_WithGridId(*gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_cell_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_CELL_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Cell_WithGridId(*gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_cell_withgridid_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_CELL_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Cell_WithGridId(*gid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid1d_coords_withgridid_f, CG_IRIC_WRITE_GRID1D_COORDS_WITHGRIDID_F) (int* isize, double* x_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid1d_Coords_WithGridId(*isize, x_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid2d_coords_withgridid_f, CG_IRIC_WRITE_GRID2D_COORDS_WITHGRIDID_F) (int* isize, int* jsize, double* x_arr, double* y_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid2d_Coords_WithGridId(*isize, *jsize, x_arr, y_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid3d_coords_withgridid_f, CG_IRIC_WRITE_GRID3D_COORDS_WITHGRIDID_F) (int* isize, int* jsize, int* ksize, double* x_arr, double* y_arr, double* z_arr, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Grid3d_Coords_WithGridId(*isize, *jsize, *ksize, x_arr, y_arr, z_arr, gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_node_withgridid_f, CG_IRIC_WRITE_GRID_REAL_NODE_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Node_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_node_withgridid_f, CG_IRIC_WRITE_GRID_INTEGER_NODE_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Node_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_cell_withgridid_f, CG_IRIC_WRITE_GRID_REAL_CELL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Cell_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_cell_withgridid_f, CG_IRIC_WRITE_GRID_INTEGER_CELL_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Cell_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_count_f, CG_IRIC_READ_COMPLEX_COUNT_F) (STR_PSTR(groupname), int* num, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Count(c_groupname, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_integer_f, CG_IRIC_READ_COMPLEX_INTEGER_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Integer(c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_real_f, CG_IRIC_READ_COMPLEX_REAL_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Real(c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_realsingle_f, CG_IRIC_READ_COMPLEX_REALSINGLE_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_RealSingle(c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_stringlen_f, CG_IRIC_READ_COMPLEX_STRINGLEN_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_StringLen(c_groupname, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_string_f, CG_IRIC_READ_COMPLEX_STRING_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_String(c_groupname, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalsize_f, CG_IRIC_READ_COMPLEX_FUNCTIONALSIZE_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalSize(c_groupname, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional(c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName(c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_realsingle_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_REALSINGLE_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_RealSingle(c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_realsingle_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_REALSINGLE_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_RealSingle(c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_stringlen_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRINGLEN_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_StringLen(c_groupname, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_string_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRING_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
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

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_String(c_groupname, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_complex_f, CG_IRIC_CLEAR_COMPLEX_F) (int *ier) {
	*ier = cg_iRIC_Clear_Complex();
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_integer_f, CG_IRIC_WRITE_COMPLEX_INTEGER_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Integer(c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_real_f, CG_IRIC_WRITE_COMPLEX_REAL_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Real(c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_string_f, CG_IRIC_WRITE_COMPLEX_STRING_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(value)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_String(c_groupname, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functional_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONAL_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Functional(c_groupname, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_FunctionalWithName(c_groupname, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_string_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_STRING_F) (STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
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

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_String(c_groupname, *num, c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_count_f, CG_IRIC_READ_BC_COUNT_F) (STR_PSTR(type), int* num STR_PLEN(type)) {
	int ier;

	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, &ier);
	if (ier != 0) return;

	cg_iRIC_Read_BC_Count(c_type, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indicessize_f, CG_IRIC_READ_BC_INDICESSIZE_F) (STR_PSTR(type), int* num, int* size, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_IndicesSize(c_type, *num, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indices_f, CG_IRIC_READ_BC_INDICES_F) (STR_PSTR(type), int* num, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Indices(c_type, *num, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_integer_f, CG_IRIC_READ_BC_INTEGER_F) (STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Integer(c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_real_f, CG_IRIC_READ_BC_REAL_F) (STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Real(c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_realsingle_f, CG_IRIC_READ_BC_REALSINGLE_F) (STR_PSTR(type), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_RealSingle(c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_stringlen_f, CG_IRIC_READ_BC_STRINGLEN_F) (STR_PSTR(type), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_StringLen(c_type, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_string_f, CG_IRIC_READ_BC_STRING_F) (STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_String(c_type, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalsize_f, CG_IRIC_READ_BC_FUNCTIONALSIZE_F) (STR_PSTR(type), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalSize(c_type, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_f, CG_IRIC_READ_BC_FUNCTIONAL_F) (STR_PSTR(type), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional(c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_F) (STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName(c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_realsingle_f, CG_IRIC_READ_BC_FUNCTIONAL_REALSINGLE_F) (STR_PSTR(type), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_RealSingle(c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_realsingle_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_REALSINGLE_F) (STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_RealSingle(c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_stringlen_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRINGLEN_F) (STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen(c_type, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_string_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRING_F) (STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
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

	*ier = cg_iRIC_Read_BC_FunctionalWithName_String(c_type, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_bc_f, CG_IRIC_CLEAR_BC_F) (int *ier) {
	*ier = cg_iRIC_Clear_BC();
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices_f, CG_IRIC_WRITE_BC_INDICES_F) (STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices(c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices2_f, CG_IRIC_WRITE_BC_INDICES2_F) (STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices2(c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_integer_f, CG_IRIC_WRITE_BC_INTEGER_F) (STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Integer(c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_real_f, CG_IRIC_WRITE_BC_REAL_F) (STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Real(c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_string_f, CG_IRIC_WRITE_BC_STRING_F) (STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(value)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_String(c_type, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functional_f, CG_IRIC_WRITE_BC_FUNCTIONAL_F) (STR_PSTR(type), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Functional(c_type, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_F) (STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_FunctionalWithName(c_type, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_string_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_STRING_F) (STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
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

	*ier = cg_iRIC_Write_BC_FunctionalWithName_String(c_type, *num, c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_node_f, CG_IRIC_READ_GRID_COMPLEX_NODE_F) (STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Node(c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_cell_f, CG_IRIC_READ_GRID_COMPLEX_CELL_F) (STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Cell(c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_node_f, CG_IRIC_WRITE_GRID_COMPLEX_NODE_F) (STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Node(c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_cell_f, CG_IRIC_WRITE_GRID_COMPLEX_CELL_F) (STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Cell(c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_str_size_f, CG_IRIC_READ_GRID2D_STR_SIZE_F) (int* isize, int* jsize, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Str_Size(isize, jsize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_coords_f, CG_IRIC_READ_GRID2D_COORDS_F) (double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Coords(x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_str_size_f, CG_IRIC_READ_GRID3D_STR_SIZE_F) (int* isize, int* jsize, int* ksize, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Str_Size(isize, jsize, ksize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_coords_f, CG_IRIC_READ_GRID3D_COORDS_F) (double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Coords(x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_gettriangleelementssize_f, CG_IRIC_GETTRIANGLEELEMENTSSIZE_F) (int* size, int *ier) {
	*ier = cg_iRIC_GetTriangleElementsSize(size);
}

void IRICLIBDLL FMNAME(cg_iric_gettriangleelements_f, CG_IRIC_GETTRIANGLEELEMENTS_F) (int* id_arr, int *ier) {
	*ier = cg_iRIC_GetTriangleElements(id_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_nodecount_f, CG_IRIC_READ_GRID_NODECOUNT_F) (int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_NodeCount(count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_cellcount_f, CG_IRIC_READ_GRID_CELLCOUNT_F) (int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_CellCount(count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_ifacecount_f, CG_IRIC_READ_GRID_IFACECOUNT_F) (int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_IFaceCount(count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_jfacecount_f, CG_IRIC_READ_GRID_JFACECOUNT_F) (int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_JFaceCount(count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_kfacecount_f, CG_IRIC_READ_GRID_KFACECOUNT_F) (int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_KFaceCount(count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_node_f, CG_IRIC_READ_GRID_REAL_NODE_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Node(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_node_f, CG_IRIC_READ_GRID_INTEGER_NODE_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Node(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_cell_f, CG_IRIC_READ_GRID_REAL_CELL_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Cell(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_cell_f, CG_IRIC_READ_GRID_INTEGER_CELL_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Cell(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimensionsize_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSIONSIZE_F) (STR_PSTR(name), STR_PSTR(dimname), int* count, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimensionSize(c_name, c_dimname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_integer_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_INTEGER_F) (STR_PSTR(name), STR_PSTR(dimname), int* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Integer(c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_real_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_REAL_F) (STR_PSTR(name), STR_PSTR(dimname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Real(c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltimesize_f, CG_IRIC_READ_GRID_FUNCTIONALTIMESIZE_F) (STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTimeSize(c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltime_f, CG_IRIC_READ_GRID_FUNCTIONALTIME_F) (STR_PSTR(name), double* time_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTime(c_name, time_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_node_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_NODE_F) (STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Node(c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_node_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_NODE_F) (STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Node(c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_cell_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_CELL_F) (STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Cell(c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_cell_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_CELL_F) (STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Cell(c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid1d_coords_f, CG_IRIC_WRITE_GRID1D_COORDS_F) (int* isize, double* x_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid1d_Coords(*isize, x_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid2d_coords_f, CG_IRIC_WRITE_GRID2D_COORDS_F) (int* isize, int* jsize, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid2d_Coords(*isize, *jsize, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid3d_coords_f, CG_IRIC_WRITE_GRID3D_COORDS_F) (int* isize, int* jsize, int* ksize, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid3d_Coords(*isize, *jsize, *ksize, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_node_f, CG_IRIC_WRITE_GRID_REAL_NODE_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Node(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_node_f, CG_IRIC_WRITE_GRID_INTEGER_NODE_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Node(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_cell_f, CG_IRIC_WRITE_GRID_REAL_CELL_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Cell(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_cell_f, CG_IRIC_WRITE_GRID_INTEGER_CELL_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Cell(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_integer_f, CG_IRIC_READ_SOL_CELL_INTEGER_F) (int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Integer(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_real_f, CG_IRIC_READ_SOL_CELL_REAL_F) (int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Real(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_integer_f, CG_IRIC_WRITE_SOL_CELL_INTEGER_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Integer(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_real_f, CG_IRIC_WRITE_SOL_CELL_REAL_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Real(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid2d_coords_f, CG_IRIC_READ_SOL_GRID2D_COORDS_F) (int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid2d_Coords(*step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid3d_coords_f, CG_IRIC_READ_SOL_GRID3D_COORDS_F) (int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid3d_Coords(*step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid2d_coords_f, CG_IRIC_WRITE_SOL_GRID2D_COORDS_F) (double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid2d_Coords(x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid3d_coords_f, CG_IRIC_WRITE_SOL_GRID3D_COORDS_F) (double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid3d_Coords(x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_integer_f, CG_IRIC_READ_SOL_IFACE_INTEGER_F) (int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Integer(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_real_f, CG_IRIC_READ_SOL_IFACE_REAL_F) (int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Real(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_integer_f, CG_IRIC_WRITE_SOL_IFACE_INTEGER_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Integer(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_real_f, CG_IRIC_WRITE_SOL_IFACE_REAL_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Real(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_integer_f, CG_IRIC_READ_SOL_JFACE_INTEGER_F) (int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Integer(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_real_f, CG_IRIC_READ_SOL_JFACE_REAL_F) (int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Real(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_integer_f, CG_IRIC_WRITE_SOL_JFACE_INTEGER_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Integer(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_real_f, CG_IRIC_WRITE_SOL_JFACE_REAL_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Real(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_integer_f, CG_IRIC_READ_SOL_KFACE_INTEGER_F) (int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Integer(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_real_f, CG_IRIC_READ_SOL_KFACE_REAL_F) (int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Real(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_integer_f, CG_IRIC_WRITE_SOL_KFACE_INTEGER_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Integer(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_real_f, CG_IRIC_WRITE_SOL_KFACE_REAL_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Real(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_integer_f, CG_IRIC_READ_SOL_NODE_INTEGER_F) (int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Integer(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_real_f, CG_IRIC_READ_SOL_NODE_REAL_F) (int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Real(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_integer_f, CG_IRIC_WRITE_SOL_NODE_INTEGER_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Integer(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_real_f, CG_IRIC_WRITE_SOL_NODE_REAL_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Real(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_count_f, CG_IRIC_READ_SOL_PARTICLE_COUNT_F) (int* step, int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Count(*step, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos2d_f, CG_IRIC_READ_SOL_PARTICLE_POS2D_F) (int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos2d(*step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos3d_f, CG_IRIC_READ_SOL_PARTICLE_POS3D_F) (int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos3d(*step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_real_f, CG_IRIC_READ_SOL_PARTICLE_REAL_F) (int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Real(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_integer_f, CG_IRIC_READ_SOL_PARTICLE_INTEGER_F) (int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Integer(*step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos2d_f, CG_IRIC_WRITE_SOL_PARTICLE_POS2D_F) (int* count, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos2d(*count, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos3d_f, CG_IRIC_WRITE_SOL_PARTICLE_POS3D_F) (int* count, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos3d(*count, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_real_f, CG_IRIC_WRITE_SOL_PARTICLE_REAL_F) (STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Real(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_integer_f, CG_IRIC_WRITE_SOL_PARTICLE_INTEGER_F) (STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Integer(c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_count_f, CG_IRIC_READ_SOL_PARTICLEGROUP_COUNT_F) (int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Count(*step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos2d_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS2D_F) (int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos2d(*step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos3d_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS3D_F) (int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, double* z_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos3d(*step, c_groupname, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_real_f, CG_IRIC_READ_SOL_PARTICLEGROUP_REAL_F) (int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Real(*step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_integer_f, CG_IRIC_READ_SOL_PARTICLEGROUP_INTEGER_F) (int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Integer(*step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupbegin_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPBEGIN_F) (STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin(c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupend_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPEND_F) (int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd();
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos2d_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS2D_F) (double* x, double* y, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos2d(*x, *y);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos3d_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS3D_F) (double* x, double* y, double* z, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos3d(*x, *y, *z);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_integer_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_INTEGER_F) (STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Integer(c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_real_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_REAL_F) (STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Real(c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_datacount_f, CG_IRIC_READ_SOL_POLYDATA_DATACOUNT_F) (int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_DataCount(*step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_coordinatecount_f, CG_IRIC_READ_SOL_POLYDATA_COORDINATECOUNT_F) (int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_CoordinateCount(*step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_pos2d_f, CG_IRIC_READ_SOL_POLYDATA_POS2D_F) (int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Pos2d(*step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_type_f, CG_IRIC_READ_SOL_POLYDATA_TYPE_F) (int* step, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Type(*step, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_real_f, CG_IRIC_READ_SOL_POLYDATA_REAL_F) (int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Real(*step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_integer_f, CG_IRIC_READ_SOL_POLYDATA_INTEGER_F) (int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Integer(*step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupbegin_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPBEGIN_F) (STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_GroupBegin(c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupend_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPEND_F) (int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_GroupEnd();
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polygon_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYGON_F) (int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polygon(*numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polyline_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYLINE_F) (int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polyline(*numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_integer_f, CG_IRIC_WRITE_SOL_POLYDATA_INTEGER_F) (STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Integer(c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_real_f, CG_IRIC_WRITE_SOL_POLYDATA_REAL_F) (STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Real(c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_integer_withgridid_f, CG_IRIC_READ_SOL_CELL_INTEGER_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Integer_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_real_withgridid_f, CG_IRIC_READ_SOL_CELL_REAL_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Real_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_integer_withgridid_f, CG_IRIC_WRITE_SOL_CELL_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Integer_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_real_withgridid_f, CG_IRIC_WRITE_SOL_CELL_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Real_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid2d_coords_withgridid_f, CG_IRIC_READ_SOL_GRID2D_COORDS_WITHGRIDID_F) (int* gid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid2d_Coords_WithGridId(*gid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid3d_coords_withgridid_f, CG_IRIC_READ_SOL_GRID3D_COORDS_WITHGRIDID_F) (int* gid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid3d_Coords_WithGridId(*gid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid2d_coords_withgridid_f, CG_IRIC_WRITE_SOL_GRID2D_COORDS_WITHGRIDID_F) (int* gid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid2d_Coords_WithGridId(*gid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid3d_coords_withgridid_f, CG_IRIC_WRITE_SOL_GRID3D_COORDS_WITHGRIDID_F) (int* gid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid3d_Coords_WithGridId(*gid, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_integer_withgridid_f, CG_IRIC_READ_SOL_IFACE_INTEGER_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Integer_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_real_withgridid_f, CG_IRIC_READ_SOL_IFACE_REAL_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Real_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_integer_withgridid_f, CG_IRIC_WRITE_SOL_IFACE_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Integer_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_real_withgridid_f, CG_IRIC_WRITE_SOL_IFACE_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Real_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_integer_withgridid_f, CG_IRIC_READ_SOL_JFACE_INTEGER_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Integer_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_real_withgridid_f, CG_IRIC_READ_SOL_JFACE_REAL_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Real_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_integer_withgridid_f, CG_IRIC_WRITE_SOL_JFACE_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Integer_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_real_withgridid_f, CG_IRIC_WRITE_SOL_JFACE_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Real_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_integer_withgridid_f, CG_IRIC_READ_SOL_KFACE_INTEGER_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Integer_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_real_withgridid_f, CG_IRIC_READ_SOL_KFACE_REAL_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Real_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_integer_withgridid_f, CG_IRIC_WRITE_SOL_KFACE_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Integer_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_real_withgridid_f, CG_IRIC_WRITE_SOL_KFACE_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Real_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_integer_withgridid_f, CG_IRIC_READ_SOL_NODE_INTEGER_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Integer_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_real_withgridid_f, CG_IRIC_READ_SOL_NODE_REAL_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Real_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_integer_withgridid_f, CG_IRIC_WRITE_SOL_NODE_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Integer_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_real_withgridid_f, CG_IRIC_WRITE_SOL_NODE_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Real_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_count_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_COUNT_WITHGRIDID_F) (int* gid, int* step, int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Count_WithGridId(*gid, *step, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos2d_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_POS2D_WITHGRIDID_F) (int* gid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId(*gid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos3d_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_POS3D_WITHGRIDID_F) (int* gid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId(*gid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_real_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_REAL_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Real_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_integer_withgridid_f, CG_IRIC_READ_SOL_PARTICLE_INTEGER_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Integer_WithGridId(*gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos2d_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLE_POS2D_WITHGRIDID_F) (int* gid, int* count, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId(*gid, *count, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos3d_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLE_POS3D_WITHGRIDID_F) (int* gid, int* count, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId(*gid, *count, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_real_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLE_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Real_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_integer_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLE_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Integer_WithGridId(*gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_count_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_COUNT_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Count_WithGridId(*gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos2d_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS2D_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId(*gid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos3d_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS3D_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, double* z_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId(*gid, *step, c_groupname, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_real_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_REAL_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId(*gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_integer_withgridid_f, CG_IRIC_READ_SOL_PARTICLEGROUP_INTEGER_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId(*gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupbegin_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPBEGIN_WITHGRIDID_F) (int* gid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_WithGridId(*gid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupend_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPEND_WITHGRIDID_F) (int* gid, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_WithGridId(*gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos2d_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS2D_WITHGRIDID_F) (int* gid, double* x, double* y, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos2d_WithGridId(*gid, *x, *y);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos3d_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS3D_WITHGRIDID_F) (int* gid, double* x, double* y, double* z, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos3d_WithGridId(*gid, *x, *y, *z);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_integer_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Integer_WithGridId(*gid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_real_withgridid_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Real_WithGridId(*gid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_datacount_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_DATACOUNT_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_DataCount_WithGridId(*gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_coordinatecount_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_COORDINATECOUNT_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_CoordinateCount_WithGridId(*gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_pos2d_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_POS2D_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId(*gid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_type_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_TYPE_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Type_WithGridId(*gid, *step, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_real_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_REAL_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Real_WithGridId(*gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_integer_withgridid_f, CG_IRIC_READ_SOL_POLYDATA_INTEGER_WITHGRIDID_F) (int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Integer_WithGridId(*gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupbegin_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPBEGIN_WITHGRIDID_F) (int* gid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_GroupBegin_WithGridId(*gid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupend_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPEND_WITHGRIDID_F) (int* gid, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_GroupEnd_WithGridId(*gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polygon_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYGON_WITHGRIDID_F) (int* gid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId(*gid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polyline_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYLINE_WITHGRIDID_F) (int* gid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId(*gid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_integer_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_INTEGER_WITHGRIDID_F) (int* gid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Integer_WithGridId(*gid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_real_withgridid_f, CG_IRIC_WRITE_SOL_POLYDATA_REAL_WITHGRIDID_F) (int* gid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Real_WithGridId(*gid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_count_f, CG_IRIC_READ_SOL_COUNT_F) (int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Count(count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_time_f, CG_IRIC_READ_SOL_TIME_F) (int* step, double* time, int *ier) {
	*ier = cg_iRIC_Read_Sol_Time(*step, time);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iteration_f, CG_IRIC_READ_SOL_ITERATION_F) (int* step, int* index, int *ier) {
	*ier = cg_iRIC_Read_Sol_Iteration(*step, index);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_integer_f, CG_IRIC_READ_SOL_BASEITERATIVE_INTEGER_F) (int* step, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_Integer(*step, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_real_f, CG_IRIC_READ_SOL_BASEITERATIVE_REAL_F) (int* step, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_Real(*step, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_stringlen_f, CG_IRIC_READ_SOL_BASEITERATIVE_STRINGLEN_F) (int* step, STR_PSTR(name), int* length, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_StringLen(*step, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_string_f, CG_IRIC_READ_SOL_BASEITERATIVE_STRING_F) (int* step, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_String(*step, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_time_f, CG_IRIC_WRITE_SOL_TIME_F) (double* time, int *ier) {
	*ier = cg_iRIC_Write_Sol_Time(*time);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iteration_f, CG_IRIC_WRITE_SOL_ITERATION_F) (int* index, int *ier) {
	*ier = cg_iRIC_Write_Sol_Iteration(*index);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_integer_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_INTEGER_F) (STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_Integer(c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_real_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_REAL_F) (STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_Real(c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_string_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_STRING_F) (STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_String(c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_errorcode_f, CG_IRIC_WRITE_ERRORCODE_F) (int* errorcode, int *ier) {
	*ier = cg_iRIC_Write_ErrorCode(*errorcode);
}


// from iriclib_not_withbaseid.h
void IRICLIBDLL FMNAME(cg_iric_read_complex_count_mul_f, CG_IRIC_READ_COMPLEX_COUNT_MUL_F) (int* fid, STR_PSTR(groupname), int* num, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Count_Mul(*fid, c_groupname, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_integer_mul_f, CG_IRIC_READ_COMPLEX_INTEGER_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Integer_Mul(*fid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_real_mul_f, CG_IRIC_READ_COMPLEX_REAL_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Real_Mul(*fid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_realsingle_mul_f, CG_IRIC_READ_COMPLEX_REALSINGLE_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_RealSingle_Mul(*fid, c_groupname, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_stringlen_mul_f, CG_IRIC_READ_COMPLEX_STRINGLEN_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_StringLen_Mul(*fid, c_groupname, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_string_mul_f, CG_IRIC_READ_COMPLEX_STRING_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_String_Mul(*fid, c_groupname, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalsize_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALSIZE_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalSize_Mul(*fid, c_groupname, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_Mul(*fid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_Mul(*fid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functional_realsingle_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONAL_REALSINGLE_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_Functional_RealSingle_Mul(*fid, c_groupname, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_realsingle_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_REALSINGLE_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_RealSingle_Mul(*fid, c_groupname, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_stringlen_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRINGLEN_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_StringLen_Mul(*fid, c_groupname, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_complex_functionalwithname_string_mul_f, CG_IRIC_READ_COMPLEX_FUNCTIONALWITHNAME_STRING_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
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

	*ier = cg_iRIC_Read_Complex_FunctionalWithName_String_Mul(*fid, c_groupname, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_complex_mul_f, CG_IRIC_CLEAR_COMPLEX_MUL_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Clear_Complex_Mul(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_integer_mul_f, CG_IRIC_WRITE_COMPLEX_INTEGER_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Integer_Mul(*fid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_real_mul_f, CG_IRIC_WRITE_COMPLEX_REAL_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Real_Mul(*fid, c_groupname, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_string_mul_f, CG_IRIC_WRITE_COMPLEX_STRING_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(value)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_String_Mul(*fid, c_groupname, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functional_mul_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONAL_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_Functional_Mul(*fid, c_groupname, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_mul_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_Mul(*fid, c_groupname, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_complex_functionalwithname_string_mul_f, CG_IRIC_WRITE_COMPLEX_FUNCTIONALWITHNAME_STRING_MUL_F) (int* fid, STR_PSTR(groupname), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(groupname) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
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

	*ier = cg_iRIC_Write_Complex_FunctionalWithName_String_Mul(*fid, c_groupname, *num, c_name, c_paramname, c_value);
}


// from iriclib_not_withgridid.h
void IRICLIBDLL FMNAME(cg_iric_read_bc_count_mul_f, CG_IRIC_READ_BC_COUNT_MUL_F) (int* fid, STR_PSTR(type), int* num STR_PLEN(type)) {
	int ier;

	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, &ier);
	if (ier != 0) return;

	cg_iRIC_Read_BC_Count_Mul(*fid, c_type, num);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indicessize_mul_f, CG_IRIC_READ_BC_INDICESSIZE_MUL_F) (int* fid, STR_PSTR(type), int* num, int* size, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_IndicesSize_Mul(*fid, c_type, *num, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_indices_mul_f, CG_IRIC_READ_BC_INDICES_MUL_F) (int* fid, STR_PSTR(type), int* num, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Indices_Mul(*fid, c_type, *num, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_integer_mul_f, CG_IRIC_READ_BC_INTEGER_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Integer_Mul(*fid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_real_mul_f, CG_IRIC_READ_BC_REAL_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Real_Mul(*fid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_realsingle_mul_f, CG_IRIC_READ_BC_REALSINGLE_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), float* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_RealSingle_Mul(*fid, c_type, *num, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_stringlen_mul_f, CG_IRIC_READ_BC_STRINGLEN_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_StringLen_Mul(*fid, c_type, *num, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_string_mul_f, CG_IRIC_READ_BC_STRING_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_String_Mul(*fid, c_type, *num, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalsize_mul_f, CG_IRIC_READ_BC_FUNCTIONALSIZE_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* size, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalSize_Mul(*fid, c_type, *num, c_name, size);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_mul_f, CG_IRIC_READ_BC_FUNCTIONAL_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_Mul(*fid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_mul_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_Mul(*fid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functional_realsingle_mul_f, CG_IRIC_READ_BC_FUNCTIONAL_REALSINGLE_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), float* x_arr, float* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_Functional_RealSingle_Mul(*fid, c_type, *num, c_name, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_realsingle_mul_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_REALSINGLE_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), float* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_RealSingle_Mul(*fid, c_type, *num, c_name, c_paramname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_stringlen_mul_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRINGLEN_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen_Mul(*fid, c_type, *num, c_name, c_paramname, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_bc_functionalwithname_string_mul_f, CG_IRIC_READ_BC_FUNCTIONALWITHNAME_STRING_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(strvalue), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(strvalue)) {
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

	*ier = cg_iRIC_Read_BC_FunctionalWithName_String_Mul(*fid, c_type, *num, c_name, c_paramname, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_clear_bc_mul_f, CG_IRIC_CLEAR_BC_MUL_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Clear_BC_Mul(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices_mul_f, CG_IRIC_WRITE_BC_INDICES_MUL_F) (int* fid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices_Mul(*fid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_indices2_mul_f, CG_IRIC_WRITE_BC_INDICES2_MUL_F) (int* fid, STR_PSTR(type), int* num, int* length, int* idx_arr, int *ier STR_PLEN(type)) {
	char c_type[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Indices2_Mul(*fid, c_type, *num, *length, idx_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_integer_mul_f, CG_IRIC_WRITE_BC_INTEGER_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Integer_Mul(*fid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_real_mul_f, CG_IRIC_WRITE_BC_REAL_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), double* value, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Real_Mul(*fid, c_type, *num, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_string_mul_f, CG_IRIC_WRITE_BC_STRING_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(value)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_String_Mul(*fid, c_type, *num, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functional_mul_f, CG_IRIC_WRITE_BC_FUNCTIONAL_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), int* length, double* x_arr, double* y_arr, int *ier STR_PLEN(type) STR_PLEN(name)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_Functional_Mul(*fid, c_type, *num, c_name, *length, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_mul_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), int* length, double* v_arr, int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname)) {
	char c_type[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	char c_paramname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(type), STR_LEN(type), c_type, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(paramname), STR_LEN(paramname), c_paramname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_BC_FunctionalWithName_Mul(*fid, c_type, *num, c_name, c_paramname, *length, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_bc_functionalwithname_string_mul_f, CG_IRIC_WRITE_BC_FUNCTIONALWITHNAME_STRING_MUL_F) (int* fid, STR_PSTR(type), int* num, STR_PSTR(name), STR_PSTR(paramname), STR_PSTR(value), int *ier STR_PLEN(type) STR_PLEN(name) STR_PLEN(paramname) STR_PLEN(value)) {
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

	*ier = cg_iRIC_Write_BC_FunctionalWithName_String_Mul(*fid, c_type, *num, c_name, c_paramname, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_node_mul_f, CG_IRIC_READ_GRID_COMPLEX_NODE_MUL_F) (int* fid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Node_Mul(*fid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_complex_cell_mul_f, CG_IRIC_READ_GRID_COMPLEX_CELL_MUL_F) (int* fid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Complex_Cell_Mul(*fid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_node_mul_f, CG_IRIC_WRITE_GRID_COMPLEX_NODE_MUL_F) (int* fid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Node_Mul(*fid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_complex_cell_mul_f, CG_IRIC_WRITE_GRID_COMPLEX_CELL_MUL_F) (int* fid, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Complex_Cell_Mul(*fid, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_str_size_mul_f, CG_IRIC_READ_GRID2D_STR_SIZE_MUL_F) (int* fid, int* isize, int* jsize, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Str_Size_Mul(*fid, isize, jsize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid2d_coords_mul_f, CG_IRIC_READ_GRID2D_COORDS_MUL_F) (int* fid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid2d_Coords_Mul(*fid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_str_size_mul_f, CG_IRIC_READ_GRID3D_STR_SIZE_MUL_F) (int* fid, int* isize, int* jsize, int* ksize, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Str_Size_Mul(*fid, isize, jsize, ksize);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid3d_coords_mul_f, CG_IRIC_READ_GRID3D_COORDS_MUL_F) (int* fid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Grid3d_Coords_Mul(*fid, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_gettriangleelementssize_mul_f, CG_IRIC_GETTRIANGLEELEMENTSSIZE_MUL_F) (int* fid, int* size, int *ier) {
	*ier = cg_iRIC_GetTriangleElementsSize_Mul(*fid, size);
}

void IRICLIBDLL FMNAME(cg_iric_gettriangleelements_mul_f, CG_IRIC_GETTRIANGLEELEMENTS_MUL_F) (int* fid, int* id_arr, int *ier) {
	*ier = cg_iRIC_GetTriangleElements_Mul(*fid, id_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_nodecount_mul_f, CG_IRIC_READ_GRID_NODECOUNT_MUL_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_NodeCount_Mul(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_cellcount_mul_f, CG_IRIC_READ_GRID_CELLCOUNT_MUL_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_CellCount_Mul(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_ifacecount_mul_f, CG_IRIC_READ_GRID_IFACECOUNT_MUL_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_IFaceCount_Mul(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_jfacecount_mul_f, CG_IRIC_READ_GRID_JFACECOUNT_MUL_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_JFaceCount_Mul(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_kfacecount_mul_f, CG_IRIC_READ_GRID_KFACECOUNT_MUL_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Grid_KFaceCount_Mul(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_node_mul_f, CG_IRIC_READ_GRID_REAL_NODE_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Node_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_node_mul_f, CG_IRIC_READ_GRID_INTEGER_NODE_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Node_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_real_cell_mul_f, CG_IRIC_READ_GRID_REAL_CELL_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Real_Cell_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_integer_cell_mul_f, CG_IRIC_READ_GRID_INTEGER_CELL_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Integer_Cell_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimensionsize_mul_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSIONSIZE_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(dimname), int* count, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimensionSize_Mul(*fid, c_name, c_dimname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_integer_mul_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_INTEGER_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(dimname), int* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Integer_Mul(*fid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaldimension_real_mul_f, CG_IRIC_READ_GRID_FUNCTIONALDIMENSION_REAL_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(dimname), double* v_arr, int *ier STR_PLEN(name) STR_PLEN(dimname)) {
	char c_name[STRINGMAXLEN + 1];
	char c_dimname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(dimname), STR_LEN(dimname), c_dimname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalDimension_Real_Mul(*fid, c_name, c_dimname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltimesize_mul_f, CG_IRIC_READ_GRID_FUNCTIONALTIMESIZE_MUL_F) (int* fid, STR_PSTR(name), int* count, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTimeSize_Mul(*fid, c_name, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functionaltime_mul_f, CG_IRIC_READ_GRID_FUNCTIONALTIME_MUL_F) (int* fid, STR_PSTR(name), double* time_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_FunctionalTime_Mul(*fid, c_name, time_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_node_mul_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_NODE_MUL_F) (int* fid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Node_Mul(*fid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_node_mul_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_NODE_MUL_F) (int* fid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Node_Mul(*fid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_integer_cell_mul_f, CG_IRIC_READ_GRID_FUNCTIONAL_INTEGER_CELL_MUL_F) (int* fid, STR_PSTR(name), int* dimid, int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Integer_Cell_Mul(*fid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_grid_functional_real_cell_mul_f, CG_IRIC_READ_GRID_FUNCTIONAL_REAL_CELL_MUL_F) (int* fid, STR_PSTR(name), int* dimid, double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Grid_Functional_Real_Cell_Mul(*fid, c_name, *dimid, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid1d_coords_mul_f, CG_IRIC_WRITE_GRID1D_COORDS_MUL_F) (int* fid, int* isize, double* x_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid1d_Coords_Mul(*fid, *isize, x_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid2d_coords_mul_f, CG_IRIC_WRITE_GRID2D_COORDS_MUL_F) (int* fid, int* isize, int* jsize, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid2d_Coords_Mul(*fid, *isize, *jsize, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid3d_coords_mul_f, CG_IRIC_WRITE_GRID3D_COORDS_MUL_F) (int* fid, int* isize, int* jsize, int* ksize, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Grid3d_Coords_Mul(*fid, *isize, *jsize, *ksize, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_node_mul_f, CG_IRIC_WRITE_GRID_REAL_NODE_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Node_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_node_mul_f, CG_IRIC_WRITE_GRID_INTEGER_NODE_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Node_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_real_cell_mul_f, CG_IRIC_WRITE_GRID_REAL_CELL_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Real_Cell_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_grid_integer_cell_mul_f, CG_IRIC_WRITE_GRID_INTEGER_CELL_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Grid_Integer_Cell_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_integer_mul_f, CG_IRIC_READ_SOL_CELL_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Integer_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_real_mul_f, CG_IRIC_READ_SOL_CELL_REAL_MUL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Real_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_integer_mul_f, CG_IRIC_WRITE_SOL_CELL_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Integer_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_real_mul_f, CG_IRIC_WRITE_SOL_CELL_REAL_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Real_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid2d_coords_mul_f, CG_IRIC_READ_SOL_GRID2D_COORDS_MUL_F) (int* fid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid2d_Coords_Mul(*fid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid3d_coords_mul_f, CG_IRIC_READ_SOL_GRID3D_COORDS_MUL_F) (int* fid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid3d_Coords_Mul(*fid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid2d_coords_mul_f, CG_IRIC_WRITE_SOL_GRID2D_COORDS_MUL_F) (int* fid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid2d_Coords_Mul(*fid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid3d_coords_mul_f, CG_IRIC_WRITE_SOL_GRID3D_COORDS_MUL_F) (int* fid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid3d_Coords_Mul(*fid, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_integer_mul_f, CG_IRIC_READ_SOL_IFACE_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Integer_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_real_mul_f, CG_IRIC_READ_SOL_IFACE_REAL_MUL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Real_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_integer_mul_f, CG_IRIC_WRITE_SOL_IFACE_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Integer_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_real_mul_f, CG_IRIC_WRITE_SOL_IFACE_REAL_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Real_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_integer_mul_f, CG_IRIC_READ_SOL_JFACE_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Integer_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_real_mul_f, CG_IRIC_READ_SOL_JFACE_REAL_MUL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Real_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_integer_mul_f, CG_IRIC_WRITE_SOL_JFACE_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Integer_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_real_mul_f, CG_IRIC_WRITE_SOL_JFACE_REAL_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Real_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_integer_mul_f, CG_IRIC_READ_SOL_KFACE_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Integer_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_real_mul_f, CG_IRIC_READ_SOL_KFACE_REAL_MUL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Real_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_integer_mul_f, CG_IRIC_WRITE_SOL_KFACE_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Integer_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_real_mul_f, CG_IRIC_WRITE_SOL_KFACE_REAL_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Real_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_integer_mul_f, CG_IRIC_READ_SOL_NODE_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Integer_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_real_mul_f, CG_IRIC_READ_SOL_NODE_REAL_MUL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Real_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_integer_mul_f, CG_IRIC_WRITE_SOL_NODE_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Integer_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_real_mul_f, CG_IRIC_WRITE_SOL_NODE_REAL_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Real_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_count_mul_f, CG_IRIC_READ_SOL_PARTICLE_COUNT_MUL_F) (int* fid, int* step, int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Count_Mul(*fid, *step, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos2d_mul_f, CG_IRIC_READ_SOL_PARTICLE_POS2D_MUL_F) (int* fid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos2d_Mul(*fid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos3d_mul_f, CG_IRIC_READ_SOL_PARTICLE_POS3D_MUL_F) (int* fid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos3d_Mul(*fid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_real_mul_f, CG_IRIC_READ_SOL_PARTICLE_REAL_MUL_F) (int* fid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Real_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_integer_mul_f, CG_IRIC_READ_SOL_PARTICLE_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Integer_Mul(*fid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos2d_mul_f, CG_IRIC_WRITE_SOL_PARTICLE_POS2D_MUL_F) (int* fid, int* count, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos2d_Mul(*fid, *count, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos3d_mul_f, CG_IRIC_WRITE_SOL_PARTICLE_POS3D_MUL_F) (int* fid, int* count, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos3d_Mul(*fid, *count, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_real_mul_f, CG_IRIC_WRITE_SOL_PARTICLE_REAL_MUL_F) (int* fid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Real_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_integer_mul_f, CG_IRIC_WRITE_SOL_PARTICLE_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Integer_Mul(*fid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_count_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_COUNT_MUL_F) (int* fid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Count_Mul(*fid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos2d_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS2D_MUL_F) (int* fid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos2d_Mul(*fid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos3d_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS3D_MUL_F) (int* fid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, double* z_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos3d_Mul(*fid, *step, c_groupname, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_real_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_REAL_MUL_F) (int* fid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Real_Mul(*fid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_integer_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Integer_Mul(*fid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupbegin_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPBEGIN_MUL_F) (int* fid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_Mul(*fid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupend_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPEND_MUL_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_Mul(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos2d_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS2D_MUL_F) (int* fid, double* x, double* y, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos2d_Mul(*fid, *x, *y);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos3d_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS3D_MUL_F) (int* fid, double* x, double* y, double* z, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos3d_Mul(*fid, *x, *y, *z);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_integer_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Integer_Mul(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_real_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_REAL_MUL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Real_Mul(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_datacount_mul_f, CG_IRIC_READ_SOL_POLYDATA_DATACOUNT_MUL_F) (int* fid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_DataCount_Mul(*fid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_coordinatecount_mul_f, CG_IRIC_READ_SOL_POLYDATA_COORDINATECOUNT_MUL_F) (int* fid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_CoordinateCount_Mul(*fid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_pos2d_mul_f, CG_IRIC_READ_SOL_POLYDATA_POS2D_MUL_F) (int* fid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Pos2d_Mul(*fid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_type_mul_f, CG_IRIC_READ_SOL_POLYDATA_TYPE_MUL_F) (int* fid, int* step, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Type_Mul(*fid, *step, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_real_mul_f, CG_IRIC_READ_SOL_POLYDATA_REAL_MUL_F) (int* fid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Real_Mul(*fid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_integer_mul_f, CG_IRIC_READ_SOL_POLYDATA_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Integer_Mul(*fid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupbegin_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPBEGIN_MUL_F) (int* fid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_GroupBegin_Mul(*fid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupend_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPEND_MUL_F) (int* fid, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_GroupEnd_Mul(*fid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polygon_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYGON_MUL_F) (int* fid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polygon_Mul(*fid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polyline_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYLINE_MUL_F) (int* fid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polyline_Mul(*fid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_integer_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Integer_Mul(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_real_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_REAL_MUL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Real_Mul(*fid, c_name, *value);
}


// from iriclib_solution.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_count_mul_f, CG_IRIC_READ_SOL_COUNT_MUL_F) (int* fid, int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Count_Mul(*fid, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_time_mul_f, CG_IRIC_READ_SOL_TIME_MUL_F) (int* fid, int* step, double* time, int *ier) {
	*ier = cg_iRIC_Read_Sol_Time_Mul(*fid, *step, time);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iteration_mul_f, CG_IRIC_READ_SOL_ITERATION_MUL_F) (int* fid, int* step, int* index, int *ier) {
	*ier = cg_iRIC_Read_Sol_Iteration_Mul(*fid, *step, index);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_integer_mul_f, CG_IRIC_READ_SOL_BASEITERATIVE_INTEGER_MUL_F) (int* fid, int* step, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_Integer_Mul(*fid, *step, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_real_mul_f, CG_IRIC_READ_SOL_BASEITERATIVE_REAL_MUL_F) (int* fid, int* step, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_Real_Mul(*fid, *step, c_name, value);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_stringlen_mul_f, CG_IRIC_READ_SOL_BASEITERATIVE_STRINGLEN_MUL_F) (int* fid, int* step, STR_PSTR(name), int* length, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_StringLen_Mul(*fid, *step, c_name, length);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_baseiterative_string_mul_f, CG_IRIC_READ_SOL_BASEITERATIVE_STRING_MUL_F) (int* fid, int* step, STR_PSTR(name), STR_PSTR(strvalue), int *ier STR_PLEN(name) STR_PLEN(strvalue)) {
	char c_name[STRINGMAXLEN + 1];
	char c_strvalue[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_BaseIterative_String_Mul(*fid, *step, c_name, c_strvalue);

	if (*ier != 0) return;
	string_2_F_string(c_strvalue, STR_PTR(strvalue), STR_LEN(strvalue), ier);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_time_mul_f, CG_IRIC_WRITE_SOL_TIME_MUL_F) (int* fid, double* time, int *ier) {
	*ier = cg_iRIC_Write_Sol_Time_Mul(*fid, *time);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iteration_mul_f, CG_IRIC_WRITE_SOL_ITERATION_MUL_F) (int* fid, int* index, int *ier) {
	*ier = cg_iRIC_Write_Sol_Iteration_Mul(*fid, *index);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_integer_mul_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_INTEGER_MUL_F) (int* fid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_Integer_Mul(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_real_mul_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_REAL_MUL_F) (int* fid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_Real_Mul(*fid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_baseiterative_string_mul_f, CG_IRIC_WRITE_SOL_BASEITERATIVE_STRING_MUL_F) (int* fid, STR_PSTR(name), STR_PSTR(value), int *ier STR_PLEN(name) STR_PLEN(value)) {
	char c_name[STRINGMAXLEN + 1];
	char c_value[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(value), STR_LEN(value), c_value, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_BaseIterative_String_Mul(*fid, c_name, c_value);
}

void IRICLIBDLL FMNAME(cg_iric_write_errorcode_mul_f, CG_IRIC_WRITE_ERRORCODE_MUL_F) (int* fid, int* errorcode, int *ier) {
	*ier = cg_iRIC_Write_ErrorCode_Mul(*fid, *errorcode);
}


// from iriclib_sol_cell.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_integer_withgridid_mul_f, CG_IRIC_READ_SOL_CELL_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Integer_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_cell_real_withgridid_mul_f, CG_IRIC_READ_SOL_CELL_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Cell_Real_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_integer_withgridid_mul_f, CG_IRIC_WRITE_SOL_CELL_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Integer_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_cell_real_withgridid_mul_f, CG_IRIC_WRITE_SOL_CELL_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Cell_Real_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_gridcoord.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_grid2d_coords_withgridid_mul_f, CG_IRIC_READ_SOL_GRID2D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid2d_Coords_WithGridId_Mul(*fid, *gid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_grid3d_coords_withgridid_mul_f, CG_IRIC_READ_SOL_GRID3D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Grid3d_Coords_WithGridId_Mul(*fid, *gid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid2d_coords_withgridid_mul_f, CG_IRIC_WRITE_SOL_GRID2D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* gid, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid2d_Coords_WithGridId_Mul(*fid, *gid, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_grid3d_coords_withgridid_mul_f, CG_IRIC_WRITE_SOL_GRID3D_COORDS_WITHGRIDID_MUL_F) (int* fid, int* gid, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Grid3d_Coords_WithGridId_Mul(*fid, *gid, x_arr, y_arr, z_arr);
}


// from iriclib_sol_iface.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_integer_withgridid_mul_f, CG_IRIC_READ_SOL_IFACE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Integer_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_iface_real_withgridid_mul_f, CG_IRIC_READ_SOL_IFACE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_IFace_Real_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_integer_withgridid_mul_f, CG_IRIC_WRITE_SOL_IFACE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Integer_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_iface_real_withgridid_mul_f, CG_IRIC_WRITE_SOL_IFACE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_IFace_Real_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_jface.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_integer_withgridid_mul_f, CG_IRIC_READ_SOL_JFACE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Integer_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_jface_real_withgridid_mul_f, CG_IRIC_READ_SOL_JFACE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_JFace_Real_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_integer_withgridid_mul_f, CG_IRIC_WRITE_SOL_JFACE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Integer_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_jface_real_withgridid_mul_f, CG_IRIC_WRITE_SOL_JFACE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_JFace_Real_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_kface.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_integer_withgridid_mul_f, CG_IRIC_READ_SOL_KFACE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Integer_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_kface_real_withgridid_mul_f, CG_IRIC_READ_SOL_KFACE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_KFace_Real_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_integer_withgridid_mul_f, CG_IRIC_WRITE_SOL_KFACE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Integer_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_kface_real_withgridid_mul_f, CG_IRIC_WRITE_SOL_KFACE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_KFace_Real_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_node.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_node_integer_withgridid_mul_f, CG_IRIC_READ_SOL_NODE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Integer_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_node_real_withgridid_mul_f, CG_IRIC_READ_SOL_NODE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Node_Real_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_integer_withgridid_mul_f, CG_IRIC_WRITE_SOL_NODE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Integer_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_node_real_withgridid_mul_f, CG_IRIC_WRITE_SOL_NODE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Node_Real_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_particle.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_count_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLE_COUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, int* count, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Count_WithGridId_Mul(*fid, *gid, *step, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos2d_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLE_POS2D_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos2d_WithGridId_Mul(*fid, *gid, *step, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_pos3d_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLE_POS3D_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Read_Sol_Particle_Pos3d_WithGridId_Mul(*fid, *gid, *step, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_real_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Real_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particle_integer_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_Particle_Integer_WithGridId_Mul(*fid, *gid, *step, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos2d_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLE_POS2D_WITHGRIDID_MUL_F) (int* fid, int* gid, int* count, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos2d_WithGridId_Mul(*fid, *gid, *count, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_pos3d_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLE_POS3D_WITHGRIDID_MUL_F) (int* fid, int* gid, int* count, double* x_arr, double* y_arr, double* z_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_Particle_Pos3d_WithGridId_Mul(*fid, *gid, *count, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_real_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLE_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Real_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particle_integer_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLE_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* v_arr, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_Particle_Integer_WithGridId_Mul(*fid, *gid, c_name, v_arr);
}


// from iriclib_sol_particlegroup.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_count_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_COUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Count_WithGridId_Mul(*fid, *gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos2d_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS2D_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos2d_WithGridId_Mul(*fid, *gid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_pos3d_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_POS3D_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, double* z_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Pos3d_WithGridId_Mul(*fid, *gid, *step, c_groupname, x_arr, y_arr, z_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_real_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Real_WithGridId_Mul(*fid, *gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_particlegroup_integer_withgridid_mul_f, CG_IRIC_READ_SOL_PARTICLEGROUP_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_ParticleGroup_Integer_WithGridId_Mul(*fid, *gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupbegin_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPBEGIN_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupBegin_WithGridId_Mul(*fid, *gid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_groupend_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_GROUPEND_WITHGRIDID_MUL_F) (int* fid, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_GroupEnd_WithGridId_Mul(*fid, *gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos2d_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS2D_WITHGRIDID_MUL_F) (int* fid, int* gid, double* x, double* y, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos2d_WithGridId_Mul(*fid, *gid, *x, *y);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_pos3d_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_POS3D_WITHGRIDID_MUL_F) (int* fid, int* gid, double* x, double* y, double* z, int *ier) {
	*ier = cg_iRIC_Write_Sol_ParticleGroup_Pos3d_WithGridId_Mul(*fid, *gid, *x, *y, *z);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_integer_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Integer_WithGridId_Mul(*fid, *gid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_particlegroup_real_withgridid_mul_f, CG_IRIC_WRITE_SOL_PARTICLEGROUP_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_ParticleGroup_Real_WithGridId_Mul(*fid, *gid, c_name, *value);
}


// from iriclib_sol_polydata.h
void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_datacount_withgridid_mul_f, CG_IRIC_READ_SOL_POLYDATA_DATACOUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_DataCount_WithGridId_Mul(*fid, *gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_coordinatecount_withgridid_mul_f, CG_IRIC_READ_SOL_POLYDATA_COORDINATECOUNT_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), int* count, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_CoordinateCount_WithGridId_Mul(*fid, *gid, *step, c_groupname, count);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_pos2d_withgridid_mul_f, CG_IRIC_READ_SOL_POLYDATA_POS2D_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), double* x_arr, double* y_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Pos2d_WithGridId_Mul(*fid, *gid, *step, c_groupname, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_type_withgridid_mul_f, CG_IRIC_READ_SOL_POLYDATA_TYPE_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), int* v_arr, int *ier STR_PLEN(groupname)) {
	char c_groupname[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Type_WithGridId_Mul(*fid, *gid, *step, c_groupname, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_real_withgridid_mul_f, CG_IRIC_READ_SOL_POLYDATA_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), double* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Real_WithGridId_Mul(*fid, *gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_read_sol_polydata_integer_withgridid_mul_f, CG_IRIC_READ_SOL_POLYDATA_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, int* step, STR_PSTR(groupname), STR_PSTR(name), int* v_arr, int *ier STR_PLEN(groupname) STR_PLEN(name)) {
	char c_groupname[STRINGMAXLEN + 1];
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(groupname), STR_LEN(groupname), c_groupname, STRINGMAXLEN, ier);
	if (*ier != 0) return;
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Read_Sol_PolyData_Integer_WithGridId_Mul(*fid, *gid, *step, c_groupname, c_name, v_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupbegin_withgridid_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPBEGIN_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_GroupBegin_WithGridId_Mul(*fid, *gid, c_name);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_groupend_withgridid_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_GROUPEND_WITHGRIDID_MUL_F) (int* fid, int* gid, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_GroupEnd_WithGridId_Mul(*fid, *gid);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polygon_withgridid_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYGON_WITHGRIDID_MUL_F) (int* fid, int* gid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polygon_WithGridId_Mul(*fid, *gid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_polyline_withgridid_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_POLYLINE_WITHGRIDID_MUL_F) (int* fid, int* gid, int* numPoints, double* x_arr, double* y_arr, int *ier) {
	*ier = cg_iRIC_Write_Sol_PolyData_Polyline_WithGridId_Mul(*fid, *gid, *numPoints, x_arr, y_arr);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_integer_withgridid_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_INTEGER_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), int* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Integer_WithGridId_Mul(*fid, *gid, c_name, *value);
}

void IRICLIBDLL FMNAME(cg_iric_write_sol_polydata_real_withgridid_mul_f, CG_IRIC_WRITE_SOL_POLYDATA_REAL_WITHGRIDID_MUL_F) (int* fid, int* gid, STR_PSTR(name), double* value, int *ier STR_PLEN(name)) {
	char c_name[STRINGMAXLEN + 1];
	string_2_C_string(STR_PTR(name), STR_LEN(name), c_name, STRINGMAXLEN, ier);
	if (*ier != 0) return;

	*ier = cg_iRIC_Write_Sol_PolyData_Real_WithGridId_Mul(*fid, *gid, c_name, *value);
}


} // extern "C"
