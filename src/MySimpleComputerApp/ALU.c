#include <MySimpleComputerApp/ALU.h>
#include <MySimpleComputerApp/CPU.h>
#include <libcomputer/computerlib.h>
#include <stdio.h>
#include <unistd.h>

int
ALU (int command, int operand)
{
  int value = 0;

  if (operand > 0 && operand <= 99)
    {
      sc_memoryGet (operand, &value);
    }
  else
    {
      return -1;
    }

  switch (command)
    {
    case 30:
      accumulator += value;
      break;
    case 31:
      accumulator -= value;
      break;
    case 32:
      if (value != 0)
        {
          accumulator /= value;
        }
      else
        {
          sc_regSet (FLAG_ERR_DIV_BY_ZERO, 1);
          return -1;
        }
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