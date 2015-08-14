#ifndef WINDOW_DEFINITION
#define WINDOW_DEFINITION

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

SDL_Window * Window_getWindow();
SDL_Renderer * Window_getRenderer();
bool Window_init(const char * title, const int width, const int height);
void Window_setSize(int w, int h);
void Window_getSize(int * w, int * h);
void Window_setFullScreen();
void Window_destroy();

#endif
