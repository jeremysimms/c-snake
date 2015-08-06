#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game_state.h"

GameState GameState_create() {
    GameState state = malloc(sizeof(GameState));
    return state;
}
