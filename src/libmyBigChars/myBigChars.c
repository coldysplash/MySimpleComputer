#include <fcntl.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// acs chars
#define CKBOARD ("a")  // ▒
#define HLINE ("q")    // ─
#define VLINE ("x")    // │
#define LUCORNER ("l") // ┌
#define LDCORNER ("m") // └
#define RDCORNER ("j") // ┘
#define RUCORNER ("k") // ┐

int
bc_printA (char *str)
{
  char buff[strlen (str)];
  sprintf (buff, "\E(0%s\E(B", str);
  if (write (1, buff, strlen (buff)) == -1)
    {
      return -1;
    }

  return 0;
}

int
bc_box (int x1, int y1, int x2, int y2)
{

  if (x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0 || x1 > x2 || y1 > y2)
    {
      return -1;
    }

  mt_gotoXY (x1, y1);
  bc_printA (LUCORNER);

  for (int i = y1 + 1; i < y2; i++)
    {
      mt_gotoXY (x1, i);
      bc_printA (HLINE);
      mt_gotoXY (x2, i);
      bc_printA (HLINE);
    }
  bc_printA (RDCORNER);

  for (int i = x1 + 1; i < x2; i++)
    {
      mt_gotoXY (i, y1);
      bc_printA (VLINE);
      mt_gotoXY (i, y2);
      bc_printA (VLINE);
    }

  mt_gotoXY (x1, y2);
  bc_printA (RUCORNER);

  mt_gotoXY (x2, y1);
  bc_printA (LDCORNER);

  return 0;
}

int
bc_printbigchar (int bigchar[], int x, int y, enum Colors frontcolor,
                 enum Colors backcolor)
{

  if (mt_setfgcolor (frontcolor) == -1 || mt_setbgcolor (backcolor) == -1
      || mt_gotoXY (x, y) == -1)
    {
      return -1;
    }

  for (int i = 0; i < 4; i++)
    {
      int value = (bigchar[0] >> (i * 8)) & 0xff;
      for (int j = 0; j < 8; j++)
        {
          mt_gotoXY (x + i, y + j);
          int ch = (value >> j) & 0x00000001;
          if (ch == 1)
            {
              bc_printA (CKBOARD);
            }
          else
            {
              write (1, " ", 2);
            }
        }
    }

  for (int i = 0; i < 4; i++)
    {
      int value = (bigchar[1] >> (i * 8)) & 0xff;
      for (int j = 0; j < 8; j++)
        {
          mt_gotoXY (x + 4 + i, y + j);
          int ch = (value >> j) & 0x00000001;
          if (ch == 1)
            {
              bc_printA (CKBOARD);
            }
          else
            {
              write (1, " ", 2);
            }
        }
    }

  return 0;
}

int
bc_setbigcharpos (int *big, int x, int y, int value)
{

  if (big == NULL || x < 0 || y < 0 || x > 7 || y > 7 || value > 1
      || value < 0)
    {
      return -1;
    }

  int bc_position = x < 4 ? 0 : 1;
  x = x % 4;

  if (value == 1)
    {
      big[bc_position] |= 1 << (x * 8 + y);
    }
  else
    {
      big[bc_position] &= ~(1 << (x * 8 + y));
    }

  return 0;
}

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (big == NULL || value == NULL || x < 0 || y < 0 || x > 7 || y > 7)
    {
      return -1;
    }

  int bc_position = x < 4 ? 0 : 1;
  x = x % 4;

  *value = big[bc_position] >> ((x * 8) + y) & 1;

  return 0;
}

int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (big == NULL || count < 1)
    {
      return -1;
    }
  if (write (fd, big, (sizeof (int)) * count * 2) == -1)
    {
      return -1;
    }
  return 0;
}

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  if (big == NULL || need_count < 1 || count == NULL)
    {
      *count = 0;
      return -1;
    }

  int cnt = read (fd, big, (sizeof (int)) * need_count * 2);

  if (cnt == -1)
    {
      *count = 0;
      return -1;
    }

  *count = cnt / (sizeof (int) * 2);

  return 0;
}
