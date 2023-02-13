#include <libcomputer/computerlib.h>
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST (test_init, sc_memoryInit){
    printf("\n");
    ASSERT_EQUAL(sc_memoryInit(), 0);
    print_memory();
}
CTEST (test_memSet, test_memGet){
    printf("\n");
    sc_memoryInit();
    for(int i = 0; i < 50; i++){
        sc_memorySet(i, i);
    }
    print_memory();
    ASSERT_EQUAL(sc_memorySet(1, 1), 0);
    ASSERT_EQUAL(sc_memorySet(120, 20), -1);

    int value = 0;
    sc_memoryGet(28, &value);
    printf("Value[28] = %d\n", value);
}

CTEST (test_memSave, sc_memorySave){
    char* path = "/home/kuroro/MySimpleComputerwork/mysimplecomputer/test/testSave.bin";
    char* path1 = "/home/kuroro/MySimpleComputerwork/mysimplecomputer/test/testLoad.bin";
    printf("\n");
    sc_memoryInit();
    sc_memorySet(10, 555);
    sc_memorySet(15, 5);
    sc_memorySave(path);
    sc_memorySave(path1);
    ASSERT_EQUAL(sc_memorySave(path), 0);
}

CTEST (test_memLoad, sc_memoryLoad){
    char* path = "/home/kuroro/MySimpleComputerwork/mysimplecomputer/test/testLoad.bin";
    printf("\n");
    sc_memoryInit();
    sc_memoryLoad(path);
    print_memory();
    ASSERT_EQUAL(sc_memoryLoad(path), 0);
}
