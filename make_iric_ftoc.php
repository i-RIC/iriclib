<?php
print <<< END
#define NAME_MAXLENGTH 200
#include "fortran_macros.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <cgnslib.h>
#include <cgns_io.h>

#include "iriclib.h"

#define CCNODE "CalculationConditions"
#define GCNODE "GridConditions"
#define STRINGMAXLEN 2048



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


END;
$fp = fopen("iriclib.h", "r");
$fp2 = fopen("iric_ftoc_part.c", "w");

$ignorefuncs = array(
"cg_iRIC_GotoBase",
"cg_iRIC_GotoCC",
"cg_iRIC_GotoRawDataTop",
"cg_iRIC_Write_Integer",
"cg_iRIC_Write_Real",
"cg_iRIC_Write_String",
"cg_iRIC_Write_Functional",
"cg_iRIC_Write_FunctionalWithName",
"cg_iRIC_Clear_Complex",
"cg_iRIC_Write_Complex_Integer",
"cg_iRIC_Write_Complex_Real",
"cg_iRIC_Write_Complex_String",
"cg_iRIC_Write_Complex_Functional",
"cg_iRIC_Write_Complex_FunctionalWithName",
"cg_iRIC_Write_Grid_Complex_Node",
"cg_iRIC_Write_Grid_Complex_Cell",
"cg_iRIC_Init_BC_Names",
"cg_iRIC_Set_ZoneId",
"cg_iRIC_Clear_BC",
"cg_iRIC_Write_BC_Indices",
"cg_iRIC_Write_BC_Integer",
"cg_iRIC_Write_BC_Real",
"cg_iRIC_Write_BC_String",
"cg_iRIC_Write_BC_Functional",
"cg_iRIC_Write_BC_FunctionalWithName",

"cg_iRIC_Write_Integer_Mul",
"cg_iRIC_Write_Real_Mul",
"cg_iRIC_Write_String_Mul",
"cg_iRIC_Write_Functional_Mul",
"cg_iRIC_Write_FunctionalWithName_Mul",
"cg_iRIC_Clear_Complex_Mul",
"cg_iRIC_Write_Complex_Integer_Mul",
"cg_iRIC_Write_Complex_Real_Mul",
"cg_iRIC_Write_Complex_String_Mul",
"cg_iRIC_Write_Complex_Functional_Mul",
"cg_iRIC_Write_Complex_FunctionalWithName_Mul",
"cg_iRIC_Write_Grid_Complex_Node_Mul",
"cg_iRIC_Write_Grid_Complex_Cell_Mul",
"cg_iRIC_Init_BC_Names_Mul",
"cg_iRIC_Set_ZoneId_Mul",
"cg_iRIC_Clear_BC_Mul",
"cg_iRIC_Write_BC_Indices_Mul",
"cg_iRIC_Write_BC_Integer_Mul",
"cg_iRIC_Write_BC_Real_Mul",
"cg_iRIC_Write_BC_String_Mul",
"cg_iRIC_Write_BC_Functional_Mul",
"cg_iRIC_Write_BC_FunctionalWithName_Mul",

);


while (! feof($fp)){
	$line = fgets($fp);
//	echo $line;
	if (strpos($line, "/*") !== FALSE){
		// skip comment
		continue;
	}
	if (preg_match("/^ *(.+) +IRICLIBDLL +(.+)\\((.*)\\)/", $line, $matches)){
	//	print_r($matches);

		$rettype  = $matches[1];
		$funcname = $matches[2];
		$argstr   = $matches[3];

		$geoopenfunc = (FALSE !== strpos($funcname, "Geo") && FALSE !== strpos($funcname, "Open"));

		if (in_array($funcname, $ignorefuncs)){continue;}

		$argstrs = explode(",", $argstr);
		$args = array();
		foreach ($argstrs as $tmparg){
			$tmparg = trim($tmparg);
			// replace const char* with char*
			$tmparg = str_replace("const char", "char", $tmparg);
			$arg = array();
			$arg['pointer'] = (FALSE !== strpos($tmparg, "*"));
			$tmparg = str_replace("*", " ", $tmparg);
			$words = explode(" ", $tmparg);
			$tmpwords = array();
			foreach ($words as $w){
				if ($w){
					$tmpwords[] = $w;
				}
			}
			$arg['type'] = $tmpwords[0];
			$arg['name'] = $tmpwords[1];

			$args[] = $arg;
		}
		echo "void IRICLIBDLL FMNAME(", strtolower($funcname), "_f, ", strtoupper($funcname), "_F) (";
		$argstrs = array();
		$chars = array();
		$inputchars = array();
		$outputchars = array();
		$inputcgsizes = array();
		$outputcgsizes = array();

		foreach ($args as $arg){
			if ($arg['type'] == "char"){
				$chars[] = $arg['name'];
				$argstrs[] = "STR_PSTR(" . $arg['name'] . ")";
				if (
					(
						FALSE !== strpos($arg['name'], "value") && 
						FALSE == strpos($funcname, "Write")) ||
					(
						$arg['name'] == "filename" && 
						FALSE == strpos($funcname, "Open")
					)
				){
					$outputchars[] = $arg['name'];
				} else {
					$inputchars[] = $arg['name'];
				}
			} else if ($arg['type'] == "cgsize_t"){
				$argstrs[] = 'int' . " *" . $arg['name'];
				if ($arg['pointer']){
					$outputcgsizes[] = $arg['name'];
				} else {
					$inputcgsizes[] = $arg['name'];
				}
			} else {
				$argstrs[] = $arg['type'] . " *" . $arg['name'];
			}
		}
		if ($rettype == "int"){
			$argstrs[] = "int *ier";
		}
		echo implode(", ", $argstrs);

		if ($chars){
			$charlens = array();
			foreach ($chars as $c){
				$charlens[] = "STR_PLEN(" . $c . ")";
			}
			echo " ", implode(" ", $charlens);
		}

		echo ") {\n";

		// internal ier
		$ierpointer = "ier";
		$ier = "*ier";
		if ($rettype != "int" && (count($inputchars) > 0 || count($outputchars) > 0)){
			echo "\t", "int ier;\n";
			$ierpointer = "&ier";
			$ier = "ier";
		}
		// char defs
		$inputstrlen = "CGIO_MAX_NAME_LENGTH";
		if ($geoopenfunc){
			$inputstrlen = "STRINGMAXLEN";
		}
		foreach ($inputchars as $c){
			echo "\t", "char c_" . $c . "[" . $inputstrlen . "+1];\n";
		}
		foreach ($outputchars as $c){
			echo "\t", "char c_" . $c . "[STRINGMAXLEN+1];\n";
		}
		// cgsize_t defs
		foreach ($inputcgsizes as $c){
			echo "\t", "int c_" . $c . ";\n";
		}
		foreach ($outputcgsizes as $c){
			echo "\t", "cgsize_t c_" . $c . ";\n";
		}

		// input chars
		foreach  ($inputchars as $c){
			echo "\t", "string_2_C_string(STR_PTR(" . $c . "), STR_LEN(" . $c . "),\n";
			echo "\t\tc_" . $c . ", " . $inputstrlen . ", " . $ierpointer . ");\n";
			echo "\t", "if (" . $ier . ") return;\n";
		}
		// input cgsize_t
		foreach  ($inputcgsizes as $c){
			echo "\tc_", $c . " = (cgsize_t)(*" . $c . ");\n";
		}
		if ($inputchars){echo "\n";}
		echo "\t";
		if ($rettype == "int"){
			echo "*ier = ";
		}
		echo $funcname . "(";
		$argstrs = array();
		foreach ($args as $arg){
			$internalArg = "";
			if ($arg['type'] == 'cgsize_t'){
				if ($arg['pointer']){
					$internalArg = "&";
				} else {
					$internalArg = "";
				}
			} else if (! $arg['pointer']){
				$internalArg = "*";
			}
			if ($arg['type'] == "char"){
				$internalArg .= "c_";
			} else if ($arg['type'] == "cgsize_t"){
				$internalArg .= "c_";
			}
			$internalArg .= $arg['name'];
			$argstrs[] = $internalArg;
		}
		echo implode(", ", $argstrs);
		echo ");\n";

		// output chars
		if ($outputchars){echo "\n";}
		foreach  ($outputchars as $c){
			echo "\tif (" . $ier . ") return;\n";
			echo "\t", "string_2_F_string(c_" . $c . ", STR_PTR(" . $c . "), STR_LEN(" . $c . "), " . $ierpointer . ");\n";
		}
		// output cgsize_t
		if ($outputcgsizes){echo "\n";}
		foreach  ($outputcgsizes as $c){
			echo "\t*", $c . " = (int)(c_" . $c . ");\n";
		}

		echo "}\n";
		echo "\n";
	}
}
fclose($fp);
?>
