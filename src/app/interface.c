#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
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

void print_interface(){

  mt_clrscr ();
  mt_setfgcolor (White);
  mt_setbgcolor (Black);

  //bc_box for memory
  bc_box (1, 1, 12, 62);
  mt_gotoXY (1, 27);
  write (1, " Memory ", 9);

  //accumulator 
  bc_box (1, 64, 3, 88);
  mt_gotoXY (1, 70);
  write (1, " accumulator ", 14);

  //instuctioncounter
  bc_box (4, 64, 6, 88);
  mt_gotoXY (4, 66);
  write (1, " instructionCounter ", 21);

  //operation
  bc_box (7, 64, 9, 88);
  mt_gotoXY (7, 71);
  write (1, " operation ", 12);

  //flags
  bc_box (10, 64, 12, 88);
  mt_gotoXY (10, 71);
  write (1, " Flags ", 8);

  //bc_box for bigChars
  bc_box (13, 1, 23, 47);

  //Keys
  bc_box (13, 48, 23, 88);

  mt_gotoXY (13, 50);
  write (1, " Keys: ", 8);

  mt_gotoXY (15, 49);
  write (1, " l - load ", 11);

  mt_gotoXY (16, 49);
  write (1, " s - save ", 11);

  mt_gotoXY (17, 49);
  write (1, " r - run ", 10);

  mt_gotoXY (18, 49);
  write (1, " t - step ", 11);
  mt_gotoXY (19, 49);
  write (1, " i - reset ", 12);

  mt_gotoXY (20, 49);
  write (1, " F5 - accumulator ", 19);

  mt_gotoXY (21, 49);
  write (1, " F6 - instructionCounter ", 26);

}