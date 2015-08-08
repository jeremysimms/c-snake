CC=gcc
SRC_DIR=src
BIN_DIR=bin
OBJ_DIR=obj
INC_DIR=include

SRC=$(wildcard $(SRC_DIR)/*.c)
#SRC=src/main.c src/consts.c src/controller.c
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
OUT=game
OUT_DEBUG=game

CFLAGS=$(shell sdl2-config --cflags) 
INC=-I$(INC_DIR)/
LIBS=$(shell sdl2-config --libs)
OTHER_LIB=-lSDL2_image
DEBUG=-ggdb 

all: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR)/,$(OUT)) $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

debug: $(OBJS);
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR),$(OUT_DEBUG)) $(DEBUG)

clean:
	rm -f $(BIN_DIR)/*
	rm -f $(OBJ_DIR)/*.o
