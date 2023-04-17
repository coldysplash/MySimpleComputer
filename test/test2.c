#include <ctest.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST (test_clrscr, mt_clrscr) { ASSERT_EQUAL (mt_clrscr (), 0); }

CTEST (test_gotoXY, mt_gotoXY)
{
  ASSERT_EQUAL (mt_gotoXY (10, 10), 0);
  ASSERT_EQUAL (mt_gotoXY (-1, -5), -1);
}

CTEST (test_getscreensize, mt_getscreensize)
{
  int *r = malloc (sizeof (u_int));
  int *c = malloc (sizeof (u_int));
  ASSERT_EQUAL (mt_getscreensize (r, c), 0);
}

CTEST (test_setfgcolor, mt_setfgcolor)
{
  ASSERT_EQUAL (mt_setfgcolor (Blue), 0);
}

CTEST (test_setbgcolor, mt_setbgcolor)
{
  ASSERT_EQUAL (mt_setbgcolor (White), 0);
}
