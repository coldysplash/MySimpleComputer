#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <libmyTerm/myTerm.h>

#define TERM_PATH "/dev/tty"

// mt_clrscr - производит очистку и перемещение курсора 
//             в левый верхний угол экрана
int mt_clrscr(){
    int term = open(TERM_PATH, O_WRONLY);

    if(term == -1){
        return -1;
    }

    write(term, "\E[H\E[J", sizeof("\E[H\E[2J"));
    close(term);

    return 0;
}

int main(){
    mt_clrscr();
    return 0;
}
