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
        fprintf(stderr, "[E] Unknown command, exiting..!\n");
        return -1;
    }

    return command;
}

int
SAT (char *inputfilename, char *outputfilename)
{

  FILE *inputFile = fopen (inputfilename, "r");
  size_t size_buf = 0;
  if (inputFile != NULL)
    {
      fseek (inputFile, 0, SEEK_END);
      size_buf = ftell (inputFile);
      rewind (inputFile);
    }
  else
    {
      fprintf(stderr, "Error input file..!\n");
      return -1;
    }

  char *buf = malloc (size_buf + 1);
  fread (buf, 1, size_buf + 1, inputFile);
  buf[size_buf] = '\0';

  fclose (inputFile);

  memset (RAM, 0, sizeof (RAM));

  printf("%ld\n", size_buf);

    char *str = strtok (buf, "\n");

    // while(str != NULL){

    //     //printf("%s", str);

    //     sat(str);

    //     str = strtok(NULL, "\n");

    // }


  free (buf);

  FILE *outputFile = fopen (outputfilename, "wb");
  fclose (outputFile);

  return 0;
}

int sat(char *buff){

    if (buff[strlen(buff)] == '\n')
        {
          buff[strlen(buff)] = 0;
        }
    char *token = strtok(buff, " ");
    int address_cell = atoi(token);

    if(address_cell < 0 || address_cell > 99){
        fprintf(stderr, "[E] Wrong address..!\n");
        return -1;
    }

    token = strtok(NULL, " ");
    int command = check_command(token);

    token = strtok(NULL, " ");
    int operand = atoi(token);

    if(operand > 65535){
        fprintf(stderr, "[E] Wrong operand..!\n");
        return -1;
    }

    int value = 0;
    sc_commandEncode (command, operand, &value);

    RAM[address_cell] = value;

    printf("%d\n ", value);

    return 0;

}