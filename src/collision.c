#include <stdio.h>
#include <stdbool.h>
#include "entity.h"

bool Collision_checkEntities(Entity * entity1, Entity * entity2) {
    double * entity1Position = Entity_getPosition(entity1);
    double * entity2Position = Entity_getPosition(entity2);

    double entity1X = entity1Position[0] + Entity_getOffsetX(entity1);
    double entity1Y = entity1Position[1] + Entity_getOffsetY(entity1);

    double entity2X = entity2Position[0] + Entity_getOffsetX(entity2);
    double entity2Y = entity2Position[1] + Entity_getOffsetY(entity2);

    int entity1W = Entity_getOffsetW(entity1);
    int entity1H = Entity_getOffsetH(entity1);
    int entity2W = Entity_getOffsetW(entity2);
    int entity2H = Entity_getOffsetH(entity2);

    if(!(entity1X + entity1W < entity2X || entity1X > entity2X + entity2W)) {
        if(!(entity1Y + entity1H < entity2Y || entity1Y > entity2Y + entity2H)) {
            printf("ENTITY 1 X: %f\n", entity1Position[0]);
            printf("ENTITY 1 Y: %f\n", entity1Position[1]);

            printf("ENTITY 2 X: %f\n", entity2Position[0]);
            printf("ENTITY 2 Y: %f\n", entity2Position[1]);
            return true;
        }
    }
    return false;
}


bool Collision_checkWalls(Entity * entity) {

    double * position = Entity_getPosition(entity);
    int * velocity = Entity_getVelocity(entity);
    int width = Entity_getWidth(entity);
    int height = Entity_getHeight(entity);
    int windowWidth;
    int windowHeight; 
    Window_getSize(&windowWidth, &windowHeight);
    bool collisionDetected = false;
    if(position[0] < 0) {
        Entity_setPosition(entity, 0, position[1]);
        Entity_setVelocity(entity, -velocity[0], velocity[1]);
        collisionDetected = true;
    } else if(position[0] + width > windowWidth) {
        Entity_setPosition(entity, (windowWidth - width), position[1]);
        Entity_setVelocity(entity, -velocity[0], velocity[1]);
        collisionDetected = true;
    }
    if(position[1] < 0) {
        Entity_setPosition(entity, position[0], 0);
        Entity_setVelocity(entity, velocity[0], -velocity[1]);
        collisionDetected = true;
    }else if(position[1] + height > windowHeight) {
        Entity_setPosition(entity, position[0], windowHeight - height);
        Entity_setVelocity(entity, velocity[0], -velocity[1]);
        collisionDetected = true;
    }
    return collisionDetected;
}
