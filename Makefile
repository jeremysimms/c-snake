CC=gcc
SRC_DIR=src/
BIN_DIR=bin/
OBJS=$(addprefix $(SRC_DIR),sprite.c controller.c sprites_test.c)
OUT=game

CFLAGS=$(shell sdl2-config --cflags)
LIBS=$(shell sdl2-config --libs)
OTHER_LIB=-lSDL2_image
DEBUG=-ggdb 

all:
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR),$(OUT))

debug: $(OBJS);
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR),OUT) $(DEBUG)

test: $(addprefix $(SRC_DIR),sprite.c controller.c sprites_test.c);
	$(addprefix $(SRC_DIR),sprite.c sprites_test.c controller.c) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR),OUT) $(DEBUG)

clean:
	rm -f $(BIN_DIR)$(OUT)
