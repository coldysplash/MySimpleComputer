#include <ctest.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST (test_bc_printA, bc_printA) { ASSERT_EQUAL (bc_printA ("q"), 0); }

CTEST (test_bc_box, bc_box)
{
  ASSERT_EQUAL (bc_box (1, 1, 2, 2), 0);
  ASSERT_EQUAL (bc_box (-1, 1, -1, -5), -1);
}

CTEST (test_bc_printbigchar, bc_printbigchar)
{
  int bc_NULL[2] = { 0x8181817e, 0x7e818181 };
  ASSERT_EQUAL (bc_printbigchar (bc_NULL, 10, 70, White, Black), 0);
}

CTEST (test_bc_setbigcharpos, bc_setbigcharpos)
{
  int bc_NULL[2] = { 0x8181817e, 0x7e818181 };
  ASSERT_EQUAL (bc_setbigcharpos (&bc_NULL[2], 1, 1, 0), 0);
  ASSERT_EQUAL (bc_setbigcharpos (&bc_NULL[2], 1, 1, 2), -1);
  ASSERT_EQUAL (bc_setbigcharpos (&bc_NULL[2], -1, -1, 0), -1);
}

CTEST (test_bc_getbigcharpos, bc_getbigcharpos)
{
  int bc_ONE[2] = { 0x8890A0C0, 0x80808080 };
  int value = 1;
  ASSERT_EQUAL (bc_getbigcharpos (&bc_ONE[2], 0, 2, &value), 0);
  ASSERT_EQUAL (bc_getbigcharpos (&bc_ONE[2], 0, -1, &value), -1);
  ASSERT_EQUAL (value, 0);
}
