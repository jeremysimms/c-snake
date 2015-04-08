CC=gcc
OBJS=pac.c
OUT=pac
CFLAGS=$(shell sdl2-config --cflags)
LIBS=$(shell sdl2-config --libs)
OTHER_LIB=-lSDL2_image
DEBUG=-ggdb 

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(OUT) 

debug: $(OBJ)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(OUT) $(DEBUG)
