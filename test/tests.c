#include <libcomputer/computerlib.h>
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST (test_init, sc_memoryInit){
    printf("\n");
    ASSERT_EQUAL(sc_memoryInit(), 0);
}
CTEST (test_memSet, test_memGet){
    printf("\n");
    sc_memoryInit();
    ASSERT_EQUAL(sc_memorySet(1, 1), 0);
    ASSERT_EQUAL(sc_memorySet(200, 20), -1);

    int value = 0;
    sc_memoryGet(28, &value);
}

CTEST (test_memSave, sc_memorySave){
    printf("\n");
    sc_memoryInit();
    sc_memorySet(10, 555);
    sc_memorySet(15, 5);
    sc_memorySave("testSave.bin");
    sc_memorySave("testLoad.bin");
    ASSERT_EQUAL(sc_memorySave("testSave.bin"), 0);
}

CTEST (test_memLoad, sc_memoryLoad){
    printf("\n");
    sc_memoryInit();
    sc_memoryLoad("testLoad.bin");
    ASSERT_EQUAL(sc_memoryLoad("testLoad.bin"), 0);
}
