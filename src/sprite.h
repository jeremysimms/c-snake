#ifndef SPRITE_DEFINITION
#define SPRITE_DEFINITION

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct sprite Sprite;

Sprite * Sprite_create(int w, int h, char * spritesheet);

void Sprite_destroy(Sprite * sprite);
void Sprite_render(Sprite * sprite, double * position, SDL_Renderer * renderer);

int Sprite_getWidth(Sprite * sprite);
int Sprite_getHeight(Sprite * sprite);

#endif