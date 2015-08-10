#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game_state.h"

GameState GameState_create() {
    GameState state = malloc(sizeof(struct game_state));
    state->update = NULL;
    state->render = NULL;
    state->init = NULL;
    state->destroy = NULL;
    state->handleEvents = NULL;
    state->pause = NULL;
    return state;
}

void GameState_destroy(GameState state) {
    state->destroy(NULL);
    free(state);
}
