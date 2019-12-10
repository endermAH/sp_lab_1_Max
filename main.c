#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

const char *optString = "h";

char *outputString = NULL;
char *envVariable = NULL;
int endOfOutputString = 0;
int endOfENVVariable = 0;

struct globalArgs_t {
  char* inputPath;
  char* outputPath;
  FILE* inputFile;
  FILE* outputFile;
} globalArgs;

void addCharToOutput(char target_char) {
  endOfOutputString++;
  outputString = realloc(outputString, endOfOutputString * sizeof(char));
  outputString[endOfOutputString-1] = target_char;
}

void addCharToENVVar(char target_char) {
  endOfENVVariable++;
  envVariable = realloc(envVariable, endOfENVVariable * sizeof(char));
  envVariable[endOfENVVariable-1] = target_char;
  envVariable[endOfENVVariable] = '\0';
}

void addENVToOUTPUT() {
  char *envpointer;
  int envValLen;
  int envNameLen;
  if (getenv(envVariable)) {
    envpointer = getenv(envVariable);
    envValLen = strlen(envpointer);
    for (int i = 0; i < envValLen; i++) {
      addCharToOutput(envpointer[i]);
    }
    envVariable = NULL;
    endOfENVVariable = 0;
  } else {
    addCharToOutput('$');
    for (int i = 0; i < endOfENVVariable; i++) {
      addCharToOutput(envVariable[i]);
    }
    envVariable = NULL;
    endOfENVVariable = 0;
  }
}

void startJob() {
  short int state = 0; // 0 - 