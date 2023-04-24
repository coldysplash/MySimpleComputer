#include <app/controldevice.h>
#include <app/interface.h>
#include <fcntl.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyReadkey/myreadkey.h>
#include <libmyTerm/myTerm.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
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

int *bc_NUMS[16] = { bc_NULL, bc_ONE,   bc_TWO,   bc_THREE, bc_FOUR, bc_FIVE,
                     bc_SIX,  bc_SEVEN, bc_EIGHT, bc_NINE,  bc_A,    bc_B,
                     bc_C,    bc_D,     bc_E,     bc_F };

int cursor = 0;
int instructionCounter = 0;
int accumulator = 0;

void
output_accumulator ()
{
  char buff[7];
  snprintf (buff, 6, "+%04X", accumulator);
  mt_gotoXY (2, 74);
  write (1, buff, 6);
}

void
output_instructionCounter ()
{
  char buff[7];
  snprintf (buff, 6, "+%04X", instructionCounter);
  mt_gotoXY (5, 72);
  write (1, buff, 6);
}

int
output_operation ()
{
  char buff[9];
  int value, command, operand;

  if (sc_memoryGet (instructionCounter, &value) < 0
      || sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    return -1;

  if ((value & 0x4000))
    {
      command = 0;
      operand = 0;
      sc_regSet (FLAG_WRONG_COMMAND, 1);
    }
  snprintf (buff, 9, "%c%02X : %02X", '+', command, operand);

  mt_gotoXY (8, 70);
  write (1, buff, 9);

  return 0;
}

void
output_flags ()
{
  int value;

  mt_gotoXY (11, 70);
  sc_regGet (FLAG_OVERFLOW, &value);
  write (1, ((value) ? "P" : ""), 1);

  mt_gotoXY (11, 73);
  sc_regGet (FLAG_ERR_DIV_BY_ZERO, &value);
  write (1, ((value) ? "O" : ""), 1);

  mt_gotoXY (11, 76);
  sc_regGet (FLAG_WRONG_ADDRESS, &value);
  write (1, ((value) ? "M" : ""), 1);

  mt_gotoXY (11, 79);
  sc_regGet (FLAG_IGNOR_TACT_IMPULS, &value);
  write (1, ((value) ? "T" : ""), 1);

  mt_gotoXY (11, 82);
  sc_regGet (FLAG_WRONG_COMMAND, &value);
  write (1, ((value) ? "E" : ""), 1);
}

int
output_BigChars ()
{
  int value, command, operand;

  if (sc_memoryGet (cursor, &value) < 0
      || sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    return -1;

  (value & 0x4000) ? bc_printbigchar (bc_MINUS, 15, 2, White, Black)
                   : bc_printbigchar (bc_PLUS, 15, 2, White, Black);

  bc_printbigchar (bc_NUMS[(command >> 4) % 16], 15, 11, White, Black);
  bc_printbigchar (bc_NUMS[(command & 0xf) % 16], 15, 20, White, Black);
  bc_printbigchar (bc_NUMS[(operand >> 4) & 0xf % 16], 15, 29, White, Black);
  bc_printbigchar (bc_NUMS[(operand & 0xf) % 16], 15, 38, White, Black);

  return 0;
}

void
output_SimpleComputer ()
{
  mt_clrscr ();
  print_interface ();
  // print memory
  for (int i = 0; i < 100; i++)
    {
      print_cell (i, cursor);
      mt_setbgcolor (Black);
    }
  output_accumulator ();
  output_instructionCounter ();
  output_operation ();
  output_flags ();
  output_BigChars ();
  mt_gotoXY (25, 1);
}

int
handler_keys ()
{
  int value;
  enum keys k;

  rk_mytermregime (0, 0, 1, 1, 1);

  sc_regGet (FLAG_IGNOR_TACT_IMPULS, &value);

  if (value == 1)
    {
      rk_readkey (&k);
    }
  else
    {
      char bf[2];
      read (1, bf, 2);
    }

  if (k == RESET)
    {
      raise (SIGUSR1);
      sc_memoryInit ();
      sc_regSet (FLAG_IGNOR_TACT_IMPULS, 1);
      sc_regGet (FLAG_OVERFLOW, 0);
      sc_regGet (FLAG_ERR_DIV_BY_ZERO, 0);
      sc_regGet (FLAG_WRONG_ADDRESS, 0);
      sc_regGet (FLAG_WRONG_COMMAND, 0);
    }
  else if (k == RUN)
    {
      sc_regSet (FLAG_IGNOR_TACT_IMPULS, 0);
    }
  else if (k == STEP)
    {
      // *code //
    }
  else if (k == UP)
    {
      if (cursor > 9 && cursor < 100)
        {
          cursor -= 10;
        }
    }
  else if (k == DOWN)
    {
      if (cursor >= 0 && cursor <= 89)
        {
          cursor += 10;
        }
    }
  else if (k == LEFT)
    {
      if (cursor > 0 && cursor < 100)
        {
          cursor--;
        }
    }
  else if (k == RIGHT)
    {
      if (cursor >= 0 && cursor < 99)
        {
          cursor++;
        }
    }

  if (k == ENTER || k == F5 || k == F6 || k == LOAD || k == SAVE)
    {

      rk_mytermregime (1, 0, 0, 1, 1);

      char buf[12] = {};

      mt_gotoXY (25, 1);
      write (0, "Input/Output:", 14);
      mt_gotoXY (26, 1);
      write (0, ">", 2);

      if (k == ENTER)
        {
          read (1, buf, 12);
          int minus_flag = 0;
          if (buf[0] == '-')
            {
              minus_flag = 1;
              buf[0] = '0';
            }
          int actual_num = (int)atoi (buf);
          if (minus_flag == 1)
            {
              actual_num |= 0x4000;
            }

          sc_memorySet (cursor, actual_num);
          setvbuf (stdout, NULL, _IONBF, 0);
          setvbuf (stdin, NULL, _IONBF, 0);
        }
      else if (k == F5)
        {
          read (1, buf, sizeof (buf));
          int tmp_accum = (int)atoi (buf);
          if (tmp_accum >= 0x0 && tmp_accum < 0x7fff)
            {
              accumulator = tmp_accum;
            }
        }
      else if (k == F6)
        {
          read (1, buf, sizeof (buf));
          int new_ic = (int)atoi (buf);
          if (new_ic >= 0 && new_ic < 99)
            {
              instructionCounter = new_ic;
            }
        }
      else if (k == LOAD)
        {
          read (1, buf, 11);
          sc_memoryLoad (buf);
        }
      else if (k == SAVE)
        {
          read (1, buf, 11);
          sc_memorySave (buf);
        }
    }

  return 0;
}