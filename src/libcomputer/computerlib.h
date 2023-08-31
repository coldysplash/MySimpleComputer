#pragma once

//Флаги
#define FLAG_OVERFLOW 1 // переполнение при выполнении операции
#define FLAG_ERR_DIV_BY_ZERO 2 // ошибка деления на ноль
#define FLAG_WRONG_ADDRESS 3 // ошибка выхода за границы памяти
#define FLAG_IGNOR_TACT_IMPULS 4 // игнорирование тактовых импульсов
#define FLAG_WRONG_COMMAND 5 // указана неверная команда

int sc_memoryInit();
int sc_memorySet(int address, int value);
int sc_memoryGet(int address, int *value);
int sc_memorySave(char *filename);
int sc_memoryLoad(char *filename);
int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int *value);
int sc_commandEncode(int command, int operand, int *value);
int sc_commandDecode(int value, int *command, int *operand);
