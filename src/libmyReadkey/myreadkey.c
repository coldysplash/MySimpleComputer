#include <libcomputer/computerlib.h>
#include <libmyReadkey/myreadkey.h>
#include <libmyTerm/myTerm.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#define F5_KEY "\E[15~"
#define F6_KEY "\E[17~"
#define DOWN_KEY "\E[B"
#define UP_KEY "\E[A"
#define LEFT_KEY "\E[D"
#define RIGHT_KEY "\E[C"
#define ENTER_KEY "\n"

int rk_readkey(enum keys *k) {
  char buf[32];
  read(0, buf, sizeof(buf));

  if (strcmp(buf, "l") == 0) {
    *k = LOAD;
  } else if (strcmp(buf, "s") == 0) {
    *k = SAVE;
  } else if (strcmp(buf, "r") == 0) {
    *k = RUN;
  } else if (strcmp(buf, "t") == 0) {
    *k = STEP;
  } else if (strcmp(buf, "i") == 0) {
    *k = RESET;
  } else if (strcmp(buf, F5_KEY) == 0) {
    *k = F5;
  } else if (strcmp(buf, F6_KEY) == 0) {
    *k = F6;
  } else if (strcmp(buf, DOWN_KEY) == 0) {
    *k = DOWN;
  } else if (strcmp(buf, UP_KEY) == 0) {
    *k = UP;
  } else if (strcmp(buf, LEFT_KEY) == 0) {
    *k = LEFT;
  } else if (strcmp(buf, RIGHT_KEY) == 0) {
    *k = RIGHT;
  } else if (strcmp(buf, ENTER_KEY) == 0) {
    *k = ENTER;
  } else {
    *k = OTHER;
  }

  return 0;
}
int rk_mytermsave() {
  struct termios term_set;
  FILE *file;

  if (tcgetattr(TCSANOW, &term_set) != 0) {
    return -1;
  }
  if ((file = fopen("termsettings", "wb")) == NULL) {
    return -1;
  }
  fwrite(&term_set, sizeof(term_set), 1, file);

  fclose(file);

  return 0;
}

int rk_mytermrestore() {
  struct termios term_set;
  FILE *file;

  if ((file = fopen("termsettings", "rb")) == NULL) {
    return -1;
  }
  if (fread(&term_set, sizeof(term_set), 1, file) <= 0) {
    return -1;
  }
  if (tcsetattr(0, TCSANOW, &term_set) != 0) {
    return -1;
  }

  return 0;
}

int rk_mytermregime(int regime, int vtime, int vmin, int echo, int sigint) {

  struct termios term_set;

  tcgetattr(0, &term_set);

  if (regime == 1) {
    term_set.c_lflag |= ICANON;
  } else if (regime == 0) {
    term_set.c_lflag &= ~ICANON;
    term_set.c_cc[VTIME] = vtime;
    term_set.c_cc[VMIN] = vmin;
  } else {
    return -1;
  }

  if (echo == 1) {
    term_set.c_lflag |= ECHO;
  } else if (echo == 0) {
    term_set.c_lflag &= ~ECHO;
  } else {
    return -1;
  }

  if (sigint == 1) {
    term_set.c_lflag |= ISIG;
  } else if (sigint == 0) {
    term_set.c_lflag &= ~ISIG;
  } else {
    return -1;
  }

  tcsetattr(0, TCSANOW, &term_set);

  return 0;
}
