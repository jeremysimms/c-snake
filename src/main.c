#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL.h>
#include "debug.h"
#include "game_state.h"
#include "window.h"
#include "consts.h"
#include "playing_state.h"
#include "main_menu.h"
#include "controller.h"
#include "game_state_engine.h"
#include "audio.h"

void gameLoop();
void initStates();
void destroyStates();

int main(int argc, char * args[]) {
    srand(time(NULL));
    if(!Window_init(GAME_WINDOW_TITLE,GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT)) {
        return 1;
    }
    if(!Audio_init()) {
        return 1;
    }
    gameLoop();
    Window_destroy();
    return 0;
}

void gameLoop() {
    bool quit = false;
    int start = SDL_GetTicks();
    int frames = 0;
    GameStateEngine engine = GameStateEngine_get();
    GameState playingState = PlayingState_get();
    engine->push(playingState);
    engine->current->init(NULL);
    while(engine->running) {
        int frameStart = SDL_GetTicks();
        GameStateEngine_handleEvents();
        GameStateEngine_update();
        GameStateEngine_render();
        SDL_Delay(5);
        frames++;
        int frameEnd = SDL_GetTicks();
        debug_print("average fps : %f\n", frames/((frameEnd-start)/1000.0));
    }
    GameStateEngine_destroy();
    Controller_destroy();
}

