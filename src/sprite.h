#ifndef SPRITE_DEFINITION
#define SPRITE_DEFINITION

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct sprite Sprite;

Sprite * Sprite_create(int w, int h, char * spritesheet);
void Sprite_destroy(Sprite * sprite);
void Sprite_update(Sprite * sprite);
void Sprite_render(Sprite * sprite, SDL_Renderer * renderer);

void Sprite_moveUp(Sprite * sprite);
void Sprite_moveDown(Sprite * sprite);
void Sprite_moveLeft(Sprite * sprite);
void Sprite_moveRight(Sprite * sprite);

void Sprite_setVelocity(Sprite * sprite, int v_x, int v_y);
void Sprite_setPosition(Sprite * sprite, int x, int y);

int * Sprite_getVelocity(Sprite * sprite);
int * Sprite_getPosition(Sprite * sprite);
int Sprite_getWidth(Sprite * sprite);
int Sprite_getHeight(Sprite * sprite);
SDL_Rect createScaleRect(Sprite * sprite);

#endif
