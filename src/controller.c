#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "controller.h"
#include "../lib/uthash.h"

Command * keyMap = NULL;

struct Command {
    int key;
    Sprite * sprite;
    void (*execute)(Sprite * sprite);
    UT_hash_handle hh;
};

Command * Controller_mapKey(Command * command, int key) {
    Command * oldCommand;
    command->key = key;
    HASH_REPLACE_INT(keyMap, key, command, oldCommand);
    return oldCommand;
}

Command * Controller_createCommand(Sprite * sprite, void (*execute)(Sprite * sprite)) {
    Command * cmd = malloc(sizeof(Command));
    cmd->sprite = sprite;
    cmd->execute = execute;
    return cmd;
}

Command * Controller_getCommand(int key) {
    Command * found;
    HASH_FIND_INT(keyMap,&key,found);
    if(found == NULL) {
        printf("NO COMMAND FOUND\n");
    }
    return found;
}

void Controller_destroy() {
    Command *current, *temp;
    HASH_ITER(hh, keyMap, current, temp) {
        HASH_DEL(keyMap,current);
        free(current);
    }
    keyMap = NULL;
}

void Controller_handleKeyDown(SDL_Event * e) {
    if(e.key.repeat==0) {
       Command * cmd = Controller_getCommand(e.key.keysym.sym);
       if(cmd != NULL) {
            cmd->execute(cmd->sprite);
       } 
    }
}

void Controller_handleKeyUp(SDL_Event * e) {
    if(e.key.repeat==0) {
       Command * cmd = Controller_getCommand(e.key.keysym.sym);
       if(cmd != NULL) {
            cmd->execute(cmd->sprite);
       } 
    }
}
