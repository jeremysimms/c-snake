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

TexturePosition createTexturePosition(int x, int y);
Button Button_create(Sprite * sprite, double screenPosX, double screenPosY);
void Button_render(Button button);

Button Button_create(Sprite * sprite, double screenPosX, double screenPosY) {
    Button button = malloc(sizeof(Button));
    button->up = createTexturePosition(0,0);
    int w = Sprite_getWidth(sprite);
    button->over = createTexturePosition(w, 2);
    button->down = createTexturePosition(w*2,0);
    button->curr = &button->up;
    button->screenPosX = screenPosX;
    button->screenPosY = screenPosY;
    return button;
}

void Button_setAction(Button btn, void (*action)(void * args)){
    btn->action = action;
}

void Button_render(Button button) {
    int x = (*button->curr)->x;
    int y = (*button->curr)->y;
    double pos[2]  = { button->screenPosX, button->screenPosY };
    Sprite_setTextureCoords(button->sprite, x, y);
    Sprite_render(button->sprite,pos,Window_getRenderer());
}

TexturePosition createTexturePosition(int x, int y) {
    TexturePosition tex = malloc(sizeof(TexturePosition));
    tex->x = x;
    tex->y = y;
    return tex;
}

void Button_highlight(Button button) {
    button->curr = &button->over;    
}
