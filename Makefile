CC = gcc
FLAGS = -Wall -Wextra -Werror
TFLAGS = -I thirdparty -I src

APP_NAME = MySimpleComputer
TEST_NAME_1 = test1
TEST_NAME_2 = test2
TEST_NAME_3 = test3
TEST_NAME_4 = test4

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = test
BIN_DIR = bin
LIB_DIR = lib

BC_DIR = $(SRC_DIR)/libmyBigChars
COMPLIB_DIR = $(SRC_DIR)/libcomputer
TERM_DIR = $(SRC_DIR)/libmyTerm
MAIN_DIR = $(SRC_DIR)/MySimpleComputerApp
READKEY_DIR = $(SRC_DIR)/libmyReadkey

OBJ_SRC_DIR = $(OBJ_DIR)/$(SRC_DIR)
OBJ_TEST_DIR = $(OBJ_DIR)/$(TEST_DIR)

APP_PATH = $(BIN_DIR)/$(APP_NAME)
TEST_PATH_1 = $(BIN_DIR)/$(TEST_NAME_1)
TEST_PATH_2 = $(BIN_DIR)/$(TEST_NAME_2)
TEST_PATH_3 = $(BIN_DIR)/$(TEST_NAME_3)
TEST_PATH_4 = $(BIN_DIR)/$(TEST_NAME_4)

LIB_COMPUTER_PATH = $(LIB_DIR)/libmySimpleComputer.a
LIB_TERM_PATH = $(LIB_DIR)/libmyTerm.a
LIB_BC_PATH = $(LIB_DIR)/libmyBigChars.a
LIB_READKEY_PATH = $(LIB_DIR)/libmyreadkey.a

PROJECT_SOURCES = $(MAIN_DIR)/main.c $(COMPLIB_DIR)/computerlib.c $(TERM_DIR)/myTerm.c $(BC_DIR)/myBigChars.c $(READKEY_DIR)/myreadkey.c $(MAIN_DIR)/interface.c $(MAIN_DIR)/CU.c $(MAIN_DIR)/ALU.c
PROJECT_OBJECTS = $(OBJ_SRC_DIR)/main.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(OBJ_SRC_DIR)/myreadkey.o $(OBJ_SRC_DIR)/interface.o $(OBJ_SRC_DIR)/CU.o $(OBJ_SRC_DIR)/ALU.o

.PHONY: all mkdir

all: mkdir $(APP_PATH) $(TEST_PATH_1) $(TEST_PATH_2) $(TEST_PATH_3) $(TEST_PATH_4)

mkdir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_SRC_DIR)
	mkdir -p $(OBJ_TEST_DIR)
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
	$(CC) $(FLAGS) -I src -c $(MAIN_DIR)/CU.c -o $(OBJ_SRC_DIR)/CU.o 

#TEST

OBJECTS_FOR_TEST = $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(OBJ_SRC_DIR)/myreadkey.o $(OBJ_SRC_DIR)/interface.o $(OBJ_SRC_DIR)/CU.o $(OBJ_SRC_DIR)/ALU.o

SOURCES_TEST = $(TEST_DIR)/test1.c $(TEST_DIR)/test2.c $(TEST_DIR)/test3.c $(TEST_DIR)/test4.c
OBJECTS_TEST = $(OBJ_TEST_DIR)/test1.o $(OBJ_TEST_DIR)/test2.o $(OBJ_TEST_DIR)/test3.o $(OBJ_TEST_DIR)/test4.o

SOURCES_TEST_MAIN = $(TEST_DIR)/main_test1.c $(TEST_DIR)/main_test2.c $(TEST_DIR)/main_test3.c $(TEST_DIR)/main_test4.c
OBJECTS_TEST_MAIN = $(OBJ_TEST_DIR)/main_test1.o $(OBJ_TEST_DIR)/main_test2.o $(OBJ_TEST_DIR)/main_test3.o $(OBJ_TEST_DIR)/main_test4.o

$(TEST_PATH_1) : $(OBJ_TEST_DIR)/test1.o $(OBJ_TEST_DIR)/main_test1.o $(OBJECTS_FOR_TEST)
	$(CC) $(FLAGS) $^ -o $@

$(TEST_PATH_2) : $(OBJ_TEST_DIR)/test2.o $(OBJ_TEST_DIR)/main_test2.o $(OBJECTS_FOR_TEST) 
	$(CC) $(FLAGS) $^ -o $@

$(TEST_PATH_3) : $(OBJ_TEST_DIR)/test3.o $(OBJ_TEST_DIR)/main_test3.o $(OBJECTS_FOR_TEST) 
	$(CC) $(FLAGS) $^ -o $@

$(TEST_PATH_4) : $(OBJ_TEST_DIR)/test4.o $(OBJ_TEST_DIR)/main_test4.o $(OBJECTS_FOR_TEST) 
	$(CC) $(FLAGS) $^ -o $@

$(OBJECTS_TEST_MAIN) : $(SOURCES_TEST_MAIN)
	$(CC) $(FLAGS) $(TFLAGS) -c $(TEST_DIR)/main_test1.c -o $(OBJ_TEST_DIR)/main_test1.o
	$(CC) $(FLAGS) $(TFLAGS) -c $(TEST_DIR)/main_test2.c -o $(OBJ_TEST_DIR)/main_test2.o
	$(CC) $(FLAGS) $(TFLAGS) -c $(TEST_DIR)/main_test3.c -o $(OBJ_TEST_DIR)/main_test3.o
	$(CC) $(FLAGS) $(TFLAGS) -I $(TEST_DIR) -c $(TEST_DIR)/main_test4.c -o $(OBJ_TEST_DIR)/main_test4.o

$(OBJECTS_TEST) : $(SOURCES_TEST)
	$(CC) $(FLAGS) $(TFLAGS) -c $(TEST_DIR)/test1.c -o $(OBJ_TEST_DIR)/test1.o
	$(CC) $(FLAGS) $(TFLAGS) -c $(TEST_DIR)/test2.c -o $(OBJ_TEST_DIR)/test2.o
	$(CC) $(FLAGS) $(TFLAGS) -c $(TEST_DIR)/test3.c -o $(OBJ_TEST_DIR)/test3.o
	$(CC) $(FLAGS) $(TFLAGS) -c $(TEST_DIR)/test4.c -o $(OBJ_TEST_DIR)/test4.o

run: $(APP_PATH)
	$(APP_PATH)

.PHONY: clean

clean:
	rm -rf obj bin lib