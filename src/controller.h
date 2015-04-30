#include <stdio.h>
#include "sprite.h"
#include <stdbool.h>

typedef struct Command Command;

Command * Controller_createCommand(Sprite * sprite, void (*commandFunc)(Sprite * sprite));
Command * Controller_mapKey(Command * command, int key);
void Controller_handleKeyDown(SDL_Event * e);
void Controller_handleKeyUp(SDL_Event * e);
void Controller_destroy();
void Controller_poll(SDL_Event * e);

