#include <app/interface.h>
#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  mt_clrscr ();
  mt_setfgcolor (Red);
  mt_setbgcolor (White);
  sc_memoryInit ();
  sc_memorySet (1, 555);
  sc_memorySet (2, 10);
  show_interface ();

  return 0;
}
