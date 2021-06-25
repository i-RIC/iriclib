#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>

#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

extern "C" {

void case_BcRead()
{
	remove("case_bc.cgn");
	fs::copy("case_init_hdf5.cgn", "case_bc.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_bc.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	int bc_count;

	cg_iRIC_Read_BC_Count(fid, "bctest", &bc_count);
	VERIFY_LOG("cg_iRIC_Read_BC_Count() bc_count == 2", bc_count == 2);

	int bc_indicessize;

	ier = cg_iRIC_Read_BC_IndicesSize(fid, "bctest", 1, &bc_indicessize);
	VERIFY_LOG("cg_iRIC_Read_BC_IndicesSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_IndicesSize() bc_indicessize == 5", bc_indicessize == 5);

	ier = cg_iRIC_Read_BC_IndicesSize(fid, "bctestaa", 1, &bc_indicessize);
	VERIFY_LOG("cg_iRIC_Read_BC_IndicesSize() ier != 0 if name is invalid", ier != 0);

	ier = cg_iRIC_Read_BC_IndicesSize(fid, "bctest", 3, &bc_indicessize);
	VERIFY_LOG("cg_iRIC_Read_BC_IndicesSize() ier != 0 if num is invalid", ier != 0);

	ier = cg_iRIC_Read_BC_IndicesSize2(fid, "bctest", 1, &bc_indicessize);
	VERIFY_LOG("cg_iRIC_Read_BC_IndicesSize2() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_IndicesSize2() bc_indicessize == 10", bc_indicessize == 10);

	std::vector<int> indices;
	indices.assign(10, 0);

	ier = cg_iRIC_Read_BC_Indices(fid, "bctest", 1, indices.data());
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[0] == 1", indices[0] == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[1] == 1", indices[1] == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[2] == 1", indices[2] == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[3] == 2", indices[3] == 2);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[4] == 1", indices[4] == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[5] == 3", indices[5] == 3);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[6] == 1", indices[6] == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[7] == 4", indices[7] == 4);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[8] == 1", indices[8] == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_Indices() indices[9] == 5", indices[9] == 5);

	int cond_int;

	ier = cg_iRIC_Read_BC_Integer(fid, "bctest", 1, "intparam", &cond_int);
	VERIFY_LOG("cg_iRIC_Read_BC_Integer() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Integer() val == 1", cond_int == 1);

	ier = cg_iRIC_Read_BC_Integer(fid, "bctestaa", 1, "intparam", &cond_int);
	VERIFY_LOG("cg_iRIC_Read_BC_Integer() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_BC_Integer(fid, "bctest", 4, "intparam", &cond_int);
	VERIFY_LOG("cg_iRIC_Read_BC_Integer() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_BC_Integer(fid, "bctest", 1, "intparam2", &cond_int);
	VERIFY_LOG("cg_iRIC_Read_BC_Integer() ier != 0 for invalid value", ier != 0);

	double cond_double;

	ier = cg_iRIC_Read_BC_Real(fid, "bctest", 1, "realparam", &cond_double);
	VERIFY_LOG("cg_iRIC_Read_BC_Real() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Real() val == 4.2", cond_double == 4.2);

	ier = cg_iRIC_Read_BC_Real(fid, "bctest", 1, "realparam2", &cond_double);
	VERIFY_LOG("cg_iRIC_Read_BC_Real() ier != 0 for invalid value", ier != 0);

	int string_len;
	std::vector<char> strbuffer;

	ier = cg_iRIC_Read_BC_StringLen(fid, "bctest", 1, "stringparam", &string_len);
	VERIFY_LOG("cg_iRIC_Read_BC_StringLen() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_StringLen() val == 3", string_len == 3);

	strbuffer.assign(string_len + 1, ' ');
	ier = cg_iRIC_Read_BC_String(fid, "bctest", 1, "stringparam", strbuffer.data());
	VERIFY_LOG("cg_iRIC_Read_BC_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_String() val == AAA", std::string("AAA") == std::string(strbuffer.data()));

	ier = cg_iRIC_Read_BC_StringLen(fid, "bctest_dummy", 1, "stringparam", &string_len);
	VERIFY_LOG("cg_iRIC_Read_BC_StringLen() ier != 0", ier != 0);

	ier = cg_iRIC_Read_BC_StringLen(fid, "bctest", 4, "stringparam", &string_len);
	VERIFY_LOG("cg_iRIC_Read_BC_StringLen() ier != 0", ier != 0);

	ier = cg_iRIC_Read_BC_StringLen(fid, "bctest", 1, "stringparam2", &string_len);
	VERIFY_LOG("cg_iRIC_Read_BC_StringLen() ier != 0", ier != 0);

	ier = cg_iRIC_Read_BC_String(fid, "bctest", 1, "stringval2", strbuffer.data());
	VERIFY_LOG("cg_iRIC_Read_BC_String() ier != 0 for invalid value", ier != 0);

	int fsize;
	ier = cg_iRIC_Read_BC_FunctionalSize(fid, "bctest", 1, "funcparam", &fsize);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalSize() val == 4", fsize == 3);

	std::vector<double> params, values;
	params.assign(fsize, 0);
	values.assign(fsize, 0);

	ier = cg_iRIC_Read_BC_Functional(fid, "bctest", 1, "funcparam", params.data(), values.data());
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() param value[0]", params.at(0) == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() param value[1]", params.at(1) == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() param value[2]", params.at(2) == 2);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() value value[0]", values.at(0) == 5);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() value value[1]", values.at(1) == 4);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() value value[2]", values.at(2) == 2);

	ier = cg_iRIC_Read_BC_FunctionalSize(fid, "bctest_dmmy", 1, "funcparam", &fsize);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalSize() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_BC_FunctionalSize(fid, "bctest", 5, "funcparam", &fsize);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalSize() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_BC_FunctionalSize(fid, "bctest", 1, "funcpareem", &fsize);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalSize() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_BC_Functional(fid, "bctest", 1, "func100", params.data(), values.data());
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_BC_FunctionalWithName(fid, "bctest", 1, "funcparam", "Param", params.data());
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName() ier == 0", ier == 0);
	ier = cg_iRIC_Read_BC_FunctionalWithName(fid, "bctest", 1, "funcparam", "Value", values.data());
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName() ier == 0", ier == 0);

	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName() param value[0]", params.at(0) == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName() param value[1]", params.at(1) == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName() param value[2]", params.at(2) == 2);

	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName() value value[0]", values.at(0) == 5);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName() value value[1]", values.at(1) == 4);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName() value value[2]", values.at(2) == 2);

	float floatv;

	ier = cg_iRIC_Read_BC_RealSingle(fid, "bctest", 1, "realparam", &floatv);
	VERIFY_LOG("cg_iRIC_Read_BC_RealSingle() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_RealSingle() val == 4.2", fabs(floatv - 4.2) < 0.001);

	ier = cg_iRIC_Read_BC_RealSingle(fid, "bctest", 1, "realparam2", &floatv);
	VERIFY_LOG("cg_iRIC_Read_BC_RealSingle() ier != 0 for invalid name ", ier != 0);

	std::vector<float> floatparams, floatvalues;

	floatparams.assign(3, 0);
	floatvalues.assign(3, 0);

	ier = cg_iRIC_Read_BC_Functional_RealSingle(fid, "bctest", 1, "funcparam", floatparams.data(), floatvalues.data());
	VERIFY_LOG("cg_iRIC_Read_BC_Functional_RealSingle() ier == 0", ier == 0);

	VERIFY_LOG("cg_iRIC_Read_BC_Functional_RealSingle() param value[0]", floatparams.at(0) == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional_RealSingle() param value[1]", floatparams.at(1) == 1);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional_RealSingle() param value[2]", floatparams.at(2) == 2);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional_RealSingle() value value[0]", floatvalues.at(0) == 5);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional_RealSingle() value value[1]", floatvalues.at(1) == 4);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional_RealSingle() value value[2]", floatvalues.at(2) == 2);

	cg_iRIC_Close(fid);

	remove("case_bc.cgn");
}

void case_BcWrite()
{
	fs::copy("case_init_hdf5.cgn", "case_bcwrite.cgn");

	int fid;
	int fid_wrong = 9999;

	int ier = cg_iRIC_Open("case_bcwrite.cgn", IRIC_MODE_MODIFY, &fid);
	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	ier = cg_iRIC_Clear_BC(fid);
	VERIFY_LOG("cg_iRIC_Clear_BC() ier == 0", ier == 0);

	std::vector<int> indices;
	indices.assign(10, 1);
	for (int i = 0; i < 5; ++i) {
		indices[i * 2 + 1] = i + 3;
	};
	ier = cg_iRIC_Write_BC_Indices(fid, "testbc", 1, 5, indices.data());
	VERIFY_LOG("cg_iRIC_Write_BC_Indices() ier == 0", ier == 0);

	int write_int = 121;
	ier = cg_iRIC_Write_BC_Integer(fid, "testbc", 1, "write_int", write_int);
	VERIFY_LOG("cg_iRIC_Write_BC_Integer() ier == 0", ier == 0);

	ier = cg_iRIC_Write_BC_Integer(fid_wrong, "testbc", 1, "write_int", write_int);
	VERIFY_LOG("cg_iRIC_Write_BC_Integer() ier != 0 for invalid fid", ier != 0);

	double write_double = 3.14159;
	ier = cg_iRIC_Write_BC_Real(fid, "testbc", 1, "write_double", write_double);
	VERIFY_LOG("cg_iRIC_Write_BC_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_BC_Real(fid_wrong, "testbc", 1, "write_double", write_double);
	VERIFY_LOG("cg_iRIC_Write_BC_Real() ier != 0 for invalid fid", ier != 0);

	std::string write_str = "TEST_STRING_3.14";
	ier = cg_iRIC_Write_BC_String(fid, "testbc", 1, "write_string", write_str.c_str());
	VERIFY_LOG("cg_iRIC_Write_BC_String() ier == 0", ier == 0);

	ier = cg_iRIC_Write_BC_String(fid_wrong, "testbc", 1, "write_string", write_str.c_str());
	VERIFY_LOG("cg_iRIC_Write_BC_String() ier != 0 for invalid fid", ier != 0);

	std::vector<double> params, vals;
	params.assign(5, 0);
	vals.assign(5, 0);

	for (int i = 0; i < 5; ++i){
		params[i] = 2.3 * i + 1.2;
		vals[i] = 5.1 * i + 0.8;
	}
	ier = cg_iRIC_Write_BC_Functional(fid, "testbc", 1, "write_func", 5, params.data(), vals.data());
	VERIFY_LOG("cg_iRIC_BC_Write_Functional() ier == 0", ier == 0);

	ier = cg_iRIC_Write_BC_Functional(fid_wrong, "testbc", 1, "write_func", 5, params.data(), vals.data());
	VERIFY_LOG("cg_iRIC_BC_Write_Functional() ier != 0 for invalid fid", ier != 0);

	ier = cg_iRIC_Write_BC_FunctionalWithName(fid, "testbc", 1, "write_func_withname", "time", (int)params.size(), params.data());
	VERIFY_LOG("cg_iRIC_BC_Write_FunctionalWithName() ier == 0", ier == 0);
	ier = cg_iRIC_Write_BC_FunctionalWithName(fid, "testbc", 1, "write_func_withname", "elev", (int)vals.size(), vals.data());
	VERIFY_LOG("cg_iRIC_BC_Write_FunctionalWithName() ier == 0", ier == 0);

	ier = cg_iRIC_Write_BC_FunctionalWithName(fid_wrong, "testbc", 1, "write_func_withname", "time", (int)params.size(), params.data());
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName() ier != 0 for invalid fid", ier != 0);

	ier = cg_iRIC_Write_BC_FunctionalWithName(fid, "testbc", 1, "write_func_withname_string", "time", (int)params.size(), params.data());
	VERIFY_LOG("cg_iRIC_BC_Write_FunctionalWithName() ier == 0", ier == 0);
	ier = cg_iRIC_Write_BC_FunctionalWithName(fid, "testbc", 1, "write_func_withname_string", "elev", (int)vals.size(), vals.data());
	VERIFY_LOG("cg_iRIC_BC_Write_FunctionalWithName() ier == 0", ier == 0);

	ier = cg_iRIC_Write_BC_FunctionalWithName_String(fid, "testbc", 1, "write_func_withname_string", "_siteID", "01646500");
	VERIFY_LOG("cg_iRIC_Write_BC_FunctionalWithName_String() ier == 0", ier == 0);
	ier = cg_iRIC_Write_BC_FunctionalWithName_String(fid, "testbc", 1, "write_func_withname_string", "_startDate", "2017-06-01T06:00");
	VERIFY_LOG("cg_iRIC_Write_BC_FunctionalWithName_String() ier == 0", ier == 0);
	ier = cg_iRIC_Write_BC_FunctionalWithName_String(fid, "testbc", 1, "write_func_withname_string", "_endDate", "2017-06-01T10:00");
	VERIFY_LOG("cg_iRIC_Write_BC_FunctionalWithName_String() ier == 0", ier == 0);

	int read_num;
	cg_iRIC_Read_BC_Count(fid, "testbc", &read_num);
	VERIFY_LOG("cg_iRIC_Read_BC_Count() read_num == 1", read_num == 1);

	int read_indicessize;
	ier = cg_iRIC_Read_BC_IndicesSize(fid, "testbc", 1, &read_indicessize);
	VERIFY_LOG("cg_iRIC_Read_BC_IndicesSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_IndicesSize() read_indicessize == 5", read_indicessize == 5);

	int read_int;
	ier = cg_iRIC_Read_BC_Integer(fid, "testbc", 1, "write_int", &read_int);
	VERIFY_LOG("cg_iRIC_Read_BC_Integer() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Integer() value match", read_int == write_int);

	double read_double;
	ier = cg_iRIC_Read_BC_Real(fid, "testbc", 1, "write_double", &read_double);
	VERIFY_LOG("cg_iRIC_Read_BC_Real() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Real() value match", read_double == read_double);

	int read_strlen;
	std::vector<char> read_str;
	ier = cg_iRIC_Read_BC_StringLen(fid, "testbc", 1, "write_string", &read_strlen);
	read_str.assign(read_strlen + 1, ' ');
	ier = cg_iRIC_Read_BC_String(fid, "testbc", 1, "write_string", read_str.data());
	VERIFY_LOG("cg_iRIC_Read_BC_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_String() value match", std::string(read_str.data()) == write_str);

	int func_len;
	std::vector<double> read_params, read_vals;
	ier = cg_iRIC_Read_BC_FunctionalSize(fid, "testbc", 1, "write_func", &func_len);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalSize() value == 5", func_len == 5);

	read_params.assign(func_len, 0);
	read_vals.assign(func_len, 0);
	ier = cg_iRIC_Read_BC_Functional(fid, "testbc", 1, "write_func", read_params.data(), read_vals.data());
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() param match", params == read_params);
	VERIFY_LOG("cg_iRIC_Read_BC_Functional() value match", vals == read_vals);

	ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen(fid, "testbc", 1, "write_func_withname_string", "_siteID", &read_strlen);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_StringLen() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_StringLen() length == 8", 8 == read_strlen);
	read_str.assign(read_strlen + 1, ' ');
	ier = cg_iRIC_Read_BC_FunctionalWithName_String(fid, "testbc", 1, "write_func_withname_string", "_siteID", read_str.data());
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_String() value match", std::string(read_str.data()) == "01646500");

	ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen(fid, "testbc", 1, "write_func_withname_string", "_startDate", &read_strlen);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName_StringLen() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName_StringLen() length == 16", 16 == read_strlen);
	read_str.assign(read_strlen + 1, ' ');
	ier = cg_iRIC_Read_BC_FunctionalWithName_String(fid, "testbc", 1, "write_func_withname_string", "_startDate", read_str.data());
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName_String() value match", std::string(read_str.data()) == "2017-06-01T06:00");

	ier = cg_iRIC_Read_BC_FunctionalWithName_StringLen(fid, "testbc", 1, "write_func_withname_string", "_endDate", &read_strlen);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName_StringLen() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName_StringLen() length == 16", 16 == read_strlen);
	read_str.assign(read_strlen + 1, ' ');
	ier = cg_iRIC_Read_BC_FunctionalWithName_String(fid, "testbc", 1, "write_func_withname_string", "_endDate", read_str.data());
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_BC_FunctionalWithName_String() value match", std::string(read_str.data()) == "2017-06-01T10:00");

	cg_iRIC_Close(fid);

	remove("case_bcwrite.cgn");
}

} // extern "C"
