#include <fcntl.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int bc_printA(char * str){

    char buff[30];
    sprintf(buff, "\E(0%s\E(B", str);
    write(1, buff, strlen(buff));

    return 0;
}



