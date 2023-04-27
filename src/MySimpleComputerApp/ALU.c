#include <MySimpleComputerApp/ALU.h>
#include <MySimpleComputerApp/CU.h>
#include <libcomputer/computerlib.h>
#include <stdio.h>
#include <unistd.h>

int ALU(int command, int operand)
{
    int value = 0;
    sc_commandEncode (command, operand, &value);

    switch (command) {
    case 30:
        accumulator += value;
        break;
    case 31:
        accumulator -= value;
        break;
    case 32: 
        accumulator /= value;
        break;
    case 33:
        accumulator *= value;
        break;

    default:
        return -1;
        break;
    };

    return 0;
}