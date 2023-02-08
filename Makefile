CC = gcc
FLAGS = -Wall -Wextra -Werror

SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj
EXE_DIR = bin

COMPLIB_DIR = $(SRC_DIR)/libcomputer
MAIN_DIR = $(SRC_DIR)/app

OBJ_SRC_DIR = $(OBJ_DIR)/$(SRC_DIR)
OBJ_TEST_DIR = $(OBJ_DIR)/$(TEST_DIR)

# .PHONY: computerlib.o main.o app all

all: computerlib.o main.o app

app : $(OBJ_SRC_DIR)/main.o $(OBJ_SRC_DIR)/computerlib.o 
	$(CC) $(FLAGS) -o $(EXE_DIR)/$@ $^

main.o : $(MAIN_DIR)/main.c 
	$(CC) -I src -c $(FLAGS) -o $(OBJ_SRC_DIR)/$@ $<

computerlib.o : $(COMPLIB_DIR)/computerlib.c
	$(CC) -I src -c $(FLAGS) -o $(OBJ_SRC_DIR)/$@ $<

run: $(EXE_DIR)/app
	$(EXE_DIR)/app

clean:
	rm -rf obj/src/* bin/* 