#include <fcntl.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
bc_printA (char *str)
{

  char buff[30];
  sprintf (buff, "\E(0%s\E(B", str);
  write (1, buff, strlen (buff));

  return 0;
}

int bc_box(int x1, int y1, int x2, int y2){

    for(; y1 < y2; y1++){
	mt_gotoXY(x1, y1);
	bc_printA("q");
    }
    for(; x1 < x2; x1++){
	mt_gotoXY(x1, 0);
	bc_printA("x");
	mt_gotoXY(x1, y2);
	bc_printA("x");
    }

    return 0;

}
