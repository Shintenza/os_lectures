CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
PROJECT=task3

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin

FIFO_NAME=fifo

PROGS = consumer handler producer
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))

.PRECIOUS: $(OBJ_DIR)/%.o

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
start:
	mkfifo -m 644 $(FIFO_NAME)
	alacritty -t PRODUCER -e ./bin/producer $(FIFO_NAME) payload.txt &
	alacritty -t CONSUMER -e ./bin/consumer $(FIFO_NAME) out.txt

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf bin obj $(FIFO_NAME)
