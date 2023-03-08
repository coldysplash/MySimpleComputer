#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
show_interface ()
{
  char buff[10];
  int *value = malloc (sizeof (int));
  int check_plus;
  int x1 = 2, y1 = 2;

  for (int i = 0; i != 10; ++i)
    {
      mt_gotoXY (x1, y1++);
      for (int j = 0; j != 10; ++j)
        {
          sc_memoryGet (i * 10 + j, value);
          check_plus = *value & 0x4000;
          if (check_plus == 0)
            {
              sprintf (buff, "%s%04X ", "+", *value);
            }
          else
            {
              sprintf (buff, "%s%04X ", "-", *value);
            }
          write (1, buff, strlen (buff));
        }
    }

  mt_gotoXY (70, 2);
  write (1, "accumulator", sizeof ("accumulator"));
  mt_gotoXY (73, 3);
  write (1, "+9999", sizeof ("+9999"));
  mt_gotoXY (70, 4);
  write (1, "instructionCounter", sizeof ("instructionCounter"));
  mt_gotoXY (73, 5);
  write (1, "+0000", sizeof ("+0000"));
  mt_gotoXY (70, 6);
  write (1, "Operation", sizeof ("Operation"));
  mt_gotoXY (73, 7);
  write (1, "+00 : 00", sizeof ("+00 : 00"));
  mt_gotoXY (70, 8);
  write (1, "Flags", sizeof ("Flags"));
  mt_gotoXY (73, 9);
  write (1, "O E V M", sizeof ("O E V M"));
  mt_gotoXY (50, 12);
  write (1, "Keys:", sizeof ("Keys:"));
  mt_gotoXY (48, 13);
  write (1, "l - load", sizeof ("l - load"));
  mt_gotoXY (48, 14);
  write (1, "s - save", sizeof ("s - save"));
  mt_gotoXY (48, 15);
  write (1, "r - run", sizeof ("r - run"));
  mt_gotoXY (48, 16);
  write (1, "t - step", sizeof ("t - step"));
  mt_gotoXY (48, 17);
  write (1, "i - reset", sizeof ("i - reset"));
  mt_gotoXY (48, 18);
  write (1, "F5 - accumulator", sizeof ("F5 - accumulator"));
  mt_gotoXY (48, 19);
  write (1, "F6 - instructionCounter", sizeof ("F6 - instructionCounter"));
  printf ("\n");

  return 0;
}
