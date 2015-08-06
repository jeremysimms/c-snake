#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include "sprite.h"
#include "window.h"

static const int MAX_VELOCITY = 2;

struct sprite {
    int width;
    int height;
    int textureX;
    int textureY;
    SDL_Texture * texture;
};

int Sprite_getWidth(Sprite * sprite) {
    return sprite->width;
}

int Sprite_getHeight(Sprite * sprite) {
    return sprite->height;
}

Sprite * Sprite_create(int w, int h, SDL_Texture * texture) {
    Sprite * sprite = malloc(sizeof(Sprite));
    sprite->height = h;
    sprite->width = w;
    sprite->textureX = 0;
    sprite->textureY = 0;
    sprite->texture = texture;
    return sprite; 
}

void Sprite_setTextureCoords(Sprite * sprite, int textureX, int textureY) {
    sprite->textureX = textureX;
    sprite->textureY = textureY;
}

void Sprite_destroy(Sprite *sprite) {
    if(sprite != NULL) {
        sprite->texture = NULL;
        free(sprite);
    }
}

void Sprite_render(Sprite *sprite, double * position, SDL_Renderer * renderer) {
    SDL_Rect screenPortion;
    screenPortion.x = (int) position[0];
    screenPortion.y = (int) position[1];
    screenPortion.w = sprite->width;
    screenPortion.h = sprite->height;
    SDL_Rect texturePortion;
    texturePortion.x = sprite->textureX;
    texturePortion.y = sprite->textureY;
    texturePortion.w = sprite->width;
    texturePortion.h = sprite->height;
    SDL_RenderCopy(renderer, sprite->texture, &texturePortion, &screenPortion);
}

