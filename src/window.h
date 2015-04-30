#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Window * Window_getWindow();
SDL_Renderer * Window_createScreenRenderer() {
SDL_Renderer * Window_getRenderer() {
SDL_Window * Window_createWindow();
void Window_setSize(int * w, int * h);
void Window_getSize(int * w, int * h);
void Window_setFullScreen();
void Window_destroy();

