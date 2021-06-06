#include "cases.h"

#include <iostream>

int main(int argc, char* argv[])
{
	case_InitSuccess();
	case_InitReadSuccess();

	case_InitOptionCheck();

	case_CheckCancel();

	case_CalcCondRead();
	case_CalcCondWrite();

	case_BcRead();
	case_BcWrite();

	case_Complex();

	case_GridRead();
	case_GridReadUnstructured();
	case_GridReadFunc();
	case_GridWrite();

	// case_SolWriteStd_adf();
	// case_SolWriteDivide_adf();

	case_SolWriteStd_hdf5();
	case_SolWriteDivide_hdf5();

	case_addGridAndResult();

	// case_read_adf();
	case_read_hdf5();

	// case_read_adf_no_results();
	case_read_hdf5_no_results();

	case_noGridOutput();

	return 0;
}
