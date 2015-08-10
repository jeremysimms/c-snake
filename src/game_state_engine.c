#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_state_engine.h"
#include "game_state.h"
#include "SDL2/SDL.h"

GameStateEngine stateEngine = NULL;

void swap(GameState state);
void pop(GameState state);
void push(GameState state);
void destroyStates();

GameStateEngine GameStateEngine_get() {
    if(stateEngine == NULL) {
        GameStateEngine engine = malloc(sizeof(struct game_state_engine));
        engine->current = malloc(sizeof(struct game_state));
        engine->running = true;
        engine->swap = &swap;
        engine->push = &push;
        engine->pop = &pop;
        engine->stack = NULL;
        stateEngine = engine;
    }
    return stateEngine;
}

void GameStateEngine_handleEvents() {
    SDL_Event e;
    GameState current = stateEngine->current;
    while(SDL_PollEvent(&e) != 0) {
        switch(e.type) {
            case SDL_QUIT:
                stateEngine->running = false;
                break;
            default: 
                current->handleEvents(stateEngine, &e);
                break;
        }
    }
}

void GameStateEngine_update() {
    stateEngine->current->update(NULL);
}

void GameStateEngine_render() {
    stateEngine->current->render(NULL);
}

void clearStates() {
    GameStateStack * curr = stateEngine->stack;
    while(curr != NULL) {
        GameStateStack * last = curr;
        curr = curr->next;
        last->state->destroy(NULL);
        free(last);
    }
    if(curr != NULL) {
        curr->state->destroy(NULL);
    }
    free(curr);
}

void swap(GameState state) {
    clearStates();
    stateEngine->current = state;
}

void push(GameState state) {
    stateEngine->current = state;
    if(stateEngine->stack != NULL) {
    GameStateStack * curr = stateEngine->stack;
    while(curr != NULL) {
        curr = curr->next;
    }
    stateEngine->current = state;
    }
}

void pop(GameState state) {
    GameStateStack * curr = stateEngine->stack;
    while(curr != NULL) {
        curr = curr->next;
    }
    curr->state->destroy(NULL);
}

void GameStateEngine_destroy() {
    clearStates();
    free(stateEngine);
    stateEngine = NULL;
}
