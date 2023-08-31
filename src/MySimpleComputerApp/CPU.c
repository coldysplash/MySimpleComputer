#include <MySimpleComputerApp/ALU.h>
#include <MySimpleComputerApp/CPU.h>
#include <MySimpleComputerApp/interface.h>
#include <fcntl.h>
#include <libcomputer/computerlib.h>
#include <libmyBigChars/myBigChars.h>
#include <libmyReadkey/myreadkey.h>
#include <libmyTerm/myTerm.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

int bc_PLUS[2] = {0xFF181818, 0x181818FF};
int bc_MINUS[2] = {0xFF000000, 0x000000FF};
int bc_NULL[2] = {0x8181817e, 0x7e818181};
int bc_ONE[2] = {0x8890A0C0, 0x80808080};
int bc_TWO[2] = {0x2040827C, 0xFE040810};
int bc_THREE[2] = {0x6080817E, 0x7E818060};
int bc_FOUR[2] = {0xFF818181, 0x80808080};
int bc_FIVE[2] = {0x7F0101FF, 0x7F808080};
int bc_SIX[2] = {0x0101817E, 0x7E81817F};
int bc_SEVEN[2] = {0x204080FE, 0x02040810};
int bc_EIGHT[2] = {0x7E81817E, 0x7E818181};
int bc_NINE[2] = {0x7E81817E, 0x7E808080};
int bc_A[2] = {0x7E42423C, 0x42424242};
int bc_B[2] = {0x3E42423E, 0x3E424242};
int bc_C[2] = {0x0101017E, 0x7E010101};
int bc_D[2] = {0x4242221E, 0x1E224242};
int bc_E[2] = {0x7E02027E, 0x7E020202};
int bc_F[2] = {0x7E02027E, 0x02020202};

int *bc_NUMS[16] = {bc_NULL, bc_ONE,   bc_TWO,   bc_THREE, bc_FOUR, bc_FIVE,
                    bc_SIX,  bc_SEVEN, bc_EIGHT, bc_NINE,  bc_A,    bc_B,
                    bc_C,    bc_D,     bc_E,     bc_F};

int cursor = 0;
int instructionCounter = 0;
int accumulator = 0;

void output_accumulator() {
  char buff[7];
  int command, operand;
  sc_commandDecode(accumulator & 0x3FFF, &command, &operand);

  snprintf(buff, 7, "%c%02X%02X ", (accumulator & 0x4000) ? '-' : '+', command,
           operand);

  mt_gotoXY(2, 74);
  write(1, buff, 6);
}

void output_instructionCounter() {
  char buff[7];
  snprintf(buff, 6, "+%04X", instructionCounter);
  mt_gotoXY(5, 72);
  write(1, buff, 6);
}

int output_operation() {
  char buff[9];
  int value, command, operand;

  if (sc_memoryGet(instructionCounter, &value) < 0 ||
      sc_commandDecode(value & 0x3FFF, &command, &operand) < 0)
    return -1;

  if (sc_commandEncode(command, operand, &value) == -1) {
    command = 0;
    operand = 0;
  } else {
    sc_regSet(FLAG_WRONG_COMMAND, 0);
  }

  snprintf(buff, 9, "%c%02X : %02X", '+', command, operand);

  mt_gotoXY(8, 70);
  write(1, buff, 9);

  return 0;
}

void output_flags() {
  int value;

  mt_gotoXY(11, 70);
  sc_regGet(FLAG_OVERFLOW, &value);
  write(1, ((value) ? "P" : ""), 1);

  mt_gotoXY(11, 73);
  sc_regGet(FLAG_ERR_DIV_BY_ZERO, &value);
  write(1, ((value) ? "O" : ""), 1);

  mt_gotoXY(11, 76);
  sc_regGet(FLAG_WRONG_ADDRESS, &value);
  write(1, ((value) ? "M" : ""), 1);

  mt_gotoXY(11, 79);
  sc_regGet(FLAG_IGNOR_TACT_IMPULS, &value);
  write(1, ((value) ? "T" : ""), 1);

  mt_gotoXY(11, 82);
  sc_regGet(FLAG_WRONG_COMMAND, &value);
  write(1, ((value) ? "E" : ""), 1);
}

int output_BigChars() {
  int value, command, operand;

  if (sc_memoryGet(cursor, &value) < 0 ||
      sc_commandDecode(value & 0x3FFF, &command, &operand) < 0)
    return -1;

  (value & 0x4000) ? bc_printbigchar(bc_MINUS, 15, 2, White, Black)
                   : bc_printbigchar(bc_PLUS, 15, 2, White, Black);

  bc_printbigchar(bc_NUMS[(command >> 4) % 16], 15, 11, White, Black);
  bc_printbigchar(bc_NUMS[(command & 0xf) % 16], 15, 20, White, Black);
  bc_printbigchar(bc_NUMS[(operand >> 4) & 0xf % 16], 15, 29, White, Black);
  bc_printbigchar(bc_NUMS[(operand & 0xf) % 16], 15, 38, White, Black);

  return 0;
}

void output_SimpleComputer() {
  mt_clrscr();
  print_interface();
  // print memory
  for (int i = 0; i < 100; i++) {
    print_cell(i, cursor);
    mt_setbgcolor(Black);
  }
  output_accumulator();
  output_instructionCounter();
  output_operation();
  output_flags();
  output_BigChars();
  mt_gotoXY(26, 1);
}

void reset_SimpleComputer() {
  sc_memoryInit();
  sc_regSet(FLAG_IGNOR_TACT_IMPULS, 1);
  sc_regSet(FLAG_OVERFLOW, 0);
  sc_regSet(FLAG_ERR_DIV_BY_ZERO, 0);
  sc_regSet(FLAG_WRONG_ADDRESS, 0);
  sc_regSet(FLAG_WRONG_COMMAND, 0);
  instructionCounter = 0;
  accumulator = 0;
  cursor = 0;
}

int handler_keys() {
  enum keys k;

  rk_mytermregime(0, 0, 1, 0, 1);

  rk_readkey(&k);

  if (k == RESET) {
    reset_SimpleComputer();
  } else if (k == RUN) {
    sc_regSet(FLAG_IGNOR_TACT_IMPULS, 0);
    output_SimpleComputer();
  } else if (k == STEP) {
    CU();
    alarm(0);
    instructionCounter++;
  } else if (k == UP) {
    if (cursor > 9 && cursor < 100) {
      cursor -= 10;
    }
  } else if (k == DOWN) {
    if (cursor >= 0 && cursor <= 89) {
      cursor += 10;
    }
  } else if (k == LEFT) {
    if (cursor > 0 && cursor < 100) {
      cursor--;
    }
  } else if (k == RIGHT) {
    if (cursor >= 0 && cursor < 99) {
      cursor++;
    }
  }

  if (k == ENTER || k == F5 || k == F6 || k == LOAD || k == SAVE) {

    rk_mytermregime(1, 0, 0, 1, 1);

    char buf[12] = {};

    mt_gotoXY(25, 1);
    write(0, "Input/Output:", 14);
    mt_gotoXY(26, 1);
    write(0, ">", 2);

    if (k == ENTER) {
      read(1, buf, 12);
      int minus_flag = 0;
      if (buf[0] == '-') {
        minus_flag = 1;
        buf[0] = '0';
      }
      int actual_num = (int)atoi(buf);
      if (minus_flag == 1) {
        actual_num |= 0x4000;
      }
      if (actual_num <= 65535) {
        sc_memorySet(cursor, actual_num);
      } else {
        return -1;
      }
    } else if (k == F5) {
      read(1, buf, sizeof(buf));
      int minus_flag = 0;
      if (buf[0] == '-') {
        minus_flag = 1;
        buf[0] = '0';
      }
      int tmp_accum = (int)atoi(buf);
      if (minus_flag == 1) {
        tmp_accum |= 0x4000;
      }
      if (tmp_accum <= 65535) {
        accumulator = tmp_accum;
      }
    } else if (k == F6) {
      read(1, buf, sizeof(buf));
      int new_ic = (int)atoi(buf);
      if (new_ic >= 0 && new_ic < 99) {
        instructionCounter = new_ic;
      }
      cursor = instructionCounter;
    } else if (k == LOAD) {
      read(1, buf, 12);
      buf[strlen(buf) - 1] = '\0';
      sc_memoryLoad(buf);
    } else if (k == SAVE) {
      read(1, buf, 12);
      buf[strlen(buf) - 1] = '\0';
      sc_memorySave(buf);
    }
  }

  return 0;
}

int CU() {

  int check_flag_wrong_command = 0;
  int memory_cell = 0, command = 0, operand = 0;
  cursor = instructionCounter;

  struct itimerval nval, oval;

  nval.it_interval.tv_sec = 1.5;
  nval.it_interval.tv_usec = 0;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;

  sc_regGet(FLAG_WRONG_COMMAND, &check_flag_wrong_command);
  if (check_flag_wrong_command == 1) {
    return -1;
  }

  sc_memoryGet(instructionCounter, &memory_cell);

  sc_commandDecode(memory_cell & 0x3FFF, &command, &operand);

  if (sc_commandEncode(command, operand, &memory_cell) == -1) {
    sc_regSet(FLAG_WRONG_COMMAND, 1);
    return -1;
  }

  if (command == 30 || command == 31 || command == 32 || command == 33) {
    ALU(command, operand);
  }

  if (command == 10) { /*READ*/

    if (operand < 0 && operand > 99) {
      sc_regSet(FLAG_WRONG_ADDRESS, 1);
      return -1;
    }

    rk_mytermregime(1, 0, 0, 1, 1);
    mt_gotoXY(25, 1);
    write(0, "Input/Output:", 14);
    mt_gotoXY(26, 1);
    write(0, ">", 2);

    char buf[12];
    alarm(0);

    read(1, buf, 12);
    int minus_flag = 0;
    if (buf[0] == '-') {
      minus_flag = 1;
      buf[0] = '0';
    }
    int actual_num = (int)atoi(buf);
    if (minus_flag == 1) {
      actual_num |= 0x4000;
    }
    if (actual_num <= 65535) {
      sc_memorySet(operand, actual_num);
      setitimer(ITIMER_REAL, &nval, &oval);
    } else {
      return -1;
    }
  } else if (command == 11) { /*WRITE*/

    mt_gotoXY(25, 1);
    write(1, "Output:", 8);
    char buff[8];
    int val;

    if (operand >= 0 && operand <= 99) {
      sc_memoryGet(operand, &val);
    } else {
      sc_regSet(FLAG_WRONG_ADDRESS, 1);
      return -1;
    }
    sc_commandDecode(val & 0x3FFF, &command, &operand);

    snprintf(buff, 8, ">%c%02X%02X ", (val & 0x4000) ? '-' : '+', command,
             operand);

    mt_gotoXY(26, 1);
    write(1, buff, 7);

    sleep(1);
  } else if (command == 20) { /*LOAD*/
    if (operand >= 0 && operand <= 99) {
      sc_memoryGet(operand, &accumulator);
    } else {
      sc_regSet(FLAG_WRONG_ADDRESS, 1);
      return -1;
    }
  } else if (command == 21) { /*STORE*/
    if (operand >= 0 && operand <= 99) {
      sc_memorySet(operand, accumulator);
    } else {
      sc_regSet(FLAG_WRONG_ADDRESS, 1);
      return -1;
    }
  } else if (command == 40) { /*JUMP*/
    if (operand >= 0 && operand <= 99) {
      instructionCounter = operand - 1;
      cursor = instructionCounter;
    } else {
      sc_regSet(FLAG_WRONG_ADDRESS, 1);
      return -1;
    }
  } else if (command == 41) { /*JNEG*/

    if (accumulator & 0x4000) {
      if (operand >= 0 && operand <= 99) {
        instructionCounter = operand - 1;
        cursor = instructionCounter;
        return 0;
      } else {
        sc_regSet(FLAG_WRONG_ADDRESS, 1);
        return -1;
      }
    }
    return 0;
  } else if (command == 42) { /*JZ*/
    if (accumulator == 0) {
      if (operand >= 0 && operand <= 99) {
        instructionCounter = operand - 1;
        cursor = instructionCounter;
        return 0;
      } else {
        sc_regSet(FLAG_WRONG_ADDRESS, 1);
        return -1;
      }
    }
    // return 0;
  } else if (command == 43) { /*HALT*/
    return 1;
  } else if (command == 74) { /*MOVCR(пользовательская функция)*/
    if (accumulator >= 0 && accumulator <= 99) {
      sc_memorySet(accumulator, memory_cell);
    }
  }

  return 0;
}

void CU_run() {
  if (instructionCounter <= 99) {
    if (CU() == 0) {
      output_SimpleComputer();
      instructionCounter++;
    } else {
      sc_regSet(FLAG_IGNOR_TACT_IMPULS, 1);
      output_SimpleComputer();
      alarm(0);
    }
  } else {
    raise(SIGUSR1);
    alarm(0);
  }
}

void CPU() {
  int flag_ignor_tact_impuls;

  sc_regInit();
  sc_memoryInit();
  sc_regSet(FLAG_IGNOR_TACT_IMPULS, 1);

  struct itimerval nval, oval;

  nval.it_interval.tv_sec = 1.5;
  nval.it_interval.tv_usec = 0;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;

  signal(SIGALRM, CU_run);
  signal(SIGUSR1, reset_SimpleComputer);

  while (1) {
    sc_regGet(FLAG_IGNOR_TACT_IMPULS, &flag_ignor_tact_impuls);

    if (flag_ignor_tact_impuls == 1) {
      output_SimpleComputer();
      handler_keys();
    } else {
      setitimer(ITIMER_REAL, &nval, &oval);
      sleep(1);
    }
  }
}