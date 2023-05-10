#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SAT.h"

void
print_usage ()
{
  printf ("Usage:\n");
  printf ("    sat <inputfile.sa> <outputfile.o>\n");
}

int
main (int argc, char *argv[])
{
  if (argc != 3)
    {
      print_usage ();
      return -1;
    }
  else
    {
      SAT(argv[1], argv[2]);
    }
  return 0;
}