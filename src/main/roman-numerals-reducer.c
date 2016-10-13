#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common-utils.h"
#include "roman-numerals-expander.h"
#include "constants.h"

static int shouldContinue(const char currentReduceByCharacter, const int loop);
static void makeResult(const char *partialResult, const int loop, char result[]);
static void removeCommonNumerals(const char *romanNumeralsCopy, const char currentReduceByCharacter, char *partialResult);
static int containsReduceBy(const char *romanNumeralsCopy, const char currentReduceByCharacter);
static int MAX_LOOP = 30;

void reduceMatchingNumerals(const char *romanNumerals, const char *reduceByRomanNumerals, char result[]){
  char partialResult[BUFFER_SIZE] = {};
  char romanNumeralsCopy[BUFFER_SIZE] = {};
  strcpy(romanNumeralsCopy, romanNumerals);

  int index = 0;
  int loop = 0;
  while(shouldContinue(reduceByRomanNumerals[index], loop)) {
    char currentReduceByCharacter = reduceByRomanNumerals[index];
    partialResult[0] = '\0';

    if(containsReduceBy(romanNumeralsCopy, currentReduceByCharacter)){
      removeCommonNumerals(romanNumeralsCopy,  currentReduceByCharacter, partialResult);
      index++;
    }
    else{
      expandNumerals(romanNumeralsCopy, currentReduceByCharacter, partialResult);
    }

    loop++;
    strcpy(romanNumeralsCopy, partialResult);
  }

  makeResult(partialResult, loop, result);
}

static int shouldContinue(const char currentReduceByCharacter, const int loop){
  return currentReduceByCharacter != '\0' && loop < MAX_LOOP;
}

static int containsReduceBy(const char *romanNumeralsCopy, const char currentReduceByCharacter){
  char currentReduceByCharacterString[2] = {};
  currentReduceByCharacterString[0] = currentReduceByCharacter;

  return strstr(romanNumeralsCopy, currentReduceByCharacterString) != NULL ? 1 : 0;
}

static void removeCommonNumerals(const char *romanNumeralsCopy, const char currentReduceByCharacter, char *partialResult){
  char currentReduceByCharacterString[2] = {};
  currentReduceByCharacterString[0] = currentReduceByCharacter;

  replaceSubstring(romanNumeralsCopy,  currentReduceByCharacterString, "", partialResult);
}

static void makeResult(const char *partialResult, const int loop, char result[]){
  if(loop >= MAX_LOOP){
    strcat(result, "REDUCER FAILED");
  }else{
    strcat(result, partialResult);
  }
}
