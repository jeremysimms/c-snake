#include <stdio.h>
#include <stdbool.h>
#include "entity.h"
#include "snake.h"
#include "sprite.h"
#include "window.h"
#include "collision.h"

struct snake {
    Entity * entity;
    Snake * next;
};

typedef enum {
    LEFT,
    RIGHT,
    UP,
    DOWN
} Direction;

Sprite * headSprite = NULL;
Sprite * bodySprite = NULL;
Snake * head = NULL;
Snake * tail = NULL;
int segmentsToAdd = 0;
int length = 0;
Direction current = DOWN;
Uint32 ticks = 0;
Snake * Snake_getTail();
Snake * Snake_removeTail();
void Snake_getNewCoords(double * x, double * y);

void Snake_update() {
    if(SDL_GetTicks() - ticks >= 100) {
        double x = 0;
        double y = 0;
        Snake_getNewCoords(&x, &y);
        Snake * tempHead = head;
        if(length > 1) {
            tempHead->entity->sprite = bodySprite;
        }
        if(segmentsToAdd == 0 && length > 1) {
            head = Snake_removeTail();
            head->entity->sprite = headSprite;
            head->next = tempHead;
        } else if(segmentsToAdd > 0) {
            segmentsToAdd--;
            length++; 
            head = malloc(sizeof(Snake));
            int velocity[2] = { 0, 0 };
            double position[2] = { x, y };
            Entity * newEntity = Entity_construct(position, velocity, headSprite);
            head->entity = newEntity;
            head->next = tempHead;
        }
        Entity_setPosition(head->entity, x, y);
        tail = Snake_getTail();
        ticks = SDL_GetTicks();
    }
}

Snake * Snake_removeTail() {
    Snake * curr = head;
    Snake * prev = NULL;
    while(curr->next != NULL) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = NULL;
    return curr;
}

Entity * Snake_getHead() {
    return head->entity;
}

void Snake_getNewCoords(double * x, double * y) {
    double * headPositionLast = Entity_getPosition(head->entity);
    int width = Entity_getWidth(head->entity);
    int height = Entity_getHeight(head->entity);
    switch(current) {
        case LEFT:
            (*x) = headPositionLast[0] - width;
            (*y) = headPositionLast[1];
            break;
        case RIGHT:
            (*x) = headPositionLast[0] + width;
            (*y) = headPositionLast[1];
            break;
        case UP:
            (*x) = headPositionLast[0];
            (*y) = headPositionLast[1] - height;
            break;
        case DOWN:
            (*x) = headPositionLast[0];
            (*y) = headPositionLast[1] + height;
            break;
    }
}

Snake * Snake_getTail() {
    Snake * curr =  head;
    while(curr->next != NULL) {
        curr = curr->next;
    }
    return curr;
}

void Snake_add() {
    if(segmentsToAdd < 4) {
        segmentsToAdd++;
    }
}

void Snake_moveUp(void * snake) {
    if(current != DOWN || length == 1) {
        current = UP;
    }
}

void Snake_moveDown(void * snake) {
    if(current != UP || length == 1) {
        current = DOWN;
    }
}

void  Snake_moveLeft(void * snake) {
    if(current != RIGHT || length == 1) {
        current = LEFT;
    }
}

void Snake_moveRight(void * snake) {
    if(current != LEFT || length == 1) {
        current = RIGHT;
    }
}

void Snake_destroy() {
    Snake * curr = head;
    while(curr->next != NULL) {
        if(curr->entity != NULL) {
            Entity_deconstruct(curr->entity);
        }
        Snake * delete = curr;
        free(delete);
        curr = curr->next;
    }
    free(curr);
    curr = NULL;
    head = NULL;
    length = 0; 
}

void Snake_render() {
    Snake * curr = head;
    Sprite_render(Entity_getSprite(curr->entity), Entity_getPosition(curr->entity), Window_getRenderer());
    while(curr->next != NULL) {
        Sprite_render(Entity_getSprite(curr->entity), Entity_getPosition(curr->entity), Window_getRenderer());
        curr = curr->next;
    }
    if(length > 1) {
        Sprite_render(Entity_getSprite(curr->entity), Entity_getPosition(curr->entity), Window_getRenderer());
    }
}

Snake * Snake_create(Sprite * headSpr, Sprite * bodySpr, double position[2]) {
    headSprite = headSpr;
    bodySprite = bodySpr;
    head = malloc(sizeof(Snake));
    int velocity[2] = { 0,0 };
    head->entity = Entity_construct(position, velocity, headSprite);
    printf("sprite position x: %f\n", position[0]);
    printf("sprite position y: %f\n", position[1]);
    head->next = NULL;
    tail = head;
    length = 1; 
    return head;
}

bool Snake_checkCollisions() {
    if(length > 1) {
        Snake * curr = head->next;
        while(curr->next != NULL) {
            if(Collision_checkEntities(curr->entity, head->entity)) {
                return true;
            }
            curr = curr->next;
        }
        return Collision_checkEntities(curr->entity, head->entity);
    }
    return false; 
}
