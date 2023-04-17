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

void test_enter(){

  mt_clrscr ();
  rk_mytermregime (0, 0, 1, 1, 1);

  enum keys k;
  rk_readkey (&k);

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

          sc_memorySet (0, actual_num);
          setvbuf (stdout, NULL, _IONBF, 0);
          setvbuf (stdin, NULL, _IONBF, 0);

        }
}

