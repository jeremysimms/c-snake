#include <stdio.h>
#include <stdbool.h>
#include "sprite.h"
#include "entity.h"

typedef struct Command Command;

Command * Controller_createCommand(Entity * entity, void (*commandFunc)(Entity * entity));
Command * Controller_mapKey(Command * command, int key);
void Controller_handleKeyDown(SDL_Event * e);
void Controller_handleKeyUp(SDL_Event * e);
void Controller_destroy();
void Controller_poll(SDL_Event * e);

