#include <libcomputer/computerlib.h>
#include <libmyTerm/myTerm.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TERM_PATH "/dev/tty"

int show_memory(){

    char buff[10];
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
	        sc_memoryGet(i * 10 + j, value);
            check_plus = *value & 0x4000;
            if(check_plus == 0){
                sprintf(buff, "%s%04X ", "+", *value);
            }else{
                sprintf(buff, "%s%04X ", "-", *value);
            }
            write(term, buff, strlen(buff));
        }
    }

    mt_gotoXY(70, 2);
    write(term, "accumulator", sizeof("accumulator"));
    mt_gotoXY(73, 3);
    write(term, "+9999", sizeof("+9999"));
    mt_gotoXY(70, 4);
    write(term, "instructionCounter", sizeof("instructionCounter"));
    mt_gotoXY(73, 5);
    write(term, "+0000", sizeof("+0000"));
    mt_gotoXY(70, 6);
    write(term, "Operation", sizeof("Operation"));
    mt_gotoXY(73, 7);
    write(term, "+00 : 00", sizeof("+00 : 00"));
    mt_gotoXY(70, 8);
    write(term, "Flags", sizeof("Flags"));
    mt_gotoXY(73, 9);
    write(term, "O E V M", sizeof("O E V M"));
    mt_gotoXY(50, 12);
    write(term, "Keys:", sizeof("Keys:"));
    mt_gotoXY(48, 13);
    write(term, "l - load", sizeof("l - load"));
    mt_gotoXY(48, 14);
    write(term, "s - save", sizeof("s - save"));
    mt_gotoXY(48, 15);
    write(term, "r - run", sizeof("r - run"));
    mt_gotoXY(48, 16);
    write(term, "t - step", sizeof("t - step"));
    mt_gotoXY(48, 17);
    write(term, "i - reset", sizeof("i - reset"));
    mt_gotoXY(48, 18);
    write(term, "F5 - accumulator", sizeof("F5 - accumulator"));
    mt_gotoXY(48, 19);
    write(term, "F6 - instructionCounter", sizeof("F6 - instructionCounter"));
    printf("\n");


    close(term);
    return 0;
}
