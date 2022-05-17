CC=gcc
CFLAGS=-Wall -std=c99 -pedantic -lpthread
PROJECT=task9

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin
HEADERS_DIR=$(SRC_DIR)/include

PROC_N=3
CRYT_N=4

PROGS = main
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))

UTILS = exclusion
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

run: all
	./$(BIN_DIR)/main $(PROC_N) $(CRYT_N)

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
