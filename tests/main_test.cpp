#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#ifndef DOCTEST_CONFIG_NO_MULTITHREADING
#define DOCTEST_CONFIG_NO_MULTITHREADING
#endif
#define DOCTEST_CONFIG_COLORS_NONE

#include <io.h>
#include <ctime>

#if defined(__MINGW32__) && !defined(__MINGW64__)
#ifndef _fileno
#define _fileno fileno
#endif
#ifndef _isatty
#define _isatty isatty
#endif
inline struct tm* gmtime_s_compat(struct tm* _tm, const time_t* _time) {
    struct tm* res = gmtime(_time);
    if (res && _tm) {
        *_tm = *res;
        return _tm;
    }
    return nullptr;
}
#define gmtime_s(tm_ptr, time_ptr) gmtime_s_compat(tm_ptr, time_ptr)
#endif

#include "doctest.h"

