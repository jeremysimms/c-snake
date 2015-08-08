#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "entity.h"
#include "snake.h"
#include "sprite.h"
#include "controller.h"
#include "collision.h"
#include "window.h"
#include "consts.h"
#include "game_state.h"
#include "debug.h"

void PlayingState_start();
void PlayingState_tick(); 
void PlayingState_init();
void PlayingState_keyHandlers();
void PlayingState_destroy();
void PlayingState_restart();
void PlayingState_getRandomSpawn(double * positionVector);
void PlayingState_loadTextures();
void PlayingState_destroyTextures();

Snake * player = NULL;
Entity * metalBall = NULL;
SDL_Texture * metalBallTexture = NULL;
SDL_Texture * snakeHeadTexture = NULL;
SDL_Texture * snakeBodyTexture = NULL;
bool paused = true;
int start = 0;
int frames = 0;

GameState PlayingState_get() {
    GameState state = NULL;
    if(state == NULL) {
        state = GameState_create();
        state->tick = &PlayingState_tick;
        state->init = &PlayingState_init;
        state->destroy = &PlayingState_destroy;
    }
    return state;
}

void PlayingState_destroyTextures() {
    SDL_DestroyTexture(metalBallTexture);
    SDL_DestroyTexture(snakeHeadTexture);
    SDL_DestroyTexture(snakeBodyTexture);
}

void PlayingState_loadTextures() {
    SDL_Surface * metalBallSurface = IMG_Load(METAL_BALL_LOCATION);
    SDL_Surface * snakeHeadSurface = IMG_Load(PLAYER_HEAD_LOCATION);
    SDL_Surface * snakeBodySurface = IMG_Load(PLAYER_BODY_LOCATION);
    if(metalBallSurface == NULL || snakeHeadSurface == NULL || snakeBodySurface == NULL) {
        debug_print("Error loading image. SDL Error: %s\n", IMG_GetError());
    }
    metalBallTexture = SDL_CreateTextureFromSurface(Window_getRenderer(), metalBallSurface);
    snakeHeadTexture = SDL_CreateTextureFromSurface(Window_getRenderer(), snakeHeadSurface);
    snakeBodyTexture = SDL_CreateTextureFromSurface(Window_getRenderer(), snakeBodySurface);
    if(metalBallTexture == NULL || snakeHeadTexture == NULL || snakeBodyTexture == NULL) {
        debug_print("Error creating texture. SDL Error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(metalBallSurface);
    SDL_FreeSurface(snakeHeadSurface);
    SDL_FreeSurface(snakeBodySurface);
}

void PlayingState_pause() {
    if(paused) {
        paused = false;
    }
}

void PlayingState_keyHandlers() {
    Command * moveUp = Controller_createCommand(player,&Snake_moveUp);
    Command * moveDown = Controller_createCommand(player,&Snake_moveDown);
    Command * moveLeft = Controller_createCommand(player,&Snake_moveLeft);
    Command * moveRight = Controller_createCommand(player,&Snake_moveRight);
    Command * start = Controller_createCommand(NULL, &PlayingState_pause);
    Controller_mapKey(moveUp, SDLK_UP);
    Controller_mapKey(moveDown, SDLK_DOWN);
    Controller_mapKey(moveLeft, SDLK_LEFT);
    Controller_mapKey(moveRight, SDLK_RIGHT);
    Controller_mapKey(start, SDLK_SPACE);
}

void PlayingState_init() {
    PlayingState_loadTextures();
    PlayingState_keyHandlers();
    PlayingState_start();
    start = SDL_GetTicks();
}

void PlayingState_destroy() {
    Snake_destroy();
    Entity_deconstruct(metalBall);
    PlayingState_destroyTextures(); 
}

void PlayingState_start() {
    Sprite * headSprite = Sprite_create(40,40,snakeHeadTexture);
    Sprite * bodySprite = Sprite_create(40,40, snakeBodyTexture);
    Sprite * metalBallSprite = Sprite_create(40,40, metalBallTexture);
    double spawnPosition[2] = { GAME_WINDOW_WIDTH/2, (GAME_WINDOW_HEIGHT/2)-(40/2) };
    double positionVector[2] = {0,0};
    PlayingState_getRandomSpawn(positionVector);
    int startingVelocity[2] = {0,0};
    metalBall = Entity_construct(positionVector, startingVelocity, metalBallSprite);
    player = Snake_create(headSprite,bodySprite,spawnPosition);
}

void PlayingState_getRandomSpawn(double * positionVector) {
    int randomScreenX = (rand() / (RAND_MAX /(GAME_WINDOW_WIDTH/40)));
    int randomScreenY = (rand() / (RAND_MAX /(GAME_WINDOW_HEIGHT/40)));
    positionVector[0] = randomScreenX*40;
    positionVector[1] = randomScreenY*40;
}

void PlayingState_update() {
    Snake_update();
    if(!(Collision_checkWalls(Snake_getHead()) || Snake_checkCollisions())) {
        if(Collision_checkEntities(Snake_getHead(), metalBall)) {
            double positionVector[2] = {0,0};
            PlayingState_getRandomSpawn(positionVector);
            Entity_setPosition(metalBall,positionVector[0], positionVector[1]);
            Snake_add();
        } 
    } else if(!paused) {
        paused = true;
        PlayingState_restart();
    }
}

void PlayingState_restart() {
   if(metalBall != NULL) {
       Entity_deconstruct(metalBall);
   }
   Snake_destroy();
   PlayingState_start();
   paused = true;
}

void PlayingState_render() {
    SDL_RenderClear(Window_getRenderer());
    Sprite_render(Entity_getSprite(metalBall), Entity_getPosition(metalBall), Window_getRenderer());
    Snake_render();
    SDL_RenderPresent(Window_getRenderer());
}

void PlayingState_tick() {
    int frameStart = SDL_GetTicks();
    if(!paused) {
        PlayingState_update();
    }
    PlayingState_render();
    SDL_Delay(1);
    ++frames;
    debug_print("average fps : %f\n", frames/((SDL_GetTicks()-start)/1000.0));
}

