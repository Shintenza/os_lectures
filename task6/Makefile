CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
PROJECT=task6

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin
HEADERS_DIR=$(SRC_DIR)/include

PROG_N=exclusion
PROC_N=5
CRYT_N=3

PROGS = main exclusion
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))

UTILS = sem_handlers file_handlers
UTILS_OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(UTILS)))
UTILS_SRC = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(UTILS)))

.PRECIOUS: $(OBJ_DIR)/%.o
.PHONY: all run clean tar cmp

all: $(BINARIES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(UTILS_OBJS) | structure
	$(CC) $(CFLAGS) -o $@ $^

structure:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

ifeq ($(firstword $(MAKECMDGOALS)), run)
EXEC_NAME = $(word 2, $(MAKECMDGOALS))

run: all
$(EXEC_NAME):
	./$(BIN_DIR)/$@ $(PROG_N) $(PROC_N) $(CRYT_N)
endif

cmp:
	diff -s $(IN) $(OUT)

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf bin obj number.txt
