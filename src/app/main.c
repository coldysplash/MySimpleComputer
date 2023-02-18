#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    mt_clrscr();
    mt_setfgcolor(Red);
    mt_setbgcolor(White);
    printf("HEllo");

    int *r = malloc(sizeof(u_int));
    int *c = malloc(sizeof(u_int));
    mt_getscreensize(r,c);
    mt_gotoXY(5,5); // 129, 129 Error
    
    return 0;
}
