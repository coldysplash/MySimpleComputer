#include "SAT.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libcomputer/computerlib.h>

int RAM[100];

int check_command(char *buf_command){
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

int
SAT (char *inputfilename, char *outputfilename)
{

  FILE *inputFile = fopen (inputfilename, "r");

  if (!inputFile)
    {
      fprintf(stderr, "Error input file..!\n");
      return -1;
    }

  fclose (inputFile);

  memset (RAM, 0, sizeof (RAM));

    int counter_str = 0;

    while (!feof (inputFile)){
        if(counter_str > 99){
            fprintf(stderr, "Instruction overflow..!\n");
            return -1;
        }
        char buf[50] = { 0 };
        fgets (buf, 50, inputFile);

    if (buf[strlen(buf)] == '\n')
        {
          buf[strlen(buf)] = 0;
        }
    char *token = strtok(buf, " ");
    int address_cell = atoi(token);

    if(address_cell < 0 || address_cell > 99){
        fprintf(stderr, "Wrong address..!\n");
        return -1;
    }

    token = strtok(NULL, " ");
    int command = check_command(token);

    token = strtok(NULL, " ");
    int operand = atoi(token);

    if(operand > 65535){
        fprintf(stderr, "Wrong operand..!\n");
        return -1;
    }

    int value = 0;
    sc_commandEncode (command, operand, &value);

    RAM[address_cell] = value;

    printf("%d\n ", value);

    counter_str++;

    }

  FILE *outputFile = fopen (outputfilename, "wb");
  fclose (outputFile);

  return 0;
}