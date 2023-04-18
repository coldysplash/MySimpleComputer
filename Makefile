CC = gcc
FLAGS = -Wall -Wextra -Werror

APP_NAME = MySimpleComputer
TEST_NAME_1 = test1
TEST_NAME_2 = test2
TEST_NAME_3 = test3
TEST_NAME_4 = test4

SRC_DIR = src
TEST_DIR = test
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib

BC_DIR = $(SRC_DIR)/libmyBigChars
COMPLIB_DIR = $(SRC_DIR)/libcomputer
TERM_DIR = $(SRC_DIR)/libmyTerm
MAIN_DIR = $(SRC_DIR)/app
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

.PHONY: all mkdir

all: mkdir $(APP_PATH) $(TEST_PATH_1) $(TEST_PATH_2) $(TEST_PATH_3) $(TEST_PATH_4)

mkdir:
	mkdir -p $(BIN_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_SRC_DIR)
	mkdir -p $(OBJ_TEST_DIR)
	mkdir -p $(LIB_DIR)

$(APP_PATH) : $(OBJ_SRC_DIR)/main.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(OBJ_SRC_DIR)/myreadkey.o $(OBJ_SRC_DIR)/interface.o $(OBJ_SRC_DIR)/controldevice.o $(LIB_COMPUTER_PATH) $(LIB_TERM_PATH) $(LIB_BC_PATH) $(LIB_READKEY_PATH)
	$(CC) $(FLAGS) $^ -o $@

$(LIB_COMPUTER_PATH) : $(OBJ_SRC_DIR)/computerlib.o
	ar rc $@ $^

$(LIB_TERM_PATH) : $(OBJ_SRC_DIR)/myTerm.o
	ar rc $@ $^

$(LIB_BC_PATH) : $(OBJ_SRC_DIR)/myBigChars.o
	ar rc $@ $^

$(LIB_READKEY_PATH) : $(OBJ_SRC_DIR)/myreadkey.o
	ar rc $@ $^

$(OBJ_SRC_DIR)/main.o : $(MAIN_DIR)/main.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/interface.o : $(MAIN_DIR)/interface.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/controldevice.o : $(MAIN_DIR)/controldevice.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/computerlib.o : $(COMPLIB_DIR)/computerlib.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/myTerm.o : $(TERM_DIR)/myTerm.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/myBigChars.o : $(BC_DIR)/myBigChars.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

$(OBJ_SRC_DIR)/myreadkey.o : $(READKEY_DIR)/myreadkey.c
	$(CC) -I src -c $(FLAGS) -o $@ $<

run: $(APP_PATH)
	$(APP_PATH)

$(TEST_PATH_1) : $(OBJ_TEST_DIR)/test1.o $(OBJ_TEST_DIR)/main_test1.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(LIB_COMPUTER_PATH) $(LIB_TERM_PATH) $(LIB_BC_PATH) $(LIB_READKEY_PATH)
	$(CC) $(FLAGS) $^ -o $@

$(TEST_PATH_2) : $(OBJ_TEST_DIR)/test2.o $(OBJ_TEST_DIR)/main_test2.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(LIB_COMPUTER_PATH) $(LIB_TERM_PATH) $(LIB_BC_PATH) $(LIB_READKEY_PATH)
	$(CC) $(FLAGS) $^ -o $@

$(TEST_PATH_3) : $(OBJ_TEST_DIR)/test3.o $(OBJ_TEST_DIR)/main_test3.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(LIB_COMPUTER_PATH) $(LIB_TERM_PATH) $(LIB_BC_PATH) $(LIB_READKEY_PATH)
	$(CC) $(FLAGS) $^ -o $@

$(TEST_PATH_4) : $(OBJ_TEST_DIR)/test4.o $(OBJ_TEST_DIR)/main_test4.o $(OBJ_SRC_DIR)/computerlib.o $(OBJ_SRC_DIR)/myTerm.o $(OBJ_SRC_DIR)/myBigChars.o $(LIB_COMPUTER_PATH) $(LIB_TERM_PATH) $(LIB_BC_PATH) $(LIB_READKEY_PATH)
	$(CC) $(FLAGS) $^ -o $@

$(OBJ_TEST_DIR)/main_test1.o : $(TEST_DIR)/main_test1.c
	$(CC) $(FLAGS) -I thirdparty -I $(TEST_DIR) -I src -c -o $@ $<

$(OBJ_TEST_DIR)/main_test2.o : $(TEST_DIR)/main_test2.c
	$(CC) $(FLAGS) -I thirdparty -I $(TEST_DIR) -I src -c -o $@ $<

$(OBJ_TEST_DIR)/main_test3.o : $(TEST_DIR)/main_test3.c
	$(CC) $(FLAGS) -I thirdparty -I $(TEST_DIR) -I src -c -o $@ $<

$(OBJ_TEST_DIR)/main_test4.o : $(TEST_DIR)/main_test4.c
	$(CC) $(FLAGS) -I thirdparty -I $(TEST_DIR) -I src -c -o $@ $<

$(OBJ_TEST_DIR)/test1.o : $(TEST_DIR)/test1.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $@ $<

$(OBJ_TEST_DIR)/test2.o : $(TEST_DIR)/test2.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $@ $<

$(OBJ_TEST_DIR)/test3.o : $(TEST_DIR)/test3.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $@ $<

$(OBJ_TEST_DIR)/test4.o : $(TEST_DIR)/test4.c
	$(CC) $(FLAGS) -I thirdparty -I src -c -o $@ $<


.PHONY: clean

clean:
	rm -rf obj bin lib

.PHONY: rebuild

rebuild:
	rm -rf obj bin lib
	make
