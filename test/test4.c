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

void
test_enter ()
{

  rk_mytermregime (0, 0, 1, 1, 1);

  enum keys k;
  rk_readkey (&k);

  if (k == ENTER)
    {
      mt_clrscr ();
      rk_mytermregime (1, 0, 0, 1, 1);

      char buf[12] = {};

      mt_gotoXY (1, 1);
      write (0, "Input/Output:", 14);
      mt_gotoXY (2, 1);
      write (0, ">", 2);
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

      sc_memorySet (0, actual_num);
      setvbuf (stdout, NULL, _IONBF, 0);
      setvbuf (stdin, NULL, _IONBF, 0);
      char buff[7];
      int value, command, operand;

      sc_memoryGet (0, &value);
      sc_commandDecode (value & 0x3FFF, &command, &operand);
      snprintf (buff, 7, "%c%02X%02X ", (value & 0x4000) ? '-' : '+', command,
                operand);
      mt_gotoXY (4, 1);
      write (1, buff, 7);
    }

  
}