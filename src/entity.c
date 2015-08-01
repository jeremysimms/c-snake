#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sprite.h"
#include "entity.h"

Entity * Entity_construct(double position[2], int velocity[2], Sprite * sprite) {
    Entity * entity = malloc(sizeof(Entity));
    entity->sprite = sprite;
    entity->position[0] = position[0];
    entity->position[1] = position[1];
    entity->velocity[0] = velocity[0];
    entity->velocity[1] = velocity[1];
    entity->collisionOffsetW = Sprite_getWidth(sprite);
    entity->collisionOffsetH = Sprite_getHeight(sprite);
    entity->collisionOffsetX = 0;
    entity->collisionOffsetY = 0;
    entity->lastUpdateTicks = 0;
    return entity;
}

void Entity_deconstruct(Entity * entity) {
    if(entity != NULL) {
        free(entity);
    }
}

void Entity_update(Entity * entity) {
    int elapsedTime = SDL_GetTicks() - entity->lastUpdateTicks;
    entity->position[0] += (double)(entity->velocity[0]/1000.0)*elapsedTime;
    entity->position[1] += (double) (entity->velocity[1]/1000.0)*elapsedTime;
    printf("POSITION: x: %f, y: %f\n",entity->position[0], entity->position[1]); 
    entity->lastUpdateTicks = SDL_GetTicks();
}

Sprite * Entity_getSprite(Entity * entity) {
    return entity->sprite;
}

double * Entity_getPosition(Entity * entity) {
    return entity->position;
}

int * Entity_getVelocity(Entity * entity) {
    return entity->velocity;
}

int Entity_getWidth(Entity * entity) {
    return Sprite_getWidth(entity->sprite);
}

int Entity_getHeight(Entity * entity) {
    return Sprite_getHeight(entity->sprite);
}

int Entity_getOffsetW(Entity * entity) {
    return entity->collisionOffsetW;
}

int Entity_getOffsetH(Entity * entity) {
    return entity->collisionOffsetH;
}
int Entity_getOffsetX(Entity * entity) {
    return entity->collisionOffsetX;
}

int Entity_getOffsetY(Entity * entity) {
    return entity->collisionOffsetY;
}

void Entity_setPosition(Entity * entity, double x, double y) {
   entity->position[0] = x;
   entity->position[1] = y;
}

void Entity_setVelocity(Entity * entity, int v_x, int v_y) {
    entity->velocity[0] = v_x;
    entity->velocity[1] = v_y;
}

