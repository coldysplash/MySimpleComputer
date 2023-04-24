#define CTEST_MAIN

#include <ctest.h>
#include <fcntl.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyReadkey/myreadkey.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <test4.h>
#include <unistd.h>

int
main (int argc, const char **argv)
{
  sc_memoryInit ();
  rk_mytermsave ();
  while (1)
    {
      test_enter ();
    }
  return ctest_main (argc, argv);
}