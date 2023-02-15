CC = gcc
FLAGS = -Wall -Wextra -Werror

APP_NAME = MySimpleComputer
TEST_NAME = test

SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

COMPLIB_DIR = $(SRC_DIR)/libcomputer
MAIN_DIR = $(SRC_DIR)/app

OBJ_SRC_DIR = $(OBJ_DIR)/$(SRC_DIR)
OBJ_TEST_DIR = $(OBJ_DIR)/$(TEST_DIR)

APP_PATH = $(BIN_DIR)/$(APP_NAME)
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)

.PHONY: all

all: $(APP_PATH)

$(APP_PATH) : $(OBJ_SRC_DIR)/main.o $(OBJ_SRC_DIR)/computerlib.o $(LIB_DIR)/libmySimpleComputer.a
	$(CC) $(FLAGS) $^ -o $@

$(LIB_DIR)/libmySimpleComputer.a : $(OBJ_SRC_DIR)/computerlib.o
	ar rc $@ $^

$(OBJ_SRC_DIR)/main.o : $(MAIN_DIR)/main.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/computerlib.o : $(COMPLIB_DIR)/computerlib.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

run: $(APP_PATH)
	$(APP_PATH)

# TEST
.PHONY: test

test: $(TEST_PATH)

$(TEST_PATH) : $(OBJ_TEST_DIR)/test.o $(OBJ_TEST_DIR)/main_test.o $(OBJ_SRC_DIR)/computerlib.o $(LIB_DIR)/libmySimpleComputer.a
	$(CC) $(FLAGS) $^ -o $@

main_test.o: $(TEST_DIR)/main.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $(OBJ_TEST_DIR)/$@ $<

test.o: $(TEST_DIR)/tests.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $(OBJ_TEST_DIR)/$@ $<

test_run: $(TEST_PATH)
	$(TEST_PATH)

.PHONY: clean

clean:
	rm -rf obj/src/* bin/*
