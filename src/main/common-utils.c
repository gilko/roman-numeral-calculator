#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *concatenateReplaceSubstring(char *beforeSubstring, char *replaceWithString, char *afterSubstring, char *result);
static char *makeBeforeSubstring(const char *copyOfInput, char *substring, char *beforeSubstring);
static char *makeAfterSubstring(const char *copyOfInput, char *substring, char *afterSubstring);
static int *doesNotContainSubstring(const char *inputString, const char *substring);
static char *doReplace(char *inputString, char *substring, char *replaceWithString, char *result);

char *replaceSubstring(char *inputString, char *substring, char *replaceWithString)
{
  char *result = calloc(1000, sizeof(char));

  if(doesNotContainSubstring(inputString,substring)){
    strcat(result, inputString);
    return result;
  }

  return doReplace(inputString, substring, replaceWithString, result);
}

char *concatenate(char* romanNumeral1, char* romanNumeral2)
{
  char *result = calloc(1000, sizeof(char));

  strcat(result, romanNumeral1);
  strcat(result, romanNumeral2);

  return result;
}

static char *doReplace(char *inputString, char *substring, char *replaceWithString, char *result){
  char copyOfInput[200] = {'\0'};
  strcpy(copyOfInput, inputString);

  char beforeSubstring[200] = {'\0'};
  makeBeforeSubstring(copyOfInput, substring,beforeSubstring);

  char afterSubstring[200] = {'\0'};
  makeAfterSubstring(copyOfInput, substring, afterSubstring);

  return concatenateReplaceSubstring(beforeSubstring, replaceWithString, afterSubstring, result);
}

static char *makeAfterSubstring(const char *copyOfInput, char *substring, char *afterSubstring){
  char *startOfSubstring = strstr(copyOfInput, substring);
  char *endOfSubstring = startOfSubstring + strlen(substring);

  strcpy(afterSubstring, endOfSubstring);

  return afterSubstring;
}

static char *makeBeforeSubstring(const char *copyOfInput, char *substring, char *beforeSubstring){
  char *startOfSubstring = strstr(copyOfInput, substring);
  strncpy(beforeSubstring, copyOfInput, startOfSubstring - copyOfInput);

  return beforeSubstring;
}

static char *concatenateReplaceSubstring(char *beforeSubstring, char *replaceWithString, char *afterSubstring, char *result){
  strcat(result, beforeSubstring);
  strcat(result, replaceWithString);
  strcat(result, afterSubstring);
  return result;
}

static int *doesNotContainSubstring(const char *inputString, const char *substring){
  return strstr(inputString, substring) == NULL;
}
