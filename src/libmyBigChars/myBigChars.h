#pragma once
#include <libmyTerm/myTerm.h>

int bc_printA (char *str);
int bc_box (int x1, int y1, int x2, int y2);
int bc_printbigchar (int bigchar[], int x, int y, enum Colors frontcolor, enum Colors backcolor);
int bc_setbigcharpos (int * big, int x, int y, int value);