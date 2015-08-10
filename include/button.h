#ifndef BUTTON_DEFINITION
#define BUTTON_DEFINITION

#include <stdio.h>
#include <stdlib.h>
#include "sprite.h"
#include "window.h"

typedef struct texture_position {
    int x;
    int y;
} * TexturePosition;

typedef struct button {
    Sprite * sprite;
    double screenPosX;
    double screenPosY;
    TexturePosition up;
    TexturePosition over;
    TexturePosition down;
    TexturePosition * curr;
    void (*action)(void * args); 
} * Button;

Button Button_create(Sprite * sprite, double screenPosX, double screenPosY);
void Button_render(Button button);

#endif
