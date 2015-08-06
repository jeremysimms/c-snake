#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "game_state.h"
#include "window.h"
#include "consts.h"
#include "playing_state.h"
#include "controller.h"

GameState currentState = NULL;
GameState playingState = NULL;
GameState mainMenuState = NULL;
GameState controlsState = NULL;

Uint32 PLAYING_STATE_EVENT;
Uint32 CONTROLS_STATE_EVENT;
Uint32 MAINMENU_STATE_EVENT;

void gameLoop();
void initStates();
void handleUserEvent(SDL_Event * e);

int main(int argc, char * args[]) {
    srand(time(NULL));
    if(!Window_init(GAME_WINDOW_TITLE,GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT)) {
        return 1;
    }
    initStates();
    PLAYING_STATE_EVENT = SDL_RegisterEvents(3);
    CONTROLS_STATE_EVENT = PLAYING_STATE_EVENT+1;
    MAINMENU_STATE_EVENT = PLAYING_STATE_EVENT+2;
    gameLoop();
    Window_destroy();
    return 0;
}

bool processEvents() {
    SDL_Event e;
    bool quit = false;
    while(SDL_PollEvent(&e) != 0) {
        switch(e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                Controller_handleKeyDown(&e);
                break;
            case SDL_USEREVENT:
                handleUserEvent(&e);
                break;
        }
    }
    return quit;
}

void initStates() {
    playingState = PlayingState_get();
    currentState = playingState;
}

void handleUserEvent(SDL_Event * e) {
    if(e->type == PLAYING_STATE_EVENT) {
        currentState = playingState;
    } else if (e->type == CONTROLS_STATE_EVENT) {
        currentState = controlsState;
    } else if (e->type == MAINMENU_STATE_EVENT) {
        currentState = mainMenuState;
    }
}

void gameLoop() {
    bool quit = false;
    currentState->init(NULL);
    while(!quit) {
        quit = processEvents();
        currentState->tick(NULL);
    }
}

