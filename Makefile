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
INC=-I$(INC_DIR)/
LIBS=$(shell sdl2-config --libs)
OTHER_LIB=-lSDL2_image -lSDL2_mixer
ifeq ($(OS), Darwin)
	DEBUG=-g
else 
	DEBUG=-ggdb
endif
debug: CFLAGS += $(DEBUG)
debug: CFLAGS += -DDEBUG_TEST

all: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR)/,$(OUT)) $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

debug: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR)/,$(OUT)_debug) $^

clean:
	rm -f $(BIN_DIR)/*
	rm -f $(OBJ_DIR)/*.o
