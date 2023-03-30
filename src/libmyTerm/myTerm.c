#include <fcntl.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

// mt_clrscr - производит очистку и перемещение курсора
//             в левый верхний угол экрана
int
mt_clrscr ()
{
  write (1, "\E[H\E[J", sizeof ("\E[H\E[J"));

  return 0;
}

// mt_gotoXY - перемещает курсор в указанную позицию
int
mt_gotoXY (int x, int y)
{

  if ((x < 0) || (y < 0))
    {
      return -1;
    }

  char buff[30];
  sprintf (buff, "\E[%d;%dH", x, y);

  write (1, buff, strlen (buff));

  return 0;
}

// mt_getscreensize - определяет размер
//                    экрана терминала
int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;

  if (rows == NULL || cols == NULL || ioctl (0, TIOCGWINSZ, &ws))
    {
      return -1;
    }

  *rows = ws.ws_row;
  *cols = ws.ws_col;

  return 0;
}

// mt_setfgcolor - устанавливает цвет последующих
//                 выводимых символов
int
mt_setfgcolor (enum Colors color)
{
  char buff[30];

  sprintf (buff, "\E[3%dm", color);

  write (1, buff, strlen (buff));

  return 0;
}

// mt_setbgcolor - устанавливает цвет фона
//                 последующих выводимых символов
int
mt_setbgcolor (enum Colors color)
{
  char buff[30];

  sprintf (buff, "\E[4%dm", color);

  write (1, buff, strlen (buff));

  return 0;
}