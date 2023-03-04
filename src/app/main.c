#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <app/interface.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    mt_clrscr();
    mt_setfgcolor(Red);
    mt_setbgcolor(White);
    sc_memoryInit();
    sc_memorySet(1, 555);
    sc_memorySet(2, 10);
    show_memory();

    #if 0
    int *r = malloc(sizeof(u_int));
    int *c = malloc(sizeof(u_int));
    mt_getscreensize(r,c);
    mt_gotoXY(5,5); // 129, 129 Error
    #endif
    return 0;
}
