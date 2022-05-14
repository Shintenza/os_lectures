CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
PROJECT=task8

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin
HEADERS_DIR=$(SRC_DIR)/include

PROGS = client server
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))

.PRECIOUS: $(OBJ_DIR)/%.o
.PHONY: all run clean tar cmp

UTILS = msg_handlers
UTILS_OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(UTILS)))
UTILS_SRC = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(UTILS)))

all: $(BINARIES)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(UTILS_OBJS) | structure
	$(CC) $(CFLAGS) -o $@ $^

structure:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

cmp:
	diff -s $(IN) $(OUT)

start: all
	alacritty --title SERVER -e ./$(BIN_DIR)/server &
	alacritty --title CLIENT -e ./$(BIN_DIR)/client &
	alacritty --title CLIENT -e ./$(BIN_DIR)/client &

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)
