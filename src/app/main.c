#include <app/interface.h>
#include <fcntl.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TERM_PATH "/dev/tty"

int
main ()
{
  int term = open (TERM_PATH, O_WRONLY);
  if (term == -1 || isatty (0) == 0 || isatty (1) == 0)
    {
      fprintf (stderr, "Error!\n");
      close (term);
      return -1;
    }

  mt_clrscr ();
  mt_setfgcolor (White);
  mt_setbgcolor (Black);
  sc_memoryInit ();
  sc_memorySet (10, 0x7FFF);
  sc_memorySet (0, 1);
  sc_memorySet (5, 4543);
  sc_memorySet (50, 0777);
  for (int i = 0; i < 100; i++)
    {
      print_cell (i);
    }

  mt_gotoXY (14, 1);
  bc_printA ("a");

  close (term);

  return 0;
}
