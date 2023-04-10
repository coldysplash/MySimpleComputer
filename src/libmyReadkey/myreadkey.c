#include <fcntl.h>
#include <libcomputer/computerlib.h>
#include <libmyReadkey/myreadkey.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define F5_KEY "\E[15~"
#define F6_KEY "\E[17~"
#define DOWN_KEY "\E[B"
#define UP_KEY "\E[A"
#define LEFT_KEY "\E[D"
#define RIGHT_KEY "\E[C"
#define ENTER_KEY "\n"

int
rk_readkey (enum keys *k)
{

  struct termios;
  tcgetattr(0, &termios);
  termios->c_lflag &= ~(ICANON | ISIG);
  tcsetattr(0, TCSANOW, &termios);

  char buf[32];
  read(0, buf, sizeof(buff));

  if(buf == 'l'){
    *k = LOAD;
  }else if(buf == 's'){
    *k = SAVE;
  }else if(buf == 'r'){
    *k = RUN;
  }else if(buf == 't'){
    *k = STEP;
  }else if(buf == 'i'){
    *k = RESET;
  }else if(buf == F5_KEY){
    *k = F5;
  }else if(buf == F6_KEY){
    *k = F6;
  }else if(buf == DOWN_KEY){
    *k = DOWN;
  }else if(buf == UP_KEY){
    *k = UP;
  }else if(buf == LEFT_KEY){
    *k = LEFT;
  }else if(buf == RIGHT_KEY){
    *k = RIGHT;
  }else if(buf == ENTER_KEY){
    *k = ENTER;
  }else{
    *k = OTHER;
  }

  return 0;

}
