CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
PROJECT=task4

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin

IN=payload.txt
OUT=output.txt

PROGS = task
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))

.PRECIOUS: $(OBJ_DIR)/%.o
.PHONY: all run clean tar cmp

all: $(BINARIES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o | structure
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
	./$(BIN_DIR)/$@ $(IN) $(OUT)
endif

cmp:
	diff -s $(IN) $(OUT)

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf bin obj $(OUT)
