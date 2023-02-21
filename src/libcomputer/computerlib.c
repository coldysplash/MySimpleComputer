#include <libcomputer/computerlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int sc_ram[memorysize]; // memory

int sc_commands[] = {
        10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43, 51,
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
        65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
};
#define MASK_DECODE_COMMAND 0x7f

//Флаги
static int flag_reg;
#define FLAG_OVERFLOW 1 // переполнение при выполнении операции
#define FLAG_ERR_DIV_BY_ZERO 2 // ошибка деления на ноль
#define FLAG_WRONG_ADDRESS 3 // ошибка выхода за границы памяти 
#define FLAG_IGNOR_TEXT_IMPULS 4 // игнорирование текстовых импульсов 
#define FLAG_WRONG_COMMAND 5 // указана неверная команда


// инициализация оперативной памяти Sipmle Computer
int sc_memoryInit(){
    memset(sc_ram, 0, sizeof(sc_ram));

    return 0;
}

//sc_memorySet - задает значение указанной ячейки памяти как value
int sc_memorySet(int address, int value){
    if(address >= 0 || address < memorysize){
        sc_ram[address] = value;
    }else{
        sc_regSet(FLAG_WRONG_ADDRESS, 1);
        return -1;
    }
    return 0;
}

//sc_memoryGet – возвращает значение указанной ячейки памяти в value.
int sc_memoryGet(int address, int *value){
    if(address >= 0 || address < memorysize){
        *value = sc_ram[address];
    }else{
        sc_regSet(FLAG_WRONG_ADDRESS, 1);
        return -1;
    }
    return 0;
}

// sc_memorySave - сохраняет содержимое памяти в файл в бинарном виде
int sc_memorySave(char *filename){
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        fclose(file);
        return -1;
    }

    fwrite(sc_ram, sizeof(int), 100, file);

    fclose(file);

    return 0;
}

//sc_memoryLoad – загружает из указанного файла содержимое оперативной памяти
int sc_memoryLoad(char *filename){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        fclose(file);
        return -1;
    }

    fread(sc_ram, sizeof(int), 100, file);

    fclose(file);

    return 0;
}

//sc_regInit – инициализирует регистр флагов нулевым значением
int sc_regInit(){
    flag_reg = 0;
    return 0;
}

//sc_regSet - устанавливает значение указанного регистра флагов
int sc_regSet(int reg, int value){
    if (reg < 1 || reg > 5 || (value != 0 && value != 1)){
        return -1;
    }

    if(value == 1){
        flag_reg = flag_reg | (1 << (reg - 1));
    }else{
        flag_reg = flag_reg & (~(1 << (reg - 1)));
    }

    return 0;
}

//sc_regGet – возвращает значение указанного флага
int sc_regGet(int reg, int *value){
    if (reg < 1 || reg > 5){
        return -1;
    }

    flag_reg = (flag_reg >> (reg - 1)) & 0x1;

    *value = flag_reg;

    return 0;
}

//sc_commandEncode - кодирует команду с указанным номером и операндом и помещает результат в value 
int sc_commandEncode(int command, int operand, int *value){
    bool flag_command = false;
    for(int i = 0; i < 38; i++){
        if (command == sc_commands[i]){
            flag_command = true;
        }
    }
    if(flag_command == false || (operand < 0 || operand > 128)){
        return -1;
    }

    *value = 0x0;
    *value = command << 7;
    *value = *value | operand;

    return 0;

}

// sc_commandDecode - декодирует значение как команду Simple Computer.
int sc_commadDecode(int value, int *command, int *operand){
    if(command == NULL || operand == NULL){
        sc_regSet(FLAG_WRONG_COMMAND, 1);
        return -1;
    }

    *operand = *command = 0x0;

    *operand = value & MASK_DECODE_COMMAND;
    value >>= 7;
    *command = value;

    return 0;
}

void print_memory(){
    for(int i = 0; i < 100; i++){
        if (i % 20 == 0 && i != 0) {
            printf("\n");
        }
        printf("%3d ", sc_ram[i]);
    }
    printf("\n");
}
