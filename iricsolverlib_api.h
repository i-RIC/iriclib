#ifndef IRICSOLVERLIB_API
# ifdef _WIN32
#  if defined(IRICSOLVERLIBSTATIC_LIBRARY)
#   define IRICSOLVERLIB_API
#  else
#   if defined(IRICSOLVERLIBDLL_LIBRARY)
#    define IRICSOLVERLIB_API __declspec(dllexport)
#   else
#    define IRICSOLVERLIB_API __declspec(dllimport)
#   endif
#  endif
# else
#  define IRICSOLVERLIB_API
# endif
#endif

