#define CG_MODE_READ	0
#define CG_MODE_WRITE	1
#define CG_MODE_MODIFY  2

#define CG_OK 0

#ifndef CGNSDLL
# ifdef _WIN32
#  if defined(CGNSLIBDLL_LIBRARY)
#    define CGNSDLL _declspec(dllexport)
#  else
#    define CGNSDLL _declspec(dllimport)
#  endif
# else
#  define CGNSDLL
# endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

CGNSDLL int cg_open(const char * filename, int mode, int *fn);
CGNSDLL int cg_close(int fn);

#ifdef __cplusplus
}
#endif
