#include <MySimpleComputerApp/CPU.h>
#include <MySimpleComputerApp/interface.h>
#include <fcntl.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyReadkey/myreadkey.h>
#include <libmyTerm/myTerm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  if (isatty(0) == 0 || isatty(1) == 0) {
    fprintf(stderr, "Error!\n");
    return -1;
  }

  CPU();

  return 0;
}