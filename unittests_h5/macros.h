#include <stdio.h>

#define VERIFY_LOG(msg, result) printf("%s %d: %s ", __FILE__, __LINE__, msg);if(result){printf("[OK]\n");}else{printf("[NG]\n");}

#define VERIFY_REMOVE(fn, hdf) printf("%s %d: remove(\"%s\") -- %s ier == 0 ", __FILE__, __LINE__, fn, hdf ? "HDF" : "ADF");if(remove(fn) == 0){printf("[OK]\n");}else{printf("[NG]\n");}
