#ifndef GAME_STATE_DEFINITION
#define GAME_STATE_DEFINITION
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct game_state {
    void (*tick)(void * args);
    void (*init)(void * args);
    void (*destroy)(void * args);
} * GameState;

GameState GameState_create();
#endif
