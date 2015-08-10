#ifndef GAME_STATE_ENGINE_DEFINITION
#define GAME_STATE_ENGINE_DEFINITION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_state.h"


GameStateEngine GameStateEngine_get();
void GameStateEngine_destroy();
void GameStateEngine_handleEvents();
void GameStateEngine_update();
void GameStateEngine_render();
#endif
