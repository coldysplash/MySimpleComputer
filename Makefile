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

.PHONY: app all

all: computerlib.o main.o app libmySimpleComputer.a

app : $(OBJ_SRC_DIR)/main.o $(OBJ_SRC_DIR)/computerlib.o libmySimpleComputer.a
	$(CC) $(FLAGS) -L. -lmySimpleComputer -o $(EXE_DIR)/$@ $^

libmySimpleComputer.a : $(OBJ_SRC_DIR)/computerlib.o
	ar rc libmySimpleComputer.a $(OBJ_SRC_DIR)/computerlib.o

main.o : $(MAIN_DIR)/main.c
	$(CC) -I src -c $(FLAGS) -o $(OBJ_SRC_DIR)/$@ $<

computerlib.o : $(COMPLIB_DIR)/computerlib.c
	$(CC) -I src -c $(FLAGS) -o $(OBJ_SRC_DIR)/$@ $<

run: $(EXE_DIR)/app
	$(EXE_DIR)/app

# TEST

.PHONY: all test

test: all test.o main_test.o test_app 

test_app: $(OBJ_TEST_DIR)/test.o $(OBJ_TEST_DIR)/main_test.o $(OBJ_SRC_DIR)/computerlib.o libmySimpleComputer.a
	$(CC) $(FLAGS) -L. -lmySimpleComputer -o $(EXE_DIR)/$@ $^

main_test.o: $(TEST_DIR)/main.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $(OBJ_TEST_DIR)/$@ $<

test.o: $(TEST_DIR)/tests.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $(OBJ_TEST_DIR)/$@ $<

test_run: $(EXE_DIR)/test_app
	$(EXE_DIR)/test_app


clean:
	rm -rf obj/src/* bin/* 
