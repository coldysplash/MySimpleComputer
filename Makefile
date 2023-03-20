CC = gcc
FLAGS = -Wall -Wextra -Werror

APP_NAME = MySimpleComputer
TEST_NAME = test

SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

BC_DIR = $(SRC_DIR)/libmyBigChars
COMPLIB_DIR = $(SRC_DIR)/libcomputer
TERM_DIR = $(SRC_DIR)/libmyTerm
MAIN_DIR = $(SRC_DIR)/app

OBJ_SRC_DIR = $(OBJ_DIR)/$(SRC_DIR)
OBJ_TEST_DIR = $(OBJ_DIR)/$(TEST_DIR)

APP_PATH = $(BIN_DIR)/$(APP_NAME)
TEST_PATH = $(BIN_DIR)/$(TEST_NAME)
LIB_COMPUTER_PATH = $(LIB_DIR)/libmySimpleComputer.a
LIB_TERM_PATH = $(LIB_DIR)/libmyTerm.a
LIB_BC_PATH = $(LIB_DIR)/libmyBigChars.a

.PHONY: all mkdir

all: mkdir $(APP_PATH)

mkdir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_SRC_DIR)
	mkdir -p $(OBJ_TEST_DIR)
	mkdir -p $(LIB_DIR)

$(APP_PATH) : $(OBJ_SRC_DIR)/main.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(OBJ_SRC_DIR)/interface.o $(LIB_COMPUTER_PATH) $(LIB_TERM_PATH) $(LIB_BC_PATH)
	$(CC) $(FLAGS) $^ -o $@

$(LIB_COMPUTER_PATH) : $(OBJ_SRC_DIR)/computerlib.o
	ar rc $@ $^

$(LIB_TERM_PATH) : $(OBJ_SRC_DIR)/myTerm.o
	ar rc $@ $^

$(LIB_BC_PATH) : $(OBJ_SRC_DIR)/myBigChars.o
	ar rc $@ $^

$(OBJ_SRC_DIR)/main.o : $(MAIN_DIR)/main.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/interface.o : $(MAIN_DIR)/interface.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/computerlib.o : $(COMPLIB_DIR)/computerlib.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/myTerm.o : $(TERM_DIR)/myTerm.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/myBigChars.o : $(BC_DIR)/myBigChars.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

run: $(APP_PATH)
	$(APP_PATH)

# TEST

.PHONY: test

test: $(TEST_PATH)

$(TEST_PATH) : $(OBJ_TEST_DIR)/test.o $(OBJ_TEST_DIR)/main_test.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(LIB_COMPUTER_PATH) $(LIB_TERM_PATH) $(LIB_BC_PATH)
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_TEST_DIR)/main_test.o : $(TEST_DIR)/main.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $@ $<

$(OBJ_TEST_DIR)/test.o : $(TEST_DIR)/tests.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $@ $<

testrun: $(TEST_PATH)
	$(TEST_PATH)

.PHONY: clean

clean:
	rm -rf obj bin lib
