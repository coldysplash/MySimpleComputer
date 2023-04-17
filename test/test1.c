#include <ctest.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tests for lab1
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

CTEST(test_sc_regGet, sc_regGet){
    sc_regInit();
    int value;
    ASSERT_EQUAL(sc_regSet(FLAG_WRONG_COMMAND, 1), 0);
    ASSERT_EQUAL(sc_regGet(FLAG_WRONG_COMMAND, &value), 0);
    printf("%d", value);

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


