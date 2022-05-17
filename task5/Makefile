CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
PROJECT=task5

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin

FIFO_NAME=fifo
IN=payload.txt
OUT=output.txt

PROGS = consumer handler producer
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))

.PRECIOUS: $(OBJ_DIR)/%.o
.PHONY: all structure cmp start run clean tar

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
	./$(BIN_DIR)/handler $(IN) $(OUT)
endif
cmp:
	diff -s $(IN) $(OUT)
start:
	mkfifo -m 644 $(FIFO_NAME)
	alacritty --hold -t PRODUCER -e ./bin/producer $(FIFO_NAME) $(IN) &
	alacritty --hold -t CONSUMER -e ./bin/consumer $(FIFO_NAME) $(OUT)

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf bin obj $(FIFO_NAME) $(OUT)
