#ifndef GAME_STATE_DEFINITION
#define GAME_STATE_DEFINITION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct game_state_engine * GameStateEngine;
typedef struct game_state * GameState;
typedef struct game_state_stack GameStateStack;

struct game_state_stack {
    GameStateStack * next;
    GameState state;
};

struct game_state_engine {
    GameState current;
    GameStateStack * stack;
    bool running;
    void (*swap) (GameState state);
    void (*push) (GameState state);
    void (*pop) (GameState state);
};

struct game_state {
    void (*update)(void * args);
    void (*render)(void * args);
    void (*init)(void * args);
    void (*destroy)(void * args);
    void (*pause)(void * args);
    void (*handleEvents)(GameStateEngine engine,SDL_Event * event);
};

GameState GameState_create();
#endif
