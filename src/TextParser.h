#ifndef _TEXTPARSER_H
#define _TEXTPARSER_H

typedef struct VariableMapping VariableMapping;
struct VariableMapping {
  char *name;
  int  *storage;
};

/**
  *Parse and compare strings. It ignores all spaces. If
  *the strings are equal, it returns non-zero, otherwise
  *zero value.
  **/
int parseAndCompare(char **linePtr, char *cmpStr);


/**
  *Parse and convert the first string number to value.
  *It ignores all spaces.The value is returned if the
  *number is successfully converted. If there is no
  *number, ERR_NOT_A_NUMBER is thrown.
  **/
int parseAndConvertToNum(char **linePtr);

int verifyNumOnlyString (char **linePtr);

int parseTextAndAssignValues(char **linePtr, VariableMapping varTableMapping[]);

char *extractVariable(char **linePtr);

int getVariableLength (char **linePtr);

#endif // _TEXTPARSER_H
