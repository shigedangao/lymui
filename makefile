# Directories

SRC_DIR = lymui
INC_DIR = lymui/include
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# CUnit directories & tests

INC_LIB_DIR = lib/cunit/include
INC_LIB_TT  = lymui/tests

# Compiler

CC = gcc
CFLAGS = -fprofile-arcs -ftest-coverage
CFLAG_LIB = -Wall -O2 -I$(INC_DIR)
INC_TT = -I$(INC_DIR) -I$(INC_LIB_DIR) -I$(INC_LIB_TT) -Wall $(CFLAGS)

# Lymui source files
LM_HEADERS = $(wildcard $(SRC_DIR)/include/*.h)
LM_SOURCES = $(filter-out lymui/main.c, $(wildcard $(SRC_DIR)/*.c))
LM_TESTS_C = $(wildcard $(SRC_DIR)/tests/*.c)
LM_TESTS_H = $(wildcard $(SRC_DIR)/tests/*.h)
OBJECTS := $(patsubst %.c, $(OBJ_DIR)/%.o, $(LM_SOURCES))

# Tests specific files

LM_MAIN = $(SRC_DIR)/main.c
LM_TESTS_ALL = $(LM_MAIN) $(LM_SOURCES) $(LM_TESTS_C)
LIB_FLAGS += -Llib/cunit
LIB_LINK  += -lcunit

# Rules specific for tests cases

lymdir:
	mkdir -p $(TEST_DIR)

lym: $(LM_TESTS_ALL)
	$(CC) -o $@ $^ $(INC_TT) $(LIB_FLAGS) $(LIB_LINK) -lm -pthread

test:
	./lym

cleanTest:
	rm -rf /*o *~core *.o *.gcda *.gcno *.gcov

# Rules for other tasks

all: cleanTest clean lib

obj:
	mkdir -p $(OBJ_DIR)/$(SRC_DIR)

bin:
	mkdir -p $(BIN_DIR)/include

headers: bin
	for fname in $(LM_HEADERS) ; do \
		cp $${fname} $(BIN_DIR)/include/ ; \
	done

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAG_LIB) -c $< -o $@

lib: obj headers $(OBJECTS)
	ar rcs $(BIN_DIR)/liblymui.a $(OBJ_DIR)/$(SRC_DIR)/*.o

clean:
	rm -rf $(OBJ_DIR) && rm -rf $(BIN_DIR)
