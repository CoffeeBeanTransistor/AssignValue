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
    return 0;
}

int verifyNumOnlyString (char **linePtr) {

  int step = 0;
  char *errvarname;

  while ((**linePtr) == ' ') {  //Remove leading spaces
    (*linePtr)++;
    step++;
  }

  while ((**linePtr) != ' ' && (**linePtr) != '\0') {   //Checks linePtr until ' ' or '\0'
      if (isdigit((**linePtr)) == 0) {
        (*linePtr) -= step;
        errvarname = extractVariable(linePtr);
        throwError(1,"ERROR %d: '%s' is not a number!",1,(errvarname)); //Throw not a number error when element is not a digit
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
  char *errvarname;

  if(*linePtr == NULL) {   //Return 1 if the command is NULL
    return 1;
  }

  if(varTableMapping == NULL) {   //Throw table error when there is no table given
    simpleThrowError(5,"ERROR 5: Table is missing!");
  }

  if(varTableMapping[i].name == 0) {   //Throw table error when there is no table given
    simpleThrowError(6,"ERROR 6: Table is empty!");
  }

  else {
    if(parseAndCompare(linePtr, "assign")) {    //Check if linePtr contains "assign"
      while((**linePtr) != '\0') {
        if(varTableMapping[i].name == NULL) {          //Throw unknown variable error if
          errvarname = extractVariable(linePtr);      //found unmatched var
          throwError(2,"ERROR %d: '%s' is not a valid variable.",2,(errvarname));
        }
        else {
          if(parseAndCompare(linePtr, varTableMapping[i].name)) {   //Checks for every var name in table
            if(parseAndCompare(linePtr,"=")) {    //Checks for the presence of '=' sign
              *varTableMapping[i].storage = parseAndConvertToNum(linePtr);    //Convert string num and return back
              i = 0;    //Reset back when found its corresponding var         //int and store to its storage
            }
            else {
              errvarname = extractVariable(linePtr);   //If no "=" is found, throw malform error
              throwError(4,"ERROR %d: Expected '=', but %s is encountered.",4,(errvarname));
            }
          }
          else
            i++;  //Increase index when the var is not matched from table
        }
      }
    }
    else{
      errvarname = extractVariable(linePtr);  //If no "assign" word is found, throw unknown command
      throwError(3,"ERROR %d: Expected 'assign', but %s is encounted from the beginning.",3, (errvarname));
    }
  }
}

char *extractVariable(char **linePtr) {

  int length = 0, i = 0;
  char *extracted_var_name;

  while ((**linePtr) == ' ') {  //Remove leading spaces
    (*linePtr)++;
  }

  length = getVariableLength(linePtr);
  extracted_var_name = malloc (length);

  while (i < length) {
    extracted_var_name[i] = (**linePtr);
    (*linePtr)++;
    i++;
  }

  extracted_var_name[i] = '\0'; //End string

  return extracted_var_name;
}

int getVariableLength (char **linePtr) {

  	int counter = 0;

    if((**linePtr) == '=') {
      counter =+ 1;
    }
    else {
	    while ((**linePtr) != ' ' && (**linePtr) != '=') {
        if((**linePtr) == '\0') {
          (*linePtr) -= counter;
      		return counter;
        }
        else
			    counter++;
          (*linePtr)++;
			}
    (*linePtr) -= counter;  //Return original linePtr address
    }

		return counter;
	}
