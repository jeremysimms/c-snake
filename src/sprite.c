#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "sprite.h"
#include "window.h"

static const int MAX_VELOCITY = 2;

struct sprite {
    int width;
    int height;
    
    SDL_Surface * spriteSheet;
    SDL_Texture * texture;
};

int Sprite_getWidth(Sprite * sprite) {
    return sprite->width;
}

int Sprite_getHeight(Sprite * sprite) {
    return sprite->height;
}

Sprite * Sprite_create(int w, int h, char * image) {
    Sprite * sprite = malloc(sizeof(Sprite));
    sprite->height = h;
    sprite->width = w;
    sprite->spriteSheet = IMG_Load(image);
    sprite->texture =  SDL_CreateTextureFromSurface(Window_getRenderer(), sprite->spriteSheet);
    if(sprite->spriteSheet == NULL) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s", cwd);
        printf("Unable to load spritesheet\n");
    }
    return sprite; 
}

void Sprite_destroy(Sprite *sprite) {
    SDL_FreeSurface(sprite->spriteSheet);
    SDL_DestroyTexture(sprite->texture);
    sprite->spriteSheet = NULL;
    sprite->texture = NULL;
    free(sprite);
}

void Sprite_render(Sprite *sprite, double * position, SDL_Renderer * renderer) {
    SDL_Rect screenPortion;
    screenPortion.x = (int) position[0];
    screenPortion.y = (int) position[1];
    screenPortion.w = sprite->width;
    screenPortion.h = sprite->height;
    SDL_RenderCopy(renderer, sprite->texture, NULL, &screenPortion);
}

