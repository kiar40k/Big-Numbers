#include "pch.h"

INT64 inputInt64(const TCHAR *format,...) {
  for(;;) {
    va_list argptr;
    va_start(argptr,format);
    _vtprintf(format, argptr);
    va_end(argptr);
    TCHAR line[100];
    GETS(line);
    INT64 d;
    if(_stscanf(line,_T("%lld"),&d) == 1) {
      return d;
    }
  }
}
