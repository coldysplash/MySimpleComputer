#include <ctest.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tests for lab1

CTEST (test_init, sc_memoryInit) { ASSERT_EQUAL (sc_memoryInit (), 0); }
CTEST (test_memSet, test_memGet)
{
  sc_memoryInit ();
  ASSERT_EQUAL (sc_memorySet (1, 1), 0);
  ASSERT_EQUAL (sc_memorySet (200, 20), -1);

  int value, command, operand;
  sc_commandEncode (10, 10, &value);
  printf ("\n %04X \n", value);
  sc_memorySet (1, 0x050A);
  sc_memoryGet (1, &value);
  sc_commandDecode (value & 0x3FFF, &command, &operand);
  printf ("\n %X \n", command);
  printf ("\n %X \n", operand);
}

CTEST (test_sc_regGet, sc_regGet)
{
  sc_regInit ();
  int value;
  ASSERT_EQUAL (sc_regSet (FLAG_WRONG_COMMAND, 1), 0);
  ASSERT_EQUAL (sc_regGet (FLAG_WRONG_COMMAND, &value), 0);
  printf ("%d", value);
}

CTEST (test_memSave, sc_memorySave)
{
  sc_memoryInit ();
  sc_memorySet (10, 555);
  sc_memorySet (15, 5);
  sc_memorySave ("testSave.bin");
  ASSERT_EQUAL (sc_memorySave ("testSave.bin"), 0);
}

CTEST (test_memLoad, sc_memoryLoad)
{
  sc_memoryInit ();
  sc_memoryLoad ("testSave.bin");
  ASSERT_EQUAL (sc_memoryLoad ("testSave.bin"), 0);
}
