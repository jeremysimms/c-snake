CC=gcc
OBJS=pac.c
OUT=pac
CFLAGS=-I/usr/include/SDL2 -D_REENTRANT
LIBS=-L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image
DEBUG=-ggdb 

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(OUT) 

debug: $(OBJ)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(OUT) $(DEBUG)
