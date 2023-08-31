#pragma once

#include <MySimpleComputerApp/ALU.h>
extern int accumulator;

void output_accumulator();
void output_instructionCounter();
int output_operation();
void output_flags();
int output_BigChars();
void output_SimpleComputer();
void reset_SimpleComputer();
int handler_keys();
void CU_run();
int CU();

void CPU();