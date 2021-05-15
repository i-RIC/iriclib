extern "C" {

void case_InitSuccess();
void case_InitFail();
void case_gotoRawDataTop();
void case_InitReadSuccess();
void case_InitReadFail();
void case_InitOptionCheck();
void case_InitCC();

void case_CheckLock();
void case_CheckCancel();

void case_CalcCondRead();
void case_CalcCondWrite();

void case_BcRead();
void case_BcWrite();

void case_Complex();

void case_GridRead();
void case_GridReadUnstructured();
void case_GridReadFunc();
void case_GridWrite();

void case_SolStartEnd();

void case_SolWriteStd_adf();
void case_SolWriteStd_hdf5();
void case_SolWriteDivide_adf();
void case_SolWriteDivide_hdf5();

void case_addGridAndResult();

void case_read_adf();
void case_read_adf_no_results();

void case_read_hdf5();
void case_read_hdf5_no_results();

void case_noGridOutput();

} // extern "C"
