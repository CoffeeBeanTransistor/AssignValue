#ifndef _ERROR_H
#define _ERROR_H

typedef enum {
  NO_ERROR,
  ERR_NOT_A_NUMBER,
  ERR_UNKNOWN_VARIABLE,
  ERR_UNKNOWN_COMMAND,
  ERR_MALFORM_ASSIGN,
  ERR_TABLE_IS_MISSING,
  ERR_TABLE_IS_EMPTY,
} ErrorCode;

#endif // _ERROR_H
