#ifndef SNAKE_DEFINITION
#define SNAKE_DEFINITION

#include <stdio.h>
#include <stdbool.h>
#include "entity.h"
#include "sprite.h"

typedef struct snake Snake;

void Snake_update();
void Snake_moveUp(void * snake);
void Snake_moveDown(void * snake);
void Snake_moveLeft(void * snake);
void Snake_moveRight(void * snake);
void Snake_destroy();
Snake * Snake_create(Sprite * snakeSprite,Sprite * bodySprite, double position[2]);
void Snake_render();
void Snake_add();
Entity * Snake_getHead();
#endif
