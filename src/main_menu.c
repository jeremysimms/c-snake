#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game_state.h"
#include "button.h"
#include "controller.h"

void MainMenu_init();
void MainMenu_destroy();
void MainMenu_update();
void MainMenu_render();
void MainMenu_handleEvents();

Button startButton;
Button controlsButton;
Button quitButton;
Button * currentButton;

GameState MainMenu_get() {
    GameState state = GameState_create();
    state->update = &MainMenu_update;
    state->render = &MainMenu_render;
    state->handleEvents = &MainMenu_handleEvents;
    state->init = &MainMenu_init;
    state->destroy = &MainMenu_destroy;
    return state;
}

void MainMenu_update() {
}

void MainMenu_handleEvents() {

}

void MainMenu_render() {
    Button_render(startButton);
    Button_render(controlsButton);
    Button_render(quitButton);
}

void MainMenu_init() {
}

void MainMenu_destroy() {
    
}
