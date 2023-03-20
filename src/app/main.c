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
  sc_memorySet (0, 0x7FFF);
  //sc_memorySet (0, 1);
  sc_memorySet (5, 4543);
  sc_memorySet (50, 0777);
  sc_regInit ();
  sc_regSet (FLAG_OVERFLOW, 1);
  // print memory
  for (int i = 0; i < 100; i++)
    {
      print_cell (i);
    }

  print_bc_box_memory ();
  print_accumulator ();
  print_instructionCounter ();
  print_operation (print_instructionCounter ());
  print_flags ();
  print_BigChars ();
  print_Keys ();

  mt_gotoXY (25, 1);
  close (term);

  return 0;
}
