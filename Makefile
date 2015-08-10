UNAME=$(shell uname)
CC=c99
SRC_DIR=src
BIN_DIR=bin
OBJ_DIR=obj
INC_DIR=include

SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
OUT=game
CFLAGS=$(shell sdl2-config --cflags) -lm
DEBUG_FLAGS=-DDEBUG_TEST
INC=-I$(INC_DIR)/
LIBS=$(shell sdl2-config --libs)
OTHER_LIB=-lSDL2_image
ifeq ($(OS), Darwin)
	DEBUG=-ggdb 
else 
	DEBUG=-g
endif
debug: CFLAGS += $(DEBUG)

all: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR)/,$(OUT)) $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

debug: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR)/,$(OUT)_debug) $^

clean:
	rm -f $(BIN_DIR)/*
	rm -f $(OBJ_DIR)/*.o
