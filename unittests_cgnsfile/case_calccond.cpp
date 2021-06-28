#include "macros.h"

#include "fs_copy.h"

#include <iriclib.h>

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

extern "C" {

void case_CalcCondRead()
{
	remove("case_cc.cgn");
	fs::copy("case_init_hdf5.cgn", "case_cc.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_cc.cgn", IRIC_MODE_MODIFY, &fid);

	VERIFY_LOG("cg_iRIC_Open() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Open() fid != 0", fid != 0);

	int cond_int;

	ier = cg_iRIC_Read_Integer(fid, "intval", &cond_int);
	VERIFY_LOG("cg_iRIC_Read_Integer() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Integer() val == 1", cond_int == 1);

	ier = cg_iRIC_Read_Integer(fid, "intval2", &cond_int);
	VERIFY_LOG("cg_iRIC_Read_Integer() ier != 0 for invalid value", ier != 0);

	double cond_double;

	ier = cg_iRIC_Read_Real(fid, "doubleval", &cond_double);
	VERIFY_LOG("cg_iRIC_Read_Real() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Real() val == 1", cond_double == 4.21);

	ier = cg_iRIC_Read_Real(fid, "doubleval2", &cond_double);
	VERIFY_LOG("cg_iRIC_Read_Real() ier != 0 for invalid value", ier != 0);

	int string_len;
	std::vector<char> strbuffer;

	ier = cg_iRIC_Read_StringLen(fid, "stringval", &string_len);
	VERIFY_LOG("cg_iRIC_Read_StringLen() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_StringLen() val == 10", string_len == 10);

	strbuffer.assign(string_len + 1, ' ');
	ier = cg_iRIC_Read_String(fid, "stringval", strbuffer.data());
	VERIFY_LOG("cg_iRIC_Read_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_String() val == TESTSTRING", std::string("TESTSTRING") == std::string(strbuffer.data()));

	ier = cg_iRIC_Read_StringLen(fid, "stringval2", &string_len);
	VERIFY_LOG("cg_iRIC_Read_StringLen() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_String(fid, "stringval2", strbuffer.data());
	VERIFY_LOG("cg_iRIC_Read_String() ier != 0 for invalid value", ier != 0);

	int fsize;
	ier = cg_iRIC_Read_FunctionalSize(fid, "func1", &fsize);
	VERIFY_LOG("cg_iRIC_Read_FunctionalSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalSize() val == 4", fsize == 4);

	std::vector<double> params, values;
	params.assign(fsize, 0);
	values.assign(fsize, 0);

	ier = cg_iRIC_Read_Functional(fid, "func1", params.data(), values.data());
	VERIFY_LOG("cg_iRIC_Read_Functional() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Functional() param value[0]", params.at(0) == 0);
	VERIFY_LOG("cg_iRIC_Read_Functional() param value[1]", params.at(1) == 1);
	VERIFY_LOG("cg_iRIC_Read_Functional() param value[2]", params.at(2) == 2);
	VERIFY_LOG("cg_iRIC_Read_Functional() param value[3]", params.at(3) == 3);
	VERIFY_LOG("cg_iRIC_Read_Functional() value value[0]", values.at(0) == 0);
	VERIFY_LOG("cg_iRIC_Read_Functional() value value[1]", values.at(1) == 3);
	VERIFY_LOG("cg_iRIC_Read_Functional() value value[2]", values.at(2) == 4.5);
	VERIFY_LOG("cg_iRIC_Read_Functional() value value[3]", values.at(3) == 2.8);

	ier = cg_iRIC_Read_FunctionalSize(fid, "func100", &fsize);
	VERIFY_LOG("cg_iRIC_Read_FunctionalSize() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_Functional(fid, "func100", params.data(), values.data());
	VERIFY_LOG("cg_iRIC_Read_Functional() ier != 0 for invalid value", ier != 0);

	ier = cg_iRIC_Read_FunctionalSize(fid, "func2", &fsize);
	VERIFY_LOG("cg_iRIC_Read_FunctionalSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalSize() val == 5", fsize == 5);

	params.assign(fsize, 0);
	values.assign(fsize, 0);

	ier = cg_iRIC_Read_FunctionalWithName(fid, "func2", "time", params.data());
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() ier == 0", ier == 0);
	ier = cg_iRIC_Read_FunctionalWithName(fid, "func2", "value2", values.data());
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() ier == 0", ier == 0);

	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() param value[0]", params.at(0) == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() param value[1]", params.at(1) == 3);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() param value[2]", params.at(2) == 4);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() param value[3]", params.at(3) == 6);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() param value[4]", params.at(4) == 8);

	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() value value[0]", values.at(0) == 4.5);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() value value[1]", values.at(1) == 8);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() value value[2]", values.at(2) == 5);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() value value[3]", values.at(3) == 4);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() value value[4]", values.at(4) == 4.2);

	ier = cg_iRIC_Read_FunctionalWithName(fid, "func200", "time", params.data());
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName() ier != 0 for invalid value", ier != 0);

	float floatv;

	ier = cg_iRIC_Read_RealSingle(fid, "singleval", &floatv);
	VERIFY_LOG("cg_iRIC_Read_RealSingle() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_RealSingle() val == 3.88", fabs(floatv - 3.88) < 0.001);

	ier = cg_iRIC_Read_RealSingle(fid, "singleval2", &floatv);
	VERIFY_LOG("cg_iRIC_Read_RealSingle() ier != 0 for invalid name ", ier != 0);

	std::vector<float> floatparams, floatvalues;

	floatparams.assign(4, 0);
	floatvalues.assign(4, 0);

	ier = cg_iRIC_Read_Functional_RealSingle(fid, "func1", floatparams.data(), floatvalues.data());
	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() ier == 0", ier == 0);

	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() param value[0]", floatparams.at(0) == 0);
	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() param value[1]", floatparams.at(1) == 1);
	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() param value[2]", floatparams.at(2) == 2);
	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() param value[3]", floatparams.at(3) == 3);
	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() value value[0]", floatvalues.at(0) == 0);
	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() value value[1]", floatvalues.at(1) == 3);
	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() value value[2]", floatvalues.at(2) == 4.5);
	VERIFY_LOG("cg_iRIC_Read_Functional_RealSingle() value value[3]", fabs(floatvalues.at(3) - 2.8) < 0.001);

	cg_iRIC_Close(fid);

	remove("case_cc.cgn");
}

void case_CalcCondWrite()
{
	fs::copy("case_init_hdf5.cgn", "case_ccwrite.cgn");

	int fid;
	int ier = cg_iRIC_Open("case_ccwrite.cgn", IRIC_MODE_MODIFY, &fid);

	int fid_wrong = 9999;

	int write_int = 121;
	ier = cg_iRIC_Write_Integer(fid, "write_int", write_int);
	VERIFY_LOG("cg_iRIC_Write_Integer() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Integer(fid_wrong, "write_int", write_int);
	VERIFY_LOG("cg_iRIC_Write_Integer() ier != 0 for invalid fid", ier != 0);

	double write_double = 3.14159;
	ier = cg_iRIC_Write_Real(fid, "write_double", write_double);
	VERIFY_LOG("cg_iRIC_Write_Real() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Real(fid_wrong, "write_double", write_double);
	VERIFY_LOG("cg_iRIC_Write_Real() ier != 0 for invalid fid", ier != 0);

	std::string write_str = "TEST_STRING_3.14";
	ier = cg_iRIC_Write_String(fid, "write_string", write_str.c_str());
	VERIFY_LOG("cg_iRIC_Write_String() ier == 0", ier == 0);

	ier = cg_iRIC_Write_String(fid_wrong, "write_string", write_str.c_str());
	VERIFY_LOG("cg_iRIC_Write_String() ier != 0 for invalid fid", ier != 0);

	std::vector<double> params, vals;
	params.assign(5, 0);
	vals.assign(5, 0);

	for (int i = 0; i < 5; ++i){
		params[i] = 2.3 * i + 1.2;
		vals[i] = 5.1 * i + 0.8;
	}
	ier = cg_iRIC_Write_Functional(fid, "write_func", 5, params.data(), vals.data());
	VERIFY_LOG("cg_iRIC_Write_Functional() ier == 0", ier == 0);

	ier = cg_iRIC_Write_Functional(fid_wrong, "write_func", 5, params.data(), vals.data());
	VERIFY_LOG("cg_iRIC_Write_String() ier != 0 for invalid fid", ier != 0);

	ier = cg_iRIC_Write_FunctionalWithName(fid, "write_func_withname", "time", params.size(), params.data());
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName() ier == 0", ier == 0);
	ier = cg_iRIC_Write_FunctionalWithName(fid, "write_func_withname", "elev", vals.size(), vals.data());
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName() ier == 0", ier == 0);

	ier = cg_iRIC_Write_FunctionalWithName(fid_wrong, "write_func_withname", "time", params.size(), params.data());
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName() ier != 0 for invalid fid", ier != 0);

	ier = cg_iRIC_Write_FunctionalWithName(fid, "write_func_withname_string", "time", params.size(), params.data());
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName() ier == 0", ier == 0);
	ier = cg_iRIC_Write_FunctionalWithName(fid, "write_func_withname_string", "discharge", vals.size(), vals.data());
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName() ier == 0", ier == 0);

	ier = cg_iRIC_Write_FunctionalWithName_String(fid, "write_func_withname_string", "_siteID", "01646500");
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName_String() ier == 0", ier == 0);
	ier = cg_iRIC_Write_FunctionalWithName_String(fid, "write_func_withname_string", "_startDate", "2017-06-01T06:00");
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName_String() ier == 0", ier == 0);
	ier = cg_iRIC_Write_FunctionalWithName_String(fid, "write_func_withname_string", "_endDate", "2017-06-01T10:00");
	VERIFY_LOG("cg_iRIC_Write_FunctionalWithName_String() ier == 0", ier == 0);

	int read_int;
	ier = cg_iRIC_Read_Integer(fid, "write_int", &read_int);
	VERIFY_LOG("cg_iRIC_Read_Integer() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Integer() value match", read_int == write_int);

	double read_double;
	ier = cg_iRIC_Read_Real(fid, "write_double", &read_double);
	VERIFY_LOG("cg_iRIC_Read_Real() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Real() value match", read_double == read_double);

	int read_strlen;
	std::vector<char> read_str;
	ier = cg_iRIC_Read_StringLen(fid, "write_string", &read_strlen);
	read_str.assign(read_strlen + 1, ' ');
	ier = cg_iRIC_Read_String(fid, "write_string", read_str.data());
	VERIFY_LOG("cg_iRIC_Read_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_String() value match", std::string(read_str.data()) == write_str);

	int func_len = 0;
	std::vector<double> read_params, read_vals;
	ier = cg_iRIC_Read_FunctionalSize(fid, "write_func", &func_len);
	VERIFY_LOG("cg_iRIC_Read_FunctionalSize() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalSize() value == 5", func_len == 5);

	read_params.assign(func_len, 0);
	read_vals.assign(func_len, 0);
	ier = cg_iRIC_Read_Functional(fid, "write_func", read_params.data(), read_vals.data());
	VERIFY_LOG("cg_iRIC_Read_Functional() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_Functional() param match", params == read_params);
	VERIFY_LOG("cg_iRIC_Read_Functional() value match", vals == read_vals);

	ier = cg_iRIC_Read_FunctionalWithName_StringLen(fid, "write_func_withname_string", "_siteID", &read_strlen);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_StringLen() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_StringLen() length == 8", 8 == read_strlen);
	read_str.assign(read_strlen + 1, ' ');
	ier = cg_iRIC_Read_FunctionalWithName_String(fid, "write_func_withname_string", "_siteID", read_str.data());
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_String() value match", std::string(read_str.data()) == "01646500");

	ier = cg_iRIC_Read_FunctionalWithName_StringLen(fid, "write_func_withname_string", "_startDate", &read_strlen);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_StringLen() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_StringLen() length == 16", 16 == read_strlen);
	read_str.assign(read_strlen + 1, ' ');
	ier = cg_iRIC_Read_FunctionalWithName_String(fid, "write_func_withname_string", "_startDate", read_str.data());
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_String() value match", std::string(read_str.data()) == "2017-06-01T06:00");

	ier = cg_iRIC_Read_FunctionalWithName_StringLen(fid, "write_func_withname_string", "_endDate", &read_strlen);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_StringLen() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_StringLen() length == 16", 16 == read_strlen);
	read_str.assign(read_strlen + 1, ' ');
	ier = cg_iRIC_Read_FunctionalWithName_String(fid, "write_func_withname_string", "_endDate", read_str.data());
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_String() ier == 0", ier == 0);
	VERIFY_LOG("cg_iRIC_Read_FunctionalWithName_String() value match", std::string(read_str.data()) == "2017-06-01T10:00");

	cg_iRIC_Close(fid);

	remove("case_ccwrite.cgn");
}

} // extern "C"
