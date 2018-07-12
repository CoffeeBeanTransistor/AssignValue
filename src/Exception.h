#ifndef _EXCEPTION_H
#define _EXCEPTION_H
#include <Exception.h>

typedef struct Exception Exception; //Works for C++ and C
struct Exception{
  int errorCode;
  char *errorMsg;
};

void simpleThrowError(int errorCode, char* errorMsg);
void throwError(int errorCode, char *format, ... );
void freeError (Exception *ex);

#endif // _EXCEPTION_H
