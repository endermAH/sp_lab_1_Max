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
  short int state = 0;
  char inChar;

  while (!feof(globalArgs.inputFile)){
    fscanf(globalArgs.inputFile,"%c",&inChar);
    if (inChar == '$' && state != 1) {
      state = 1;
      continue;
    } else if ((inChar == ' ' || inChar == '\n' || inChar == '\0') && (state == 1)) {
      state = 2;
    }
    if (state == 1) {
      addCharToENVVar(inChar);
    } else if (state == 2) {
      addENVToOUTPUT();
      state = 0;
    }
    if (state == 0) {
      addCharToOutput(inChar);
    }
  }
}

void display_usage(char* name) {
  printf("\nUSAGE:\n%s [-h] \n\nARGS: \n-h: Help\n\n", name);
  exit(EXIT_SUCCESS);
}

int getStartData(int argc, char** argv) {
  int opt = 0;

  opt = getopt(argc, argv, optString);
  while (opt != -1) {
    switch (opt) {
      case 'h':
        display_usage(argv[0]);
        break;
      default:
        break;
    }
    opt = getopt(argc, argv, optString);
  }

  if (optind < argc) {
    globalArgs.inputPath = argv[optind++];
    if (optind < argc) {
      globalArgs.outputPath = argv[optind];
    }
  }

  return 1;
}

int main(int argc, char** argv) {

  globalArgs.inputPath = NULL;
  globalArgs.outputPath = NULL;

  if (getStartData(argc, argv) == 0) printf("Error occured - programm has stopped\n");

  if (globalArgs.outputPath != NULL) {
    if ((globalArgs.outputFile = fopen(globalArgs.outputPath, "w")) == NULL) {
      fprintf(stderr, "Can not open output file!\n");
      exit(EXIT_FAILURE);
    }
  } else {
    globalArgs.outputFile = stdout;
  }

  if (globalArgs.inputPath != NULL) {
    if ((globalArgs.inputFile = fopen(globalArgs.inputPath, "r")) == NULL) {
      fprintf(stderr, "Can not open input file!\n");
      exit(EXIT_FAILURE);
    }
  } else {
    globalArgs.inputFile = stdin;
  }

  startJob();

  if (globalArgs.inputPath == NULL) {
    endOfOutputString -= 2;
  }

  if (endOfOutputString != 0) {
    for (int i = 0; i <= endOfOutputString; i++) {
      fprintf(globalArgs.outputFile, "%c", outputString[i]);
    }
  }

  return 0;
}
