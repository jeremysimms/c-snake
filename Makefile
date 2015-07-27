CC=gcc
SRC_DIR=src/
BIN_DIR=bin/
OBJS=$(addprefix $(SRC_DIR), snake.c entity.c window.c collision.c sprite.c controller.c game.c)
OUT=game
OUT_DEBUG=game

CFLAGS=$(shell sdl2-config --cflags)
LIBS=$(shell sdl2-config --libs)
OTHER_LIB=-lSDL2_image
DEBUG=-ggdb 

all:
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR),$(OUT))

debug: $(OBJS);
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR),$(OUT_DEBUG)) $(DEBUG)

clean:
	rm -f $(BIN_DIR)/*
