#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

SDL_Window * window = NULL;
SDL_Renderer * renderer = NULL;

SDL_Window * Window_getWindow() {
    if(window == NULL) {
        printf("ERROR: Window has not been initialized!\n");
    }
    return window;
}

SDL_Window * Window_createWindow(const char * windowTitle, const int windowWidth, const int windowHeight) {
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windowWidth,windowHeight,SDL_WINDOW_SHOWN);
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

bool Window_init(const char * title, const int width, const int height) {
    int imgFlags = IMG_INIT_PNG; 
    if((SDL_Init(SDL_INIT_VIDEO)<0) ) {
        printf("SDL Could not be initialized! SDL Error %s\n", SDL_GetError());
        return false;
    }
    else if(!(IMG_Init(imgFlags)) & imgFlags) {
        printf("SDL Image Library failed to load. ERROR: %s\n", IMG_GetError());
        return false;
    } else {
        window = Window_createWindow(title, width, height);
        renderer = Window_createScreenRenderer();
        if(window == NULL || renderer == NULL) {
            return false;
        }
    }
    return true;
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

void Window_setSize(int width, int height) {
    SDL_SetWindowSize(window, width, height);
}

void Window_setFullScreen() {
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
}

void Window_destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

