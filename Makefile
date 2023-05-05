CC = gcc
FLAGS = -Wall -Wextra -Werror

APP_NAME = MySimpleComputer

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

BC_DIR = $(SRC_DIR)/libmyBigChars
COMPLIB_DIR = $(SRC_DIR)/libcomputer
TERM_DIR = $(SRC_DIR)/libmyTerm
MAIN_DIR = $(SRC_DIR)/MySimpleComputerApp
READKEY_DIR = $(SRC_DIR)/libmyReadkey

OBJ_SRC_DIR = $(OBJ_DIR)/$(SRC_DIR)

APP_PATH = $(BIN_DIR)/$(APP_NAME)

LIB_COMPUTER_PATH = $(LIB_DIR)/libmySimpleComputer.a
LIB_TERM_PATH = $(LIB_DIR)/libmyTerm.a
LIB_BC_PATH = $(LIB_DIR)/libmyBigChars.a
LIB_READKEY_PATH = $(LIB_DIR)/libmyreadkey.a

PROJECT_SOURCES = $(MAIN_DIR)/main.c $(COMPLIB_DIR)/computerlib.c $(TERM_DIR)/myTerm.c $(BC_DIR)/myBigChars.c $(READKEY_DIR)/myreadkey.c $(MAIN_DIR)/interface.c $(MAIN_DIR)/CPU.c $(MAIN_DIR)/ALU.c
PROJECT_OBJECTS = $(OBJ_SRC_DIR)/main.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(OBJ_SRC_DIR)/myreadkey.o $(OBJ_SRC_DIR)/interface.o $(OBJ_SRC_DIR)/CPU.o $(OBJ_SRC_DIR)/ALU.o

.PHONY: all mkdir

all: mkdir $(APP_PATH)

mkdir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_SRC_DIR)
	mkdir -p $(LIB_DIR)

$(APP_PATH) : $(PROJECT_OBJECTS) $(LIB_COMPUTER_PATH) $(LIB_TERM_PATH) $(LIB_BC_PATH) $(LIB_READKEY_PATH)
	$(CC) $(FLAGS) $^ -o $@

$(LIB_COMPUTER_PATH) : $(OBJ_SRC_DIR)/computerlib.o
	ar rc $@ $^

$(LIB_TERM_PATH) : $(OBJ_SRC_DIR)/myTerm.o
	ar rc $@ $^

$(LIB_BC_PATH) : $(OBJ_SRC_DIR)/myBigChars.o
	ar rc $@ $^

$(LIB_READKEY_PATH) : $(OBJ_SRC_DIR)/myreadkey.o
	ar rc $@ $^

$(PROJECT_OBJECTS): $(PROJECT_SOURCES)
	$(CC) $(FLAGS) -I src -c $(MAIN_DIR)/main.c -o $(OBJ_SRC_DIR)/main.o
	$(CC) $(FLAGS) -I src -c $(COMPLIB_DIR)/computerlib.c -o $(OBJ_SRC_DIR)/computerlib.o
	$(CC) $(FLAGS) -I src -c $(TERM_DIR)/myTerm.c -o $(OBJ_SRC_DIR)/myTerm.o
	$(CC) $(FLAGS) -I src -c $(BC_DIR)/myBigChars.c -o $(OBJ_SRC_DIR)/myBigChars.o
	$(CC) $(FLAGS) -I src -c $(READKEY_DIR)/myreadkey.c -o $(OBJ_SRC_DIR)/myreadkey.o
	$(CC) $(FLAGS) -I src -c $(MAIN_DIR)/interface.c -o $(OBJ_SRC_DIR)/interface.o
	$(CC) $(FLAGS) -I src -c $(MAIN_DIR)/ALU.c -o $(OBJ_SRC_DIR)/ALU.o
	$(CC) $(FLAGS) -I src -c $(MAIN_DIR)/CPU.c -o $(OBJ_SRC_DIR)/CPU.o 

run: $(APP_PATH)
	$(APP_PATH)

.PHONY: clean

clean:
	rm -rf obj bin lib
