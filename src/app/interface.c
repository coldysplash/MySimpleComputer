#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int bc_PLUS[2] = { 0xFF181818, 0x181818FF };
int bc_MINUS[2] = { 0xFF000000, 0x000000FF };
int bc_NULL[2] = { 0x8181817e, 0x7e818181 };
int bc_ONE[2] = { 0x8890A0C0, 0x80808080 };
int bc_TWO[2] = { 0x2040827C, 0xFE040810 };
int bc_THREE[2] = { 0x6080817E, 0x7E818060 };
int bc_FOUR[2] = { 0xFF818181, 0x80808080 };
int bc_FIVE[2] = { 0x7F0101FF, 0x7F808080 };
int bc_SIX[2] = { 0x0101817E, 0x7E81817F };
int bc_SEVEN[2] = { 0x204080FE, 0x02040810 };
int bc_EIGHT[2] = { 0x7E81817E, 0x7E818181 };
int bc_NINE[2] = { 0x7E81817E, 0x7E808080 };
int bc_A[2] = { 0x7E42423C, 0x42424242 };
int bc_B[2] = { 0x3E42423E, 0x3E424242 };
int bc_C[2] = { 0x0101017E, 0x7E010101 };
int bc_D[2] = { 0x4242221E, 0x1E224242 };
int bc_E[2] = { 0x7E02027E, 0x7E020202 };
int bc_F[2] = { 0x7E02027E, 0x02020202 };

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

void
print_bc_box_memory ()
{

  bc_box (1, 1, 12, 62);
  mt_gotoXY (1, 27);
  write (1, " Memory ", 9);
}

void
print_accumulator ()
{

  bc_box (1, 64, 3, 88);
  mt_gotoXY (1, 70);
  write (1, " accumulator ", 14);
  mt_gotoXY (2, 74);
  write(1, "+0000", 5);
}

void
print_instructionCounter ()
{
  bc_box (4, 64, 6, 88);
  mt_gotoXY (4, 66);
  write (1, " instructionCounter ", 21);
  mt_gotoXY(5, 72);
  write(1, "0", 1);
}

void
print_operation ()
{

  bc_box (7, 64, 9, 88);
  mt_gotoXY (7, 71);
  write (1, " operation ", 12);
  mt_gotoXY (8, 70);
  write (1, " +00 : 00 ", 10);

}

void
print_flags ()
{
  bc_box (10, 64, 12, 88);
  mt_gotoXY (10, 71);
  write (1, " Flags ", 8);

  int value;
  mt_gotoXY (11, 68);
  sc_regGet (FLAG_OVERFLOW, &value);
  write (1, ((value) ? "P" : ""), 1);

  mt_gotoXY (11, 70);
  sc_regGet (FLAG_ERR_DIV_BY_ZERO, &value);
  write (1, ((value) ? "O" : ""), 1);

  mt_gotoXY (11, 72);
  sc_regGet (FLAG_WRONG_ADDRESS, &value);
  write (1, ((value) ? "M" : ""), 1);

  mt_gotoXY (11, 74);
  sc_regGet (FLAG_IGNOR_TEXT_IMPULS, &value);
  write (1, ((value) ? "T" : ""), 1);

  mt_gotoXY (11, 76);
  sc_regGet (FLAG_WRONG_COMMAND, &value);
  write (1, ((value) ? "E" : ""), 1);
}

void
print_BigChars ()
{
  // int value;
  bc_box (13, 1, 23, 47);
  bc_setbigcharpos (bc_PLUS, 0, 6, 0);
  bc_printbigchar (bc_PLUS, 15, 2, White, Black);
  bc_printbigchar (bc_NULL, 15, 11, White, Black);
  bc_printbigchar (bc_NULL, 15, 20, White, Black);
  bc_printbigchar (bc_NULL, 15, 29, White, Black);
  bc_printbigchar (bc_ONE, 15, 38, White, Black);
  // bc_getbigcharpos(bc_NINE, 2, 7, &value);
  // printf("%d", value);
}

void
print_Keys ()
{
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
