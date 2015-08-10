#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>


typedef struct color {
    Uint8 R;
    Uint8 G;
    Uint8 B;
} * Color;

void colorTop(Uint32 * pixels, int w, int h, int rows,  Color color);
void colorLeft(Uint32 * pixels, int w, int h, int rows, Color color);
void colorRight(Uint32 * pixels, int w, int h, int rows, Color color);
void colorBottom(Uint32 * pixels, int w, int h, int rows, Color color);

SDL_Texture * createButtonTexture(Color primary) {
    double r_prime = primary->R/255;
    double g_prime = primary->G/255;
    double b_prime = primary->B/255;

    double c_max = fmax(r_prime,g_prime);
    c_max = fmax(c_max, b_prime);

    double c_min = fmin(r_prime,g_prime);
    c_min = fmin(c_min, b_prime);
    
    double H;
    double S;
    double V = c_max;
    double delta = c_max - c_min;
    if(r_prime > g_prime && r_prime > b_prime) { 
        H = 60 * (fmod( ((g_prime - b_prime)/delta), 6));
    }
    else if ( g_prime > r_prime && g_prime > b_prime) {
        H = 60 * ((b_prime - r_prime)/delta+2);
    }
    else if( b_prime > r_prime && b_prime > g_prime) {
        H = 60 * ((r_prime - g_prime)/delta+4);
    }
    else {
        H = 0;
    }
    if(c_max != 0) {
        S = delta/c_max;
    } else {
        S = 0;
    }
}

Uint32 darkenColor(Color color) {

}

Uint32 lightenColor(Color color) {

}

SDL_Surface * createSurface(int w, int h, Color color) {
    SDL_Surface * surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0,0,0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format,color->R, color->G, color->B));
    Uint32 *pixels = (Uint32*) surface->pixels;
    colorTop(pixels, w, h, 3, color);
    return surface;
}

void colorBottom(Uint32 * pixels, int w, int h, int rows, Color color) {

}

void colorLeft(Uint32 * pixels, int w, int h, int rows, Color color) {

}

void colorRight(Uint32 * pixels, int w, int h, int rows, Color color) {

}

void colorTop(Uint32 * pixels, int w, int h, int rows, Color color) {
    for(int i = 0; i < rows; i++) {
        for(int j = 0+i; j < w-i; j++) {
            pixels[i*w+j+i] = lightenColor(color);
        }
    }
}
