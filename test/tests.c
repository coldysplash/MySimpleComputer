#include <ctest.h>
#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <libmyBigChars/myBigChars.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//tests for lab1
#if 0

CTEST (test_init, sc_memoryInit){
    ASSERT_EQUAL(sc_memoryInit(), 0);
}
CTEST (test_memSet, test_memGet){
    sc_memoryInit();
    ASSERT_EQUAL(sc_memorySet(1, 1), 0);
    ASSERT_EQUAL(sc_memorySet(200, 20), -1);

    int value = 0;
    sc_memoryGet(28, &value);
}

CTEST (test_memSave, sc_memorySave){
    sc_memoryInit();
    sc_memorySet(10, 555);
    sc_memorySet(15, 5);
    sc_memorySave("bin/testSave.bin");
    sc_memorySave("bin/testLoad.bin");
    ASSERT_EQUAL(sc_memorySave("bin/testSave.bin"), 0);
}

CTEST (test_memLoad, sc_memoryLoad){
    sc_memoryInit();
    sc_memoryLoad("bin/testLoad.bin");
    ASSERT_EQUAL(sc_memoryLoad("bin/testLoad.bin"), 0);
}
#endif

//tests for lab2

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

//tests for lab3

CTEST (test_bc_printA, bc_printA)
{
  ASSERT_EQUAL (bc_printA("q"), 0);
}
