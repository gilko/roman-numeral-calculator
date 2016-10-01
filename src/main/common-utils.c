#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *concatenateReplaceSubstring(char *beforeSubstring, char *replaceWithString, char *afterSubstring, char result[]);
static char *makeBeforeSubstring(const char *inputStringCopy, char *subString, char *beforeSubstring);
static char *makeAfterSubstring(const char *inputStringCopy, char *subString, char *afterSubstring);
static int *doesNotContainSubstring(const char *inputString, const char *subString);
static void doReplace(char *inputString, char *subString, char *replaceWithString, char result[]);

void replaceSubstring(char *inputString, char *subString, char *replaceWithString, char result[])
{
  if(doesNotContainSubstring(inputString,subString)){
    strcat(result, inputString);
  }else{
    doReplace(inputString, subString, replaceWithString, result);
  }
}

char *concatenate(char* romanNumeral1, char* romanNumeral2)
{
  char *result = calloc(1000, sizeof(char));

  strcat(result, romanNumeral1);
  strcat(result, romanNumeral2);

  return result;
}

static void doReplace(char *inputString, char *subString, char *replaceWithString, char result[]){
  char inputStringCopy[200] = {'\0'};
  strcpy(inputStringCopy, inputString);

  char beforeSubstring[200] = {'\0'};
  makeBeforeSubstring(inputStringCopy, subString,beforeSubstring);

  char afterSubstring[200] = {'\0'};
  makeAfterSubstring(inputStringCopy, subString, afterSubstring);

  concatenateReplaceSubstring(beforeSubstring, replaceWithString, afterSubstring, result);
}

static char *makeAfterSubstring(const char *inputStringCopy, char *subString, char *afterSubstring){
  char *startOfSubstring = strstr(inputStringCopy, subString);
  char *endOfSubstring = startOfSubstring + strlen(subString);

  strcpy(afterSubstring, endOfSubstring);

  return afterSubstring;
}

static char *makeBeforeSubstring(const char *inputStringCopy, char *subString, char *beforeSubstring){
  char *startOfSubstring = strstr(inputStringCopy, subString);
  strncpy(beforeSubstring, inputStringCopy, startOfSubstring - inputStringCopy);

  return beforeSubstring;
}

static char *concatenateReplaceSubstring(char *beforeSubstring, char *replaceWithString, char *afterSubstring, char result[]){
  strcat(result, beforeSubstring);
  strcat(result, replaceWithString);
  strcat(result, afterSubstring);
  return result;
}

static int *doesNotContainSubstring(const char *inputString, const char *subString){
  return strstr(inputString, subString) == NULL;
}
