#include "window.h"
#include <stdio.h>

const int DEFAULT_WINDOW_WIDTH = 800;
const int DEFAULT_WINDOW_HEIGHT = 600;
int window_width = DEFAULT_WINDOW_WIDTH;
int window_height = DEFAULT_WINDOW_HEIGHT;

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

SDL_Window * Window_getWindow() {
    if(window == NULL) {
        printf("ERROR: Window has not been initialized!\n");
    }
    return window;
}

SDL_Window * Window_createWindow(char * title) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,window_width,window_height,SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("ERROR: Window has not been initialized!\n");
    }
    return window; 
}

SDL_Renderer * Window_createScreenRenderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("ERROR: renderer has not been initialized!\n");
    } else {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
    return renderer;
}

void Window_init() {
    int imgFlags = IMG_INIT_PNG; 
    //TODO: Move intialization to window library. 
    if((SDL_Init(SDL_INIT_VIDEO)<0) ) {
        printf("SDL Could not be initialized! SDL Error %s\n", SDL_GetError());
    }
    else if(!(IMG_Init(imgFlags)) & imgFlags) {
        printf("SDL Image Library failed to load. ERROR: %s\n", IMG_GetError());
    } 
}

SDL_Renderer * Window_getRenderer() {
    if(renderer == NULL) {
        printf("ERROR: Renderer has not been initialized!\n");
    }
    return renderer;
}

void Window_getSize(int * w, int * h) {
    SDL_GetWindowSize(window, w, h);
}

void Window_setSize(int * width, int * height) {
    SDL_SetWindowSize(window, width, height);
}

void Window_setFullScreen() {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Window_destroy() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

