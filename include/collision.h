#ifndef COLLISION_DEFINITION
#define COLLISION_DEFINITION

#include <stdio.h>
#include <stdbool.h>
#include "entity.h"

typedef enum wall_collision_type{
    LEFT_WALL_COLLISION,
    RIGHT_WALL_COLLISION,
    TOP_WALL_COLLISION,
    BOTTOM_WALL_COLLISION,
    NO_WALL_COLLISION,
} WallCollisionType;

typedef enum entity_collision_side {
    LEFT_SIDE,
    RIGHT_SIDE,
    TOP_SIDE,
    BOTTOM_SIDE
} EntityCollisionSide;

bool Collision_checkEntities(Entity * entity1, Entity * entity2);
bool Collision_checkWalls(Entity * entity);

#endif
