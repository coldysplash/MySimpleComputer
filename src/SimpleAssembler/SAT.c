#include "SAT.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libcomputer/computerlib.h>

int RAM[100];

int check_command(char *buf_command) {
  int command = 0;

  if (!strcmp(buf_command, "READ")) {
    command = 10;
  } else if (!strcmp(buf_command, "WRITE")) {
    command = 11;
  } else if (!strcmp(buf_command, "LOAD")) {
    command = 20;
  } else if (!strcmp(buf_command, "STORE")) {
    command = 21;
  } else if (!strcmp(buf_command, "ADD")) {
    command = 30;
  } else if (!strcmp(buf_command, "SUB")) {
    command = 31;
  } else if (!strcmp(buf_command, "DIVIDE")) {
    command = 32;
  } else if (!strcmp(buf_command, "MUL")) {
    command = 33;
  } else if (!strcmp(buf_command, "JUMP")) {
    command = 40;
  } else if (!strcmp(buf_command, "JNEG")) {
    command = 41;
  } else if (!strcmp(buf_command, "JZ")) {
    command = 42;
  } else if (!strcmp(buf_command, "HALT")) {
    command = 43;
  } else {
    fprintf(stderr, "Unknown command, exiting..!\n");
    return -1;
  }

  return command;
}

int SAT(char *inputfilename, char *outputfilename) {

  FILE *inputFile = fopen(inputfilename, "r");

  if (!inputFile) {
    fprintf(stderr, "Error input file..!\n");
    return -1;
  }

  memset(RAM, 0, sizeof(RAM));

  int counter_str = 0;

  while (!feof(inputFile)) {
    if (counter_str > 99) {
      fprintf(stderr, "Instruction overflow..!\n");
      return -1;
    }
    char buf[50] = {0};
    fgets(buf, 50, inputFile);
    if (strlen(buf) < 1) {
      break;
    }

    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = 0;
    }
    char *token = strtok(buf, " ");
    int address_cell = atoi(token);

    if (address_cell < 0 || address_cell > 99) {
      fprintf(stderr, "Wrong address..!\n");
      return -1;
    }

    int command = 0;
    token = strtok(NULL, " ");
    if (!strcmp(token, "=")) {
      command = 0;
    } else {
      command = check_command(token);
    }

    token = strtok(NULL, " ");
    char *tok_tmp = *token == '+' || *token == '-' ? token + 1 : token;
    int operand = command ? atoi(tok_tmp) : atoi(tok_tmp);

    if (*token == '-') {
      operand = -operand;
    }

    if (operand > 65535) {
      fprintf(stderr, "Wrong operand..!\n");
      return -1;
    }

    if (command != 0) {
      if (sc_commandEncode(command, operand, &RAM[address_cell]) == -1) {
        printf("Error: sc_commandEncode(): -1 !\n");
      }
    } else {
      if (operand < 0) {
        RAM[address_cell] = ((-operand) & 0x3fff) | 0x4000;
      } else {
        RAM[address_cell] = operand & 0x3fff;
      }
    }

    counter_str++;
  }
  fclose(inputFile);

  FILE *outputFile = fopen(outputfilename, "wb");
  if (!outputFile) {
    fprintf(stderr, "Error input file..!\n");
    return -1;
  }

  fwrite(RAM, sizeof(RAM[0]), 100, outputFile);

  fclose(outputFile);

  return 0;
}

void print_usage() {
  printf("Usage:\n");
  printf("    sat <inputfile.sa> <outputfile.o>\n");
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    print_usage();
    return -1;
  } else {
    SAT(argv[1], argv[2]);
  }
  return 0;
}