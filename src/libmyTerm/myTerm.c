#include <libmyTerm/myTerm.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define TERM_PATH "/dev/tty"
int mt_getscreensize(int *rows, int *cols);

// mt_clrscr - производит очистку и перемещение курсора 
//             в левый верхний угол экрана
int mt_clrscr(){
    int term = open(TERM_PATH, O_WRONLY);

    if(term == -1){
        return -1;
    }

    write(term, "\E[H\E[J", sizeof("\E[H\E[J"));
    close(term);

    return 0;
}

// mt_gotoXY - перемещает курсор в указанную позицию
int mt_gotoXY(int x, int y){
    int row, col;
    mt_getscreensize(&row, &col);

    if (((x > col) || (x < 0)) || ((y > row) || (y < 0))) {
        return -1;
    }

    char buff[50];
    sprintf(buff, "\E[%d;%dH", y, x);

    int term = open(TERM_PATH, O_RDWR);
    if (term == -1) {
        return -1;
    }
    write(term, buff, strlen(buff));
    close(term);
    return 0;
}

// mt_getscreensize - определяет размер 
//                    экрана терминала 

int mt_getscreensize(int *rows, int *cols){
    struct winsize ws;

    if (rows == NULL || cols == NULL ||
        ioctl(0, TIOCGWINSZ, &ws)) {
        return -1;
    }

    *rows = ws.ws_row;
    *cols = ws.ws_col;

    return 0;
}

// int main(){
//     mt_gotoXY(10,10);
//     return 0;
// }