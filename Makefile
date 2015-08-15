UNAME=$(shell uname)
CC=gcc
SRC_DIR=src
BIN_DIR=bin
OBJ_DIR=obj
INC_DIR=include

SDL_CONFIG=sdl2-config
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
OUT=game
CFLAGS=$(shell $(SDL_CONFIG) --cflags) -lm -std=gnu99
INC=-I$(INC_DIR)/
LIBS=$(shell $(SDL_CONFIG) --libs)
OTHER_LIB=-lSDL2_image -lSDL2_mixer
ifeq ($(OS), Darwin)
	DEBUG=-g
else 
	DEBUG=-ggdb
endif
debug: CFLAGS += $(DEBUG)
debug: CFLAGS += -DDEBUG_TEST
windows: CC=x86_64-w64-mingw32-gcc 
windows: SDL_CONFIG=$(shell echo $$WINDOWS_SDL_CONFIG_LOCATION)
windows: CFLAGS += --std=c99

all: $(OBJS)
	$(CC) $^ $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR)/,$(OUT))

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

debug: $(OBJS)
	$(CC) $^ $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR)/,$(OUT)_debug)

windows: $(OBJS)
	$(CC) $^ $(CFLAGS) $(LIBS) $(OTHER_LIB) -o $(addprefix $(BIN_DIR)/,$(OUT).exe)

clean:
	rm -rf $(BIN_DIR)/*
	rm -f $(OBJ_DIR)/*.o
