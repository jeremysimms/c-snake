#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "debug.h"

bool Audio_init() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        debug_print("Error loading audio library. Mix error: %s\n", Mix_GetError());
        return false;
    }
    else return true;
}

void Audio_close() {
    Mix_Quit();
}
