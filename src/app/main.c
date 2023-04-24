#include <app/controldevice.h>
#include <app/interface.h>
#include <fcntl.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyReadkey/myreadkey.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TERM_PATH "/dev/tty"

int
main ()
{
  int term = open (TERM_PATH, O_RDWR);
  if (term == -1 || isatty (0) == 0 || isatty (1) == 0)
    {
      fprintf (stderr, "Error!\n");
      close (term);
      return -1;
    }
  sc_regInit ();
  sc_memoryInit ();
  sc_regSet (FLAG_IGNOR_TACT_IMPULS, 1);

  while (1)
    {
      output_SimpleComputer ();
      handler_keys ();
    }
  close (term);

  return 0;
}
