CC=gcc
CFLAGS=-Wall
PROJECT=task1

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin

EXECS = $(BIN_DIR)/task2 $(BIN_DIR)/task2_out
.PHONY: all clean
# prevents from deleting object files
.PRECIOUS: $(OBJ_DIR)/%.o
all: $(EXECS) | structure

$(BIN_DIR)/%: $(OBJ_DIR)/%.o | structure
	gcc -o $@ $<

structure:
	mkdir -p bin 
	mkdir -p obj

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	gcc -c $< -o $@

# var below contains list of targets given by user calling make
ifeq ($(firstword $(MAKECMDGOALS)), run)
EXEC_NAME = $(word 2, $(MAKECMDGOALS))
run: all
$(EXEC_NAME):
	./$(BIN_DIR)/$@ $(ARGS)
endif
tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf bin obj
