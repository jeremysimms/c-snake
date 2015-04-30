#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "sprite.h"
#include "controller.h"


SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

bool hasQuit() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT) {
            return true;
        }
    }
    return false;
}

void moveSpriteUp(Sprite * sprite) {
    Sprite_setVelocity(sprite, 0, -5); 
}

void moveSpriteDown(Sprite * sprite) {
    Sprite_setVelocity(sprite, 0, 5); 
}

void moveSpriteLeft(Sprite * sprite) {
    Sprite_setVelocity(sprite, -5, 0); 
}

void moveSpriteRight(Sprite * sprite) {
    Sprite_setVelocity(sprite, 5, 0); 
}

void checkBoundCollision(Sprite * sprite) {
    int * position = Sprite_getPosition(sprite);
    int width = Sprite_getWidth(sprite);
    int height = Sprite_getHeight(sprite);
    if(position[0] <= 0 ) { 
        Sprite_setPosition(sprite, 0, position[1]);
    } else if((position[0]+width) >= 800) {
        Sprite_setPosition(sprite, 800-width, position[1]);
    }

    if(position[1] <= 0 ) {
        Sprite_setPosition(sprite, position[0], 0);
    } else if(position[1]+height >= 600) {
        Sprite_setPosition(sprite, position[0], 600-height);
    }
}

int main(int argc, char * argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("FAILED");
    } else {
        window = SDL_CreateWindow("Testing Sprites Module", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800,600,SDL_WINDOW_SHOWN);
        if(window == NULL) {
            printf("FAILED\n");
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
            int imgFlags = IMG_INIT_PNG;
            if(imgFlags & !(IMG_Init(imgFlags))) {
                printf("FAILED\n");
            } else {
                bool quit = false;
                Sprite * sprite = Sprite_create(50, 50, "res/img/image.png");
                Sprite_setVelocity(sprite, 1,1);
                int ticksCurrent = SDL_GetTicks();
                int ticksLast = SDL_GetTicks();
                Command * moveUp = Controller_createCommand(sprite,&moveSpriteUp);
                Command * moveDown = Controller_createCommand(sprite,&moveSpriteDown);
                Command * moveLeft = Controller_createCommand(sprite,&moveSpriteLeft);
                Command * moveRight = Controller_createCommand(sprite,&moveSpriteRight);
                Controller_mapKey(moveUp, SDLK_UP);
                Controller_mapKey(moveDown, SDLK_DOWN);
                Controller_mapKey(moveLeft, SDLK_LEFT);
                Controller_mapKey(moveRight, SDLK_RIGHT);
                while(!quit) {
                    ticksCurrent = SDL_GetTicks();
                    quit = Controller_poll();
                    if(ticksCurrent - ticksLast >= (1000/60)) {
                        SDL_RenderClear(renderer);
                        Sprite_update(sprite);
                        checkBoundCollision(sprite);
                        Sprite_render(sprite,renderer);
                        SDL_RenderPresent(renderer);
                        ticksLast = ticksCurrent;
                    }
                }
                Sprite_destroy(sprite);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                Controller_destroy();
                renderer = NULL;
                window = NULL;
                sprite = NULL;
            }
        }
    }
}
