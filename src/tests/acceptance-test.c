#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../main/calculator.h"
#include "test-constants.h"

static const char *getfield(char* line, int num);
static void assertAdd(char *firstNumeral, char *secondNumeral, char *expected);
static void assertSubtract(char *firstNumeral, char *secondNumeral, char *expected);
static FILE *openFileStreamAdd();
static FILE *openFileStreamSubtract();

START_TEST(testAddAcceptance)
{
  char line[TEST_BUFFER_SIZE] = {'\0'};
  char lineCopy[TEST_BUFFER_SIZE] = {'\0'};
  char firstNumeral[TEST_BUFFER_SIZE] = {'\0'};
  char secondNumeral[TEST_BUFFER_SIZE] = {'\0'};
  char expectedNumeral[TEST_BUFFER_SIZE] = {'\0'};

  FILE *stream = openFileStreamAdd();
  int addAsserts = 0;
  while (fgets(line, TEST_BUFFER_SIZE, stream))
  {
      firstNumeral[0] = '\0';
      secondNumeral[0] = '\0';
      expectedNumeral[0] = '\0';
      lineCopy[0] = '\0';

      strcat(lineCopy,line);
      strcat(firstNumeral, getfield(lineCopy, 1));

      strcat(lineCopy,line);
      strcat(secondNumeral, getfield(lineCopy, 2));

      strcat(lineCopy,line);
      strcat(expectedNumeral, getfield(lineCopy, 3));

      assertAdd(firstNumeral, secondNumeral, expectedNumeral);
      addAsserts++;
  }
   ck_assert_int_eq(addAsserts, 3000);
   printf(" Add Asserts: %d\n", addAsserts);
   fclose(stream);
}
END_TEST

START_TEST(testSubtractAcceptance)
{
  char line[TEST_BUFFER_SIZE] = {'\0'};
  char lineCopy[TEST_BUFFER_SIZE] = {'\0'};
  char firstNumeral[TEST_BUFFER_SIZE] = {'\0'};
  char secondNumeral[TEST_BUFFER_SIZE] = {'\0'};
  char expectedNumeral[TEST_BUFFER_SIZE] = {'\0'};
  FILE *stream = openFileStreamSubtract();

  int subtractAsserts = 0;
  while (fgets(line, TEST_BUFFER_SIZE, stream))
  {
      firstNumeral[0] = '\0';
      secondNumeral[0] = '\0';
      expectedNumeral[0] = '\0';
      lineCopy[0] = '\0';

      strcat(lineCopy,line);
      strcat(firstNumeral, getfield(lineCopy, 1));

      strcat(lineCopy,line);
      strcat(secondNumeral, getfield(lineCopy, 2));

      strcat(lineCopy,line);
      strcat(expectedNumeral, getfield(lineCopy, 3));

      assertSubtract(firstNumeral, secondNumeral, expectedNumeral);
      subtractAsserts++;
  }
   ck_assert_int_eq(subtractAsserts, 2000);
   printf(" Subtract Asserts: %d\n", subtractAsserts);
   fclose(stream);
}
END_TEST

static void assertAdd(char *firstNumeral, char *secondNumeral, char *expectedNumeral){
  char result[TEST_BUFFER_SIZE] = {'\0'};
  expectedNumeral[strlen(expectedNumeral)-1] = '\0';
  add(firstNumeral, secondNumeral, result, TEST_BUFFER_SIZE);

  ck_assert_str_eq(result, expectedNumeral);
}

static void assertSubtract(char *firstNumeral, char *secondNumeral, char *expectedNumeral){
  char result[TEST_BUFFER_SIZE] = {'\0'};
  expectedNumeral[strlen(expectedNumeral)-1] = '\0';

  subtract(firstNumeral,secondNumeral, result, TEST_BUFFER_SIZE);

  ck_assert_str_eq(result, expectedNumeral);
}

static FILE *openFileStreamAdd(){
  return fopen("src/tests/acceptance-test-data-add", "r");
}

static FILE *openFileStreamSubtract(){
  return fopen("src/tests/acceptance-test-data-subtract", "r");
}

static const char *getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok != NULL;
            tok = strtok(NULL, ","))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

Suite * makeAcceptanceSuite(void)
{
    Suite *s;
    TCase *tcCore;

    s = suite_create("Acceptance Suite");
    tcCore = tcase_create("Core");

    tcase_add_test(tcCore, testAddAcceptance);
    tcase_add_test(tcCore, testSubtractAcceptance);
    suite_add_tcase(s, tcCore);

    return s;
}
