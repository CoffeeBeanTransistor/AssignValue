#include "TextParser.h"
#include <ctype.h>
#include <stdio.h>
#include <malloc.h>
#include "Exception.h"

int parseAndCompare(char **linePtr, char *cmpStr) {

  int step = 0;

  while ((*cmpStr) == ' ') {    //Remove leading spaces
    cmpStr++;
  }

  while ((**linePtr) == ' ') {  //Remove leading spaces
    (*linePtr)++;
    step++;
  }

  if((**linePtr) == '\0')   //Return 1 if linePtr contains no command
    return 1;

  if((*cmpStr) == '=' && (**linePtr) == '=') {    //Return 1 when linePtr contains '='
    (*linePtr)++;
    return 1;
  }

  while((*cmpStr) == (**linePtr)) {     //Compares 2 strings
    if((*cmpStr) =='\0'|| (**linePtr) =='\0')
      break;
    cmpStr++;
    (*linePtr)++;
    step++;
  }

  while ((*cmpStr) == ' ') {    //Remove trailing spaces of cmpStr
    cmpStr++;
  }

  if((**linePtr) == ' ' && (*cmpStr) == '\0') {   //Continue to parse next word if
    while ((**linePtr) == ' ') {                  //linePtr has not reach '\0'
      (*linePtr)++;                               //and finished compare
    }
    return 1;
  }

  else if((**linePtr) == '\0' && (*cmpStr) == '\0')  //Return 1 if both strings
    return 1;                                        //reaches the end

  else if((**linePtr) == '=' && (*cmpStr) == '\0')   //Return 1 when linePtr reaches '='
    return 1;                                        //and finished compare

  else {
    (*linePtr) -= step;   //Revert step of linePtr and return 0 if none
    return 0;             //of the above trigger
  }
}


int parseAndConvertToNum(char **linePtr) {

  int step = 0, result = 0;

  while((**linePtr) == ' ') {   //Remove leading spaces
    (*linePtr)++;
    step++;
  }

  if(verifyNumOnlyString (linePtr)) {   //Check string only contains number
    while((**linePtr) != ' ' && (**linePtr) != '\0') {    //Conversion of string to int
      result += ((**linePtr) - 48);                       //using substraction of ASCII
      result *= 10;
      (*linePtr)++;
      step++;
    }

    while((**linePtr) == ' ') {   //Remove trailing spaces
      (*linePtr)++;
      step++;
    }

    result /= 10;
    return result;
    }

  else
    return 0; //ERR_NOT_A_NUMBER
}


int verifyNumOnlyString (char **linePtr) {

  int step = 0;

  while ((**linePtr) == ' ') {  //Remove leading spaces
    (*linePtr)++;
    step++;
  }

  while ((**linePtr) != ' ' && (**linePtr) != '\0') {   //Checks linePtr until ' ' or '\0'
      if (isdigit((**linePtr)) == 0) {
        (*linePtr) -= step;
        throwSimpleError(1,"ERR_NOT_A_NUMBER"); //Throw not a number error when element is not a digit
      }
      else {
        (*linePtr)++;
        step ++;
      }
  }
  (*linePtr) -= step;   //Revert back and return 1 when it is done
  return 1;
}


int parseTextAndAssignValues(char **linePtr, VariableMapping varTableMapping[]) {

  int i = 0;

  if(*linePtr == NULL) {   //Return 1 if the command is NULL
    return 1;
  }

  if(varTableMapping == NULL) {   //Throw table error when there is no table given
    throwSimpleError(5,"ERR_TABLE_IS_MISSING");
  }

  else {
    if(parseAndCompare(linePtr, "assign")) {    //Check if linePtr contains "assign"
      while((**linePtr) != '\0') {
        if(varTableMapping[i].name == NULL) {          //Throw unknown variable error if
          throwSimpleError(2,"ERR_UNKNOWN_VARIABLE");  //found unmatched var
        }
        else {
          if(parseAndCompare(linePtr, varTableMapping[i].name)) {   //Checks for every var name in table
            if(parseAndCompare(linePtr,"=")) {    //Checks for the presence of '=' sign
              *varTableMapping[i].storage = parseAndConvertToNum(linePtr);    //Convert string num and return back
              i = 0;    //Reset back when found its corresponding var         //int and store to its storage
            }
            else
              throwSimpleError(4,"ERR_MALFORM_ASSIGN");   //If no "=" is found, throw malform error
          }
          else
            i++;  //Increase index when the var is not matched from table
        }
      }
    }

    else
      throwSimpleError(3,"ERR_UNKNOWN_COMMAND");    //If no "assign" word is found, throw unknown command
  }                                                 //error
}
