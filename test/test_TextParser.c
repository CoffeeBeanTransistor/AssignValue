#include "unity.h"
#include "CException.h"
#include "TextParser.h"
#include <stdio.h>
#include "Error.h"
#include "Exception.h"


void setUp(void) {}

void tearDown(void) {}

void test_parseAndCompare_given_assign_should_return_true(void)
{
  char *line ="assign";
  char *originalLine = line;

  TEST_ASSERT_TRUE (parseAndCompare(&line,"assign"));
  TEST_ASSERT_EQUAL_PTR (originalLine + 6, line);
}

void test_parseAndCompare_given_ass_and_spaced_assign_should_return_false(void)
{
  char *line ="ass";
  char *originalLine = line;

  TEST_ASSERT_FALSE (parseAndCompare(&line," assign"));
  TEST_ASSERT_EQUAL_PTR (originalLine, line);
}

void test_parseAndCompare_given_spaced_assign_should_return_true(void)
{
  char *line =" assign";
  char *originalLine = line;

  TEST_ASSERT_TRUE (parseAndCompare(&line,"assign"));
  TEST_ASSERT_EQUAL_PTR (originalLine + 7, line);
}

void test_parseAndCompare_given_assign_and_ass_should_return_false(void)
{
  char *line ="assign";
  char *originalLine = line;

  TEST_ASSERT_FALSE (parseAndCompare(&line,"ass"));
  TEST_ASSERT_EQUAL_PTR (originalLine, line);
}

void test_parseAndCompare_given_assign_with_extra_trailing_space_should_return_true(void)
{
  char *line ="assign   ";
  char *originalLine = line;


  TEST_ASSERT_TRUE (parseAndCompare(&line,"assign "));
  TEST_ASSERT_EQUAL_PTR (originalLine + 9, line);
}

void test_parseAndCompare_given_spaced_assign_and_assign_with_spaced_and_extra_trailing_space_should_return_true(void)
{
  char *line ="   assign";
  char *originalLine = line;

  TEST_ASSERT_TRUE (parseAndCompare(&line," assign "));
  TEST_ASSERT_EQUAL_PTR (originalLine + 9, line);
}

void test_parseAndConvertToNum_given_string_213_expect_return_number_213 (void){
  char *line = "213";
  char *originalLine = line;


  int v = parseAndConvertToNum (&line);
  TEST_ASSERT_EQUAL (213,v);
  TEST_ASSERT_EQUAL_PTR (originalLine + 3, line);
}

void test_parseAndConvertToNum_given_string_456_with_trailing_space_expect_return_number_456 (void){
  char *line = "456 ";
  char *originalLine = line;

  int v = parseAndConvertToNum (&line);
  TEST_ASSERT_EQUAL (456,v);
  TEST_ASSERT_EQUAL_PTR (originalLine + 4, line);
}

void test_parseAndConvertToNum_given_leading_and_traiing_space_string_978_expect_return_number_978 (void){
  char *line = "   978   ";
  char *originalLine = line;

  int v = parseAndConvertToNum (&line);
  TEST_ASSERT_EQUAL (978,v);
  TEST_ASSERT_EQUAL_PTR (originalLine + 9, line);
}


void test_verifyNumOnlyString_given_423_expect_true () {
  char *line = "423";
  char *originalLine = line;

  TEST_ASSERT_TRUE (verifyNumOnlyString(&line));
  TEST_ASSERT_EQUAL_PTR (originalLine, line);
}

void test_verifyNumOnlyString_given_849_with_leading_and_traiing_spaces_expect_return_true () {
  char *line = "   849      ";
  char *originalLine = line;

  TEST_ASSERT_TRUE (verifyNumOnlyString(&line));
  TEST_ASSERT_EQUAL_PTR (originalLine, line);
}

void test_verifyNumOnlyString_given_2l0_expect_false () {
  CEXCEPTION_T e;
  char *line = "2l0";
  char *originalLine = line;

  Try{
    verifyNumOnlyString(&line);
    TEST_FAIL_MESSAGE("Expect ERR_NOT_A_NUMBER. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_NOT_A_NUMBER, e->errorCode);
    freeError(e);
  }
}

void test_verifyNumOnlyString_given_53e7_with_trailing_and_leading_spaces_expect_false () {
  CEXCEPTION_T e;
  char *line = "   53e7  ";
  char *originalLine = line;

  Try{
    verifyNumOnlyString(&line);
    TEST_FAIL_MESSAGE("Expect ERR_NOT_A_NUMBER. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_NOT_A_NUMBER, e->errorCode);
    freeError(e);
  }
}


void test_parseTextAndAssignValues_given_orange_21346_apple_1_lemon_10_should_assign_correctly(void)
{
  CEXCEPTION_T e;
  int orange = 0, apple = 0, lemon = 0;
  VariableMapping varTableMapping[] = {
    {"apple",&apple},
    {"orange",&orange},
    {"lemon",&lemon},
    {NULL, NULL},
  };
  char *line ="assign orange  = 21346 apple = 1 lemon=10";
  Try {
    parseTextAndAssignValues(&line, varTableMapping);

    TEST_ASSERT_EQUAL(21346,orange);
    TEST_ASSERT_EQUAL(1,apple);
    TEST_ASSERT_EQUAL(10,lemon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_strawberry_9385_lime_632_mangoesteen_7493_should_assign_correctly(void)
{
  CEXCEPTION_T e;
  int lime = 0, strawberry = 0, mangoesteen = 0;
  VariableMapping varTableMapping[] = {
    {"mangoesteen",&mangoesteen},
    {"lime",&lime},
    {"strawberry",&strawberry},
    {NULL, NULL},
  };
  char *line ="assign strawberry=9385 lime=632 mangoesteen=7493";
  Try {
    parseTextAndAssignValues(&line, varTableMapping);

    TEST_ASSERT_EQUAL(9385,strawberry);
    TEST_ASSERT_EQUAL(7493,mangoesteen);
    TEST_ASSERT_EQUAL(632,lime);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_text_without_assign_should_throw_ERR_UNKNOWN_COMMAND(void) {
  CEXCEPTION_T e;
  int papaya = 0;
  VariableMapping varTableMapping[] = {
    {"papaya", &papaya},
    {NULL, NULL},
  };
  char *line = "  papaya = 345 ";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_COMMAND. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_COMMAND, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_no_table_mapping_should_throw_ERR_TABLE_IS_MISSING(void) {
  CEXCEPTION_T e;
  char *line = " assign mango = 589 ";

  Try {
    parseTextAndAssignValues(&line, NULL);
    TEST_FAIL_MESSAGE("Expect ERR_TABLE_IS_MISSING. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_TABLE_IS_MISSING, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_no_command_should_do_nothing(void) {
  CEXCEPTION_T e;
  int tomato = 0;
  VariableMapping varTableMapping[] = {
    {"tomato", &tomato},
    {NULL, NULL},
  };
  char *line = NULL;

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    // Should reach here because no command given
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_input_command_is_NULL_should_do_nothing(void) {
  CEXCEPTION_T e;
  int kiwi = 0;
  VariableMapping varTableMapping[] = {
    {"kiwi", &kiwi},
    {NULL, NULL},
  };
  char *line = "  ";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    // Should reach here because no command given
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_melon_and_value_with_trailing_spaces_should_parse_properly(void) {
  CEXCEPTION_T e;
  int melon = 0;
  VariableMapping varTableMapping[] = {
    {"melon  ", &melon},
    {NULL, NULL},
  };
  char *line = "assign melon = 89   ";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_ASSERT_EQUAL(89, melon);
  } Catch(e) {
    printf(e->errorMsg);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_guava_23_cucumber_92_should_throw_ERR_UNKNOWN_VARIABLE(void) {
  CEXCEPTION_T e;
  int guava = 0;
  VariableMapping varTableMapping[] = {
    {"guava", &guava},
    {NULL, NULL},
  };
  char *line = "assign guava=23 cucumber=92";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_VARIABLE. But no exception thrown.");
  } Catch(e) {
    TEST_ASSERT_EQUAL(23, guava);
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_VARIABLE, e->errorCode);
    freeError(e);
  }
}


void test_parseTextAndAssignValues_given_malform_pineapple_without_equal_sign_should_throw_ERR_MALFORM_ASSIGN(void) {
  CEXCEPTION_T e;
  int pineapple = 0;
  VariableMapping varTableMapping[] = {
    {"pineapple", &pineapple},
    {NULL, NULL},
  };
  char *line = "assign pineapple 23 ";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_MALFORM_ASSIGN. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_MALFORM_ASSIGN, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_malform_ciku_without_number_should_throw_ERR_NOT_A_NUMBER(void) {
  CEXCEPTION_T e;
  int ciku = 0;
  VariableMapping varTableMapping[] = {
    {"ciku", &ciku},
    {NULL, NULL},
  };
  char *line = "assign ciku =  durian = 6";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_NOT_A_NUMBER. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_NOT_A_NUMBER, e->errorCode);
    freeError(e);
  }
}

void test_parseTextAndAssignValues_given_missing_variable_and_mandarin_123_expect_ERR_UNKNOWN_VARIABLE(void) {
  CEXCEPTION_T e;
  int mandarin = 0, banana = 0;
  VariableMapping varTableMapping[] = {
    {"banana", &banana},
    {"mandarin", &mandarin},
    {NULL, NULL},
  };
  char *line = "assign = 53 mandarin= 123";

  Try {
    parseTextAndAssignValues(&line, varTableMapping);
    TEST_FAIL_MESSAGE("Expect ERR_UNKNOWN_VARIABLE. But no exception thrown.");
  } Catch(e) {
    printf(e->errorMsg);
    TEST_ASSERT_EQUAL(ERR_UNKNOWN_VARIABLE, e->errorCode);
    freeError(e);
  }
}
