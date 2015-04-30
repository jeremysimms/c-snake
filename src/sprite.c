#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"
#include <unistd.h>

static const int MAX_VELOCITY = 2;

struct sprite {
    
    int position[2];
    int velocity[2];
    
    int width;
    int height;
    
    SDL_Surface * spriteSheet;
};

Sprite * Sprite_create(int w, int h, char * image) {
    Sprite * sprite = malloc(sizeof(Sprite));
    sprite->position[0] = 0;
    sprite->position[1] = 0;
    sprite->height = h;
    sprite->width = w;
    sprite->velocity[0] = 0;
    sprite->velocity[1] = 0;
    sprite->spriteSheet = IMG_Load(image);
    if(sprite->spriteSheet == NULL) {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s", cwd);
        printf("Unable to load spritesheet\n");
    }
    return sprite; 
}

SDL_Texture * Sprite_loadTexture(SDL_Renderer * renderer, Sprite * sprite) {
    SDL_Texture * texture;
    texture = SDL_CreateTextureFromSurface(renderer, sprite->spriteSheet);
    if(texture == NULL) {
        printf("Unable to create texture from spriteSheet! SDL Error: %s\n", SDL_GetError());
    }
    return texture;
}

void Sprite_destroy(Sprite *sprite) {
    SDL_FreeSurface(sprite->spriteSheet);
    sprite->spriteSheet = NULL;
    free(sprite);
}

void Sprite_update(Sprite *sprite) {
    sprite->position[0] += sprite->velocity[0];
    sprite->position[1] += sprite->velocity[1];
}

int * Sprite_getPosition(Sprite * sprite) {
    return sprite->position;
}

int * Sprite_getVelocity(Sprite * sprite) {
    return sprite->velocity;
}

int Sprite_getWidth(Sprite * sprite) {
    return sprite->width;
}

int Sprite_getHeight(Sprite * sprite) {
    return sprite->height;
}

void Sprite_render(Sprite *sprite, SDL_Renderer * renderer) {
    SDL_Rect screenPortion;
    screenPortion.x = sprite->position[0];
    screenPortion.y = sprite->position[1];
    screenPortion.w = sprite->width;
    screenPortion.h = sprite->height;
    SDL_Texture * texture = Sprite_loadTexture(renderer, sprite);
    SDL_RenderCopy(renderer, texture, NULL, &screenPortion);
    SDL_DestroyTexture(texture);
    texture = NULL;
}

void Sprite_setPosition(Sprite * sprite, int x, int y) {
   sprite->position[0] = x;
   sprite->position[1] = y;
}

void Sprite_setVelocity(Sprite * sprite, int v_x, int v_y) {
    sprite->velocity[0] = v_x;
    sprite->velocity[1] = v_y;
}
