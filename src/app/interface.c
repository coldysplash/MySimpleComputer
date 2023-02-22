#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define TERM_PATH "/dev/tty"

int show_memory(){

    char buff[6];
    int term = open(TERM_PATH, O_WRONLY);
    if (term == -1) {
        close(term);
        return -1;
    }
    int *value = malloc(sizeof(int));
    int check_plus;
    int x1 = 2, y1 = 2;

    for(int i = 0; i != 10; ++i){
        mt_gotoXY(x1, y1++);
        for(int j = 0; j != 10; ++j){
            if (sc_memoryGet(i * 10 + j, value) == -1) {
                return -1;
            } 
            check_plus = *value & 0x4000;
            if(check_plus == 0){
                sprintf(buff, "%s%04X", "+", *value);
            }else{
                sprintf(buff, "%s%04X", "-", *value);
            }
            write(term, buff, strlen(buff));
        }
    }
    printf("\n");

    close(term);
    return 0;
}