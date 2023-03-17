#include <fcntl.h>
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
  write (1, buff, strlen (buff));

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