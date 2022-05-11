CC=clang
CFLAGS=-Wall -pedantic -std=gnu99
PROJECT=task5

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin

FIFO_NAME=fifo
IN=payload.txt
OUT=output.txt

PROGS = main producer consumer
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))

UTILS = sem_handlers mem_handlers
UTILS_OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(UTILS)))
UTILS_SRC = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(UTILS)))

.PRECIOUS: $(OBJ_DIR)/%.o
.PHONY: all structure cmp start run clean tar

all: $(BINARIES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(UTILS_OBJS) | structure
	$(CC) $(CFLAGS) -o $@ $^

structure:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

ifeq ($(firstword $(MAKECMDGOALS)), run)
EXEC_NAME = $(word 2, $(MAKECMDGOALS))
run: all 
$(EXEC_NAME):
	./$(BIN_DIR)/main
endif
cmp:
	diff -s $(IN) $(OUT)

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf bin obj $(OUT)
