#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
print_cell (int address)
{
  char buff[7];
  int row, col, value, command, operand;

  if (sc_memoryGet (address, &value) < 0
      || sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    return -1;

  snprintf (buff, 7, "%c%02X%02X ", (value & 0x4000) ? '-' : '+', command,
            operand);
  row = address / 10;
  col = address % 10;
  mt_gotoXY (2 + row, 2 + col * 6);
  write (1, buff, 6);

  return 0;
}