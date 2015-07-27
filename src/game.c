#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "entity.h"
#include "snake.h"
#include "sprite.h"
#include "controller.h"
#include "window.h"
#include "consts.h"

bool Game_processEvents();
void Game_gameLoop(); 
void Game_initGame();
void Game_keyHandlers();
void Game_restart();
void Game_getRandomSpawn(double * positionVector);

Snake * player = NULL;
Entity * egg = NULL;
bool paused = false;

int main(int argc, char * args[]) {
    if(!Window_init(GAME_WINDOW_TITLE,GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT)) {
        return 1;
    } 
    Game_initGame();
    Game_keyHandlers(player);
    Game_gameLoop();
    Window_destroy();
    return 0;
}

void Game_keyHandlers() {
    Command * moveUp = Controller_createCommand(player,&Snake_moveUp);
    Command * moveDown = Controller_createCommand(player,&Snake_moveDown);
    Command * moveLeft = Controller_createCommand(player,&Snake_moveLeft);
    Command * moveRight = Controller_createCommand(player,&Snake_moveRight);
    Controller_mapKey(moveUp, SDLK_UP);
    Controller_mapKey(moveDown, SDLK_DOWN);
    Controller_mapKey(moveLeft, SDLK_LEFT);
    Controller_mapKey(moveRight, SDLK_RIGHT);
}

void Game_initGame() {
    Sprite * headSprite = Sprite_create(40,40,PLAYER_HEAD_LOCATION);
    Sprite * bodySprite = Sprite_create(40,40, PLAYER_BODY_LOCATION);
    Sprite * eggSprite = Sprite_create(40,40, METAL_BALL_LOCATION);
    double spawnPosition[2] = { GAME_WINDOW_WIDTH/2, (GAME_WINDOW_HEIGHT/2)-(40/2) };
    double positionVector[2] = {0,0};
    Game_getRandomSpawn(positionVector);
    int startingVelocityEgg[2] = {0,0};
    egg = Entity_construct(positionVector, startingVelocityEgg, eggSprite);
    player = Snake_create(headSprite,bodySprite,spawnPosition);
}

void Game_getRandomSpawn(double * positionVector) {
    srand(time(NULL));
    int randomScreenX = (rand() / (RAND_MAX /(GAME_WINDOW_WIDTH/40)));
    int randomScreenY = (rand() / (RAND_MAX /(GAME_WINDOW_HEIGHT/40)));
    positionVector[0] = randomScreenX*40;
    positionVector[1] = randomScreenY*40;
}

void Game_update() {
    Snake_update();
    if(!Collision_checkWalls(Snake_getHead())) {
        if(Collision_checkEntities(Snake_getHead(), egg)) {
            double positionVector[2] = {0,0};
            Game_getRandomSpawn(positionVector);
            Entity_setPosition(egg,positionVector[0], positionVector[1]);
            Snake_add();
        } 
    } else {
        Game_restart();
    }
}

void Game_restart() {
   if(egg != NULL) {
       Entity_deconstruct(egg);
   }
   Snake_destroy();
   Game_initGame();
   paused = true;
}

void Game_render() {
    SDL_RenderClear(Window_getRenderer());
    Sprite_render(Entity_getSprite(egg), Entity_getPosition(egg), Window_getRenderer());
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
        Game_update();
        Game_render();
        SDL_Delay(1);
        ++frames;
        printf("average fps : %f\n", frames/((SDL_GetTicks()-start)/1000.0));
    }
    Snake_destroy();
    Entity_deconstruct(egg);
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
            case SDL_KEYUP:
                Controller_handleKeyUp(&e);
                break;
        }
    }
    return quit;
}
