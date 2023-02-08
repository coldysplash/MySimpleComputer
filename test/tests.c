#include <libcomputer/computerlib.h>
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CTEST (test_init, sc_memoryInit){
    ASSERT_EQUAL(sc_memoryInit(), 0);
    print_memory();
}
CTEST (test_memSet, test_memGet){
    sc_memorySet(1, 99);
    ASSERT_EQUAL(sc_memorySet(1, 99), 0);
}