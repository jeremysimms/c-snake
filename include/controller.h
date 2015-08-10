#include <stdio.h>
#include <stdbool.h>
#include "sprite.h"
#include "entity.h"

typedef struct Command Command;

Command * Controller_createCommand(void * entity, void (*commandFunc)(void * entity));
Command * Controller_mapKey(Command * command, int key);
void Controller_handleKeyDown(SDL_Event * e);
void Controller_handleKeyUp(SDL_Event * e);
void Controller_destroy();

