CC=gcc
CFLAGS=-Wall -std=c99 -pedantic
PROJECT=task3

OBJ_DIR=obj
SRC_DIR=src
BIN_DIR=bin

PROGS = task_a task_b task_c task_c2
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))
UTILS = utils
UTILS_OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR)/, $(UTILS)))
UTILS_HEADERS = $(addsuffix .h, $(addprefix $(SRC_DIR)/, $(UTILS)))
UTILS_SRC = $(addsuffix .c, $(addprefix $(SRC_DIR)/, $(UTILS)))

.PRECIOUS: $(OBJ_DIR)/%.o

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
	./$(BIN_DIR)/$@ $(HM) $(PN)
endif

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)
clean:
	rm -rf bin obj
