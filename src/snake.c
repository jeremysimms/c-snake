#include <stdio.h>
#include <stdbool.h>
#include "entity.h"
#include "snake.h"
#include "sprite.h"
#include "window.h"

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

Sprite * sprite = NULL;
Snake * head = NULL;
Snake * tail = NULL;
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
        head = Snake_removeTail();
        head->next = tempHead;
        Entity_setPosition(head->entity, x, y);
        tail = Snake_getTail();
        ticks = SDL_GetTicks();
    }
}

void Snake_truncate(int length) {
    Snake * curr = head;
    int count;
    while(curr->next != NULL) {
        if(count >= length) {
           Snake * delete = curr;
           free(delete);
        }
        curr = curr->next;
        count++;
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
    Snake * newTail = malloc(sizeof(Snake));
    double x = 0;
    double y = 0;
    Snake_getNewCoords(&x, &y);
    double position[2] = { x , y };
    int velocity[2] = { 0, 0 };
    Entity * newEntity = Entity_construct(position, velocity, sprite);
    newTail->entity = newEntity;
    newTail->next = NULL;
    tail->next = newTail;
    tail = newTail;
}

void Snake_moveUp(void * snake) {
    if(current != DOWN) {
        current = UP;
    }
}

void Snake_moveDown(void * snake) {
    if(current != UP) {
        current = DOWN;
    }
}

void  Snake_moveLeft(void * snake) {
    if(current != RIGHT) {
        current = LEFT;
    }
}

void Snake_moveRight(void * snake) {
    if(current != LEFT) {
        current = RIGHT;
    }
}

void Snake_destroy() {
    Snake * curr = head;
    while(curr->next != NULL) {
        if(curr->entity != NULL) {
            Entity_deconstruct(head->entity);
        }
        Snake * delete = curr;
        free(delete);
        curr = curr->next;
    }
    free(curr);
    curr = NULL;
    head = NULL;
}

void Snake_render() {
    Snake * curr = head;
    while(curr->next != NULL) {
        Sprite_render(Entity_getSprite(curr->entity), Entity_getPosition(curr->entity), Window_getRenderer());
        curr = curr->next;
    }
}

Snake * Snake_create(Sprite * snakeSprite, double position[2]) {
    sprite = snakeSprite;
    head = malloc(sizeof(Snake));
    int velocity[2] = { 0,0 };
    head->entity = Entity_construct(position, velocity, sprite);
    head->next = NULL;
    tail = head;
    Snake_add();
    Snake_add();
    Snake_add();
    return head;
}