#include "computerlib.h"
#include <stdio.h>
#include <stdlib.h>

void test_1(){
    printf("Тест функции sc_memoryInit\n");
    sc_memoryInit();
    print_memory();
}

void test_2(){
    printf("\n");
    printf("Тест функции sc_memorySet, sc_memoryGet\n");
    sc_memorySet(10, 2023);
}

void test_3(){
    printf("Тест загрузки в бинарный файл\n");
    sc_memoryInit();
    sc_memorySet(85, 555);
    sc_memorySave("test.bin");
}

void test_4(){
    printf("Тест чтения из бинарного файла\n");
    sc_memoryLoad("test.bin");
}


int main(){
    int ch;
    printf("Тест функций MySimpleComputerlib\n");
    printf("1 - тест функций sc_memoryInit, sc_memorySet, sc_memoryGet\n");
    printf("2 - тест функции sc_memorySave\n");
    printf("3 - тест функции sc_memoryLoad\n");

    printf(">>");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        test_1();
        test_2();
        break;
    case 2:
        test_3();
        break;
    case 3:
        test_4();
        break;
    default:
        break;
    }

    return 0;
}
