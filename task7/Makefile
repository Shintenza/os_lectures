CC=gcc
CFLAGS=-Wall -pedantic -std=gnu99
LDFLAGS=-pthread
AR=ar
ARFLAGS=rsv
#1 - normal, 2 - static, 3 - dynamic v1, 4 - dynamic v2
MODE= 4


PROJECT=task7

SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
LIB_DIR=lib
INC_DIR=$(SRC_DIR)/include

IN=payload.txt
OUT=output.txt

PROGS=main producer consumer
BINARIES = $(addprefix $(BIN_DIR)/, $(PROGS))
MEM_LIB_NAME=mem_handlers
MEM_LIB_OBJ=$(OBJ_DIR)/$(MEM_LIB_NAME).o

SEM_LIB_NAME=sem_handlers
SEM_LIB_OBJ=$(OBJ_DIR)/$(SEM_LIB_NAME).o

LIB_NAME=handlers
LIB_STAT = lib$(LIB_NAME).a
LIB_SHAR = lib$(LIB_NAME).so

all: $(BINARIES)

ifeq ($(MODE), 1)
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(MEM_LIB_OBJ) $(SEM_LIB_OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
endif
ifeq ($(MODE), 2)
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(LIB_STAT)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -L$(LIB_DIR) -l$(LIB_NAME)
endif
ifeq ($(MODE), 3)
$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(LIB_SHAR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -L$(LIB_DIR) -l$(LIB_NAME) -Wl,-R $(LIB_DIR)
endif
ifeq ($(MODE), 4)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o $(LIB_SHAR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) -L$(LIB_DIR) -l$(LIB_NAME)
endif

structure:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

$(LIB_STAT): $(SEM_LIB_OBJ) $(MEM_LIB_OBJ)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)
$(LIB_SHAR): $(SEM_LIB_OBJ) $(MEM_LIB_OBJ)
	$(CC) -shared -o $@ $(LDFLAGS) $^
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h | structure
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | structure
	$(CC) $(CFLAGS) -c $< -o $@

run: all
ifeq ($(MODE), 4)
	export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(BIN_DIR)/main
else
	./$(BIN_DIR)/main
endif

cmp:
	diff -s $(IN) $(OUT)

tar: clean
	cd ../; tar cvfz $(PROJECT).tar.gz $(PROJECT)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(LIB_DIR) $(OUT)
