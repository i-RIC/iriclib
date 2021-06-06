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

CGNSDLL int cg_close(int fn);

#ifdef __cplusplus
}
#endif
