#include <libcomputer/computerlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define memorysize 100
int sc_ram[memorysize]; // memory

int sc_commands[] = { 10, 11, 20, 21, 30, 31, 32, 33, 40, 41, 42, 43 };

#define MASK_DECODE_COMMAND 0x7f
static int flag_reg;

// инициализация оперативной памяти Sipmle Computer
int
sc_memoryInit ()
{
  memset (sc_ram, 0, sizeof (sc_ram));

  return 0;
}

// sc_memorySet - задает значение указанной ячейки памяти как value
int
sc_memorySet (int address, int value)
{
  if (address < 0 || address > memorysize)
    {
      sc_regSet (FLAG_WRONG_ADDRESS, 1);
      return -1;
    }
  sc_ram[address] = value;
  return 0;
}

// sc_memoryGet – возвращает значение указанной ячейки памяти в value.
int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address > memorysize)
    {
      sc_regSet (FLAG_WRONG_ADDRESS, 1);
      return -1;
    }
  *value = sc_ram[address];
  return 0;
}

// sc_memorySave - сохраняет содержимое памяти в файл в бинарном виде
int
sc_memorySave (char *filename)
{
  FILE *file = fopen (filename, "w");
  if (file == NULL)
    {
      fclose (file);
      return -1;
    }

  fwrite (sc_ram, sizeof (int), 100, file);

  fclose (file);

  return 0;
}

// sc_memoryLoad – загружает из указанного файла содержимое оперативной памяти
int
sc_memoryLoad (char *filename)
{
  FILE *file = fopen (filename, "r");
  if (file == NULL)
    {
      fclose (file);
      return -1;
    }

  fread (sc_ram, sizeof (int), 100, file);

  fclose (file);

  return 0;
}

// sc_regInit – инициализирует регистр флагов нулевым значением
int
sc_regInit ()
{
  flag_reg = 0;
  return 0;
}

// sc_regSet - устанавливает значение указанного регистра флагов
int
sc_regSet (int reg, int value)
{
  if (reg < 1 || reg > 5 || (value != 0 && value != 1))
    {
      return -1;
    }

  if (value == 1)
    {
      flag_reg = flag_reg | (1 << (reg - 1));
    }
  else
    {
      flag_reg = flag_reg & (~(1 << (reg - 1)));
    }

  return 0;
}

// sc_regGet – возвращает значение указанного флага
int
sc_regGet (int reg, int *value)
{
  if (reg < 1 || reg > 5)
    {
      return -1;
    }

  *value = (flag_reg >> (reg - 1)) & 0x1;

  return 0;
}

// sc_commandEncode - кодирует команду с указанным номером и операндом и
// помещает результат в value
int
sc_commandEncode (int command, int operand, int *value)
{
  bool flag_command = false;
  for (int i = 0; i < 12; i++)
    {
      if (command == sc_commands[i])
        {
          flag_command = true;
        }
    }
  if (flag_command == false || (operand < 0 || operand > 128))
    {
      return -1;
    }

  *value = 0x0;
  *value = command << 7;
  *value = *value | operand;

  return 0;
}

// sc_commandDecode - декодирует значение как команду Simple Computer.
int
sc_commandDecode (int value, int *command, int *operand)
{
  if (command == NULL || operand == NULL)
    {
      sc_regSet (FLAG_WRONG_COMMAND, 1);
      return -1;
    }

  *operand = *command = 0x0;

  *operand = value & MASK_DECODE_COMMAND;
  value >>= 7;
  *command = value;

  return 0;
}