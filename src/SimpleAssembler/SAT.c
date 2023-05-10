#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "SAT.h"

int commands[] = { 10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43, 74 };

int RAM[100];

int SAT(char *inputfilename, char *outputfilename){


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
        printf ("Error input file!\n");
        return -1;
    }

    char *buf = malloc (size_buf + 1);
    fread (buf, 1, size_buf + 1, inputFile);
    buf[size_buf] = '\0';

    fclose (inputFile);


    char *str = strtok (buf, "\n");

    while(str != NULL){

        printf ("%s\n", str);

        str = strtok (NULL, "\n");
    }




    free(buf);

    memset (RAM, 0, sizeof (RAM));


    FILE *outputFile = fopen (outputfilename, "wb");
    fclose(outputFile);

    return 0;


}