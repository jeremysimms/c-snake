#ifndef ENTITY_DEFINITION
#define ENTITY_DEFINITION

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>

#include "sprite.h"

typedef struct entity {
    double position[2];
    int velocity[2];
    Sprite * sprite;
    
    int collisionOffsetW;
    int collisionOffsetH;

    int collisionOffsetX;
    int collisionOffsetY;

    int lastUpdateTicks;
} Entity;

Entity * Entity_construct(double position[2], int velocity[2], Sprite * sprite);

void Entity_moveUp(Entity * entity);
void Entity_moveDown(Entity * entity);
void Entity_moveLeft(Entity * entity);
void Entity_moveRight(Entity * entity);

void Entity_setVelocity(Entity * entity, int v_x, int v_y);
void Entity_setPosition(Entity * entity, double x, double y);

int * Entity_getVelocity(Entity * entity);
double * Entity_getPosition(Entity * entity);

int Entity_getWidth(Entity * entity);
int Entity_getHeight(Entity * entity);

int Entity_getOffsetY(Entity * entity);
int Entity_getOffsetX(Entity * entity);

int Entity_getOffsetW(Entity * entity);
int Entity_getOffsetH(Entity * entity);

Sprite * Entity_getSprite(Entity * entity);

void Entity_update(Entity * entity);
void Entity_deconstruct(Entity * entity); 

#endif
