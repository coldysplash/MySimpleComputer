#include <app/interface.h>
#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define TERM_PATH "/dev/tty"

int
main ()
{
  int term = open (TERM_PATH, O_WRONLY);
  if (term == -1 || isatty(0) == 0 || isatty(1) == 0)
  {
    fprintf(stderr, "Error!\n");
    close (term);
    return -1;
  }

  mt_clrscr ();
  mt_setfgcolor (Red);
  mt_setbgcolor (White);
  sc_memoryInit ();
  sc_memorySet (1, 555);
  sc_memorySet (2, 10);
  show_interface ();

  close (term);

  return 0;
}
