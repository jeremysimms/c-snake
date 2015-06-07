#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#include "entity.h"
#include "sprite.h"
#include "controller.h"
#include "window.h"
#include "consts.h"

bool Game_processEvents();
void Game_gameLoop(); 
void Game_initGame();

Entity * player = NULL;
Entity * egg = NULL;

int main(int argc, char * args[]) {
    if(!Window_init(GAME_WINDOW_TITLE,GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT)) {
        return 1;
    } 
    Game_initGame();
    Game_gameLoop();
    Window_destroy();
    return 0;
}

void moveEntityUp(Entity * entity) {
    Entity_setVelocity(entity, 0, -200); 
}

void moveEntityDown(Entity * entity) {
    Entity_setVelocity(entity, 0, 200); 
}

void moveEntityLeft(Entity * entity) {
    Entity_setVelocity(entity, -200, 0); 
}

void moveEntityRight(Entity * entity) {
    Entity_setVelocity(entity, 200, 0); 
}

void Game_keyHandlers(Entity * entity) {
    Command * moveUp = Controller_createCommand(entity,&moveEntityUp);
    Command * moveDown = Controller_createCommand(entity,&moveEntityDown);
    Command * moveLeft = Controller_createCommand(entity,&moveEntityLeft);
    Command * moveRight = Controller_createCommand(entity,&moveEntityRight);
    Controller_mapKey(moveUp, SDLK_UP);
    Controller_mapKey(moveDown, SDLK_DOWN);
    Controller_mapKey(moveLeft, SDLK_LEFT);
    Controller_mapKey(moveRight, SDLK_RIGHT);
}

void Game_initGame() {
    Sprite * playerSprite = Sprite_create(50,50,"res/img/sprite_scaled.png");
    Sprite * eggSprite = Sprite_create(40,40, "res/img/egg.png");
    srand(time(NULL));
    double randomScreenX = ((double)rand() / ((double)RAND_MAX + 1) * (GAME_WINDOW_WIDTH-40));
    double randomScreenY = ((double)rand() / ((double)RAND_MAX + 1) * (GAME_WINDOW_HEIGHT-40));

    double spawnPositionEgg[2] = { randomScreenX, randomScreenY };
    double spawnPosition[2] = { GAME_WINDOW_WIDTH/2, GAME_WINDOW_HEIGHT/2 };
    int startingVelocity[2] = { GAME_STARTING_VELOCITY[0], GAME_STARTING_VELOCITY[1]};
    int startingVelocityEgg[2] = {0,0};
    egg = Entity_construct(spawnPositionEgg, startingVelocityEgg, eggSprite);
    player = Entity_construct(spawnPosition, startingVelocity, playerSprite);
    Game_keyHandlers(player);
}

void Game_update() {
    Collision_checkWalls(player);
    Entity_update(player);
    if(Collision_checkEntities(player, egg)) {
        srand(time(NULL));
        double randomScreenX = ((double)rand() / ((double)RAND_MAX + 1) * (GAME_WINDOW_WIDTH-40));
        double randomScreenY = ((double)rand() / ((double)RAND_MAX + 1) * (GAME_WINDOW_HEIGHT-40));
        Entity_setPosition(egg,randomScreenX, randomScreenY);
    }
}

void Game_render() {
    SDL_RenderClear(Window_getRenderer());
    Sprite_render(Entity_getSprite(egg), Entity_getPosition(egg), Window_getRenderer());
    Sprite_render(Entity_getSprite(player), Entity_getPosition(player), Window_getRenderer());
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
        SDL_Delay(10);
        ++frames;
        printf("average fps : %f\n", frames/((SDL_GetTicks()-start)/1000.0));
    }
    Entity_deconstruct(player);
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
