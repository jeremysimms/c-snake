
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "sprite.h"
#include "controller.h"
#include "window.h"
#include "bool.h"

void Game_gameLoop(); 
int Game_hasQuit();
void Game_processEvents();
void Game_checkCollisions(Sprite * sprite1, Sprite * sprite2);
void Game_checkWallCollisions(Sprite * sprite);

int main(int argc, char * args[]) {
    SDL_Window * window = Window_createWindow("Pac Man");
    if(Window_init() == 1) {
        if(window == NULL) 
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            Game_gameLoop();
            Window_destroy();
            return 0;
        }
    }
}

// TODO: Modify control flow
//   1.) Iterate through entities;
//   2.) For every entity, poll for controller input
//      a.) If controller input, respond to events
//      b.) Update positions.
//   4.) Detect and resolve collisions.
//   5.) For every entity, render entity.

void Game_checkCollisions(Sprite * sprite1, Sprite * sprite2) {
    if(!(sprite2.x + sprite2.w < sprite1.x)) {
        if(!(sprite2.y + sprite1.h < sprite1.y)) {
            Sprite_setVelocity(sprite2, -sprite2.velocity[0], sprite2.velocity[1]);
        }
    }
}

void Game_checkWallCollisions(Sprite * sprite) {
    int * position = Sprite_getPosition();
    int * velocity = Sprite_getVelocity();
    if(position[0] <= 0) {
        Sprite_setPosition(sprite, 0, position[1]);
        Sprite_setVelocity(sprite, -velocity[0], velocity[1]);
    } else if(position[0] + sprite.w >= Window_getWidth()) {
        Sprite_setPosition(sprite, (Window_getWidth() - sprite.w), position[1]);
        Sprite_setVelocity(sprite, -velocity[0], velocity[1]);
    }
    if(position[1] <= 0) {
        Sprite_setPosition(sprite, position[0], 0);
        Sprite_setVelocity(sprite, velocity[0], -velocity[1]);
    }else if(position[1] + sprite.h >= Window_getHeight()) {
        Sprite_setPosition(sprite, position[0], Window_getHeight() - sprite.h);
        Sprite_setVelocity(sprite, velocity[0], -velocity[1]);
    }
}

//TODO: Implement sprite methods
//TODO: Add controller methods to controller.h
void Game_gameLoop() {
    int quit = 0;
    SDL_Surface * wSurface = NULL;
    wSurface = SDL_GetWindowSurface(window);
    
    Sprite * paddle1 = Sprite_createSprite(100,100,"res/img/sprite.png");
    Sprite * paddle2 = Sprite_createSprite(100,100,"res/img/sprite.png");
    Sprite * ball = Sprite_createSprite(100,100,"res/img/sprite.png");

    Game_keyHandlers(paddle1);

    while(quit == false) {
        //TODO: Process all events and hand them to the correct listeners
        Game_processEvents();
        Sprite_update(ball);
        Game_checkCollisions(paddle1, ball);
        Game_checkCollisions(paddle2, ball);
        Game_checkWallCollisions(ball);
        Sprite_render(paddle1);
        Sprite_render(paddle2);
        Sprite_render(ball);
        quit = Game_processEvents();
    }
}

void Game_keyHandlers(Sprite * sprite) {
    Command * moveUp = Controller_createCommand(sprite,sprite->moveUp);
    Command * moveDown = Controller_createCommand(sprite,sprite->moveDown);
    Command * moveLeft = Controller_createCommand(sprite,sprite->moveLeft);
    Command * moveRight = Controller_createCommand(sprite,sprite->moveRight);
    Controller_mapKey(moveUp, SDLK_UP);
    Controller_mapKey(moveDown, SDLK_DOWN);
    Controller_mapKey(moveLeft, SDLK_LEFT);
    Controller_mapKey(moveRight, SDLK_RIGHT);
}

void Game_processEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT) {
        }
        switch(e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                Controller_handleKeyDown(&e);
                break;
            case SDL_KEYUP:
                break;
            case SDL_USEREVENT:
                break;
        }
    }
}
