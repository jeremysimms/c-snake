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

bool Game_processEvents();
void Game_gameLoop(); 
void Game_initGame();
void Game_keyHandlers();
void Game_restart();
void Game_getRandomSpawn(double * positionVector);
void Game_loadTextures();
void Game_destroyTextures();

Snake * player = NULL;
Entity * metalBall = NULL;
SDL_Texture * metalBallTexture = NULL;
SDL_Texture * snakeHeadTexture = NULL;
SDL_Texture * snakeBodyTexture = NULL;
bool paused = true;

int main(int argc, char * args[]) {
    srand(time(NULL));
    if(!Window_init(GAME_WINDOW_TITLE,GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT)) {
        return 1;
    } 
    Game_loadTextures();
    Game_initGame();
    Game_keyHandlers(player);
    Game_gameLoop();
    Window_destroy();
    Game_destroyTextures(); 
    return 0;
}

void Game_destroyTextures() {
    SDL_DestroyTexture(metalBallTexture);
    SDL_DestroyTexture(snakeHeadTexture);
    SDL_DestroyTexture(snakeBodyTexture);
}
void Game_loadTextures() {
    SDL_Surface * metalBallSurface = IMG_Load(METAL_BALL_LOCATION);
    SDL_Surface * snakeHeadSurface = IMG_Load(PLAYER_HEAD_LOCATION);
    SDL_Surface * snakeBodySurface = IMG_Load(PLAYER_BODY_LOCATION);
    if(metalBallSurface == NULL || snakeHeadSurface == NULL || snakeBodySurface == NULL) {
        printf("Error loading image. SDL Error: %s\n", IMG_GetError());
    }
    metalBallTexture = SDL_CreateTextureFromSurface(Window_getRenderer(), metalBallSurface);
    snakeHeadTexture = SDL_CreateTextureFromSurface(Window_getRenderer(), snakeHeadSurface);
    snakeBodyTexture = SDL_CreateTextureFromSurface(Window_getRenderer(), snakeBodySurface);
    if(metalBallTexture == NULL || snakeHeadTexture == NULL || snakeBodyTexture == NULL) {
        printf("Error creating texture. SDL Error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(metalBallSurface);
    SDL_FreeSurface(snakeHeadSurface);
    SDL_FreeSurface(snakeBodySurface);
}

void Game_pause() {
    if(paused) {
        paused = false;
    }
}

void Game_keyHandlers() {
    Command * moveUp = Controller_createCommand(player,&Snake_moveUp);
    Command * moveDown = Controller_createCommand(player,&Snake_moveDown);
    Command * moveLeft = Controller_createCommand(player,&Snake_moveLeft);
    Command * moveRight = Controller_createCommand(player,&Snake_moveRight);
    Command * start = Controller_createCommand(NULL, &Game_pause);
    Controller_mapKey(moveUp, SDLK_UP);
    Controller_mapKey(moveDown, SDLK_DOWN);
    Controller_mapKey(moveLeft, SDLK_LEFT);
    Controller_mapKey(moveRight, SDLK_RIGHT);
    Controller_mapKey(start, SDLK_SPACE);
}

void Game_initGame() {
    Sprite * headSprite = Sprite_create(40,40,snakeHeadTexture);
    Sprite * bodySprite = Sprite_create(40,40, snakeBodyTexture);
    Sprite * metalBallSprite = Sprite_create(40,40, metalBallTexture);
    double spawnPosition[2] = { GAME_WINDOW_WIDTH/2, (GAME_WINDOW_HEIGHT/2)-(40/2) };
    double positionVector[2] = {0,0};
    Game_getRandomSpawn(positionVector);
    int startingVelocity[2] = {0,0};
    metalBall = Entity_construct(positionVector, startingVelocity, metalBallSprite);
    player = Snake_create(headSprite,bodySprite,spawnPosition);
}

void Game_getRandomSpawn(double * positionVector) {
    int randomScreenX = (rand() / (RAND_MAX /(GAME_WINDOW_WIDTH/40)));
    int randomScreenY = (rand() / (RAND_MAX /(GAME_WINDOW_HEIGHT/40)));
    positionVector[0] = randomScreenX*40;
    positionVector[1] = randomScreenY*40;
}

void Game_update() {
    Snake_update();
    if(!(Collision_checkWalls(Snake_getHead()) || Snake_checkCollisions())) {
        if(Collision_checkEntities(Snake_getHead(), metalBall)) {
            double positionVector[2] = {0,0};
            Game_getRandomSpawn(positionVector);
            Entity_setPosition(metalBall,positionVector[0], positionVector[1]);
            Snake_add();
        } 
    } else if(!paused) {
        paused = true;
        Game_restart();
    }
}

void Game_restart() {
   if(metalBall != NULL) {
       Entity_deconstruct(metalBall);
   }
   Snake_destroy();
   Game_initGame();
   paused = true;
}

void Game_render() {
    SDL_RenderClear(Window_getRenderer());
    Sprite_render(Entity_getSprite(metalBall), Entity_getPosition(metalBall), Window_getRenderer());
    Snake_render();
    SDL_RenderPresent(Window_getRenderer());
}

void Game_gameLoop() {
    bool quit = false;
    int frames = 0;
    int start = SDL_GetTicks();
    while(!quit) {
        int frameStart = SDL_GetTicks();
        quit = Game_processEvents();
        if(!paused) {
            Game_update();
        }
        Game_render();
        SDL_Delay(1);
        ++frames;
        printf("average fps : %f\n", frames/((SDL_GetTicks()-start)/1000.0));
    }
    Snake_destroy();
    Entity_deconstruct(metalBall);
    Window_destroy();
    Controller_destroy();
}


bool Game_processEvents() {
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
        }
    }
    return quit;
}
