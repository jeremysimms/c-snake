
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int MAX_VELOCITY = 2;

struct Sprite {
    int x;
    int y;
    int w;
    int h;
    int v_x;
    int v_y;
    
    char * path;

    int upKey;
    int downKey;
    int leftKey;
    int rightKey;

    SDL_Surface * surface;
};

void gameLoop(SDL_Window * window);
struct Sprite createSprite(char * image, int w, int h);
SDL_Rect createScaleRect(struct Sprite * sprite);
int processEvents(struct Sprite * sprite);
void incrementVelocity(struct Sprite * sprite, int key);
void decrementVelocity(struct Sprite * sprite, int key);
void moveSprite(struct Sprite * sprite);


int main(int argc, char * args[]) {
    SDL_Window * window = NULL;
    if(SDL_Init(SDL_INIT_VIDEO)<0) 
    {
        printf("SDL Could not be initialized! SDL Error %s\n", SDL_GetError());
    }
    else 
    {
        window = SDL_CreateWindow("Pac Man", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
        if(window == NULL) 
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) & imgFlags)) {
                printf("SDL Image Library failed to load. ERROR: %s\n", IMG_GetError());
            }
            else {
                gameLoop(window);
            }
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 0;
        }
    }
}

struct Sprite createSprite(char * image, int w, int h) {
    struct Sprite sprite;
    sprite.x = SCREEN_WIDTH/2-(w/2);
    sprite.y = SCREEN_HEIGHT/2-(h/2);
    sprite.h = h;
    sprite.w = w;
    sprite.v_y = 0;
    sprite.v_x = 0;
    sprite.upKey = SDLK_UP;
    sprite.downKey = SDLK_DOWN;
    sprite.leftKey = SDLK_LEFT;
    sprite.rightKey = SDLK_RIGHT;
    sprite.surface = IMG_Load(image);
    if(sprite.surface == NULL) {
        printf("Could not load image. ERROR:%s\n", IMG_GetError());
    }
    return sprite; 
}

SDL_Rect createScaleRect(struct Sprite * sprite) {
    SDL_Rect stretchRect;
    stretchRect.x = sprite->x;
    stretchRect.y = sprite->y;
    stretchRect.w = sprite->w;
    stretchRect.h = sprite->h;
    return stretchRect;
}

void gameLoop(SDL_Window * window) {
    int quit = 0;
    SDL_Surface * wSurface = NULL;
    wSurface = SDL_GetWindowSurface(window);
    struct Sprite sprite = createSprite("image.png", 50, 50);
    while(quit == 0) {
        quit = processEvents(&sprite);
        moveSprite(&sprite);
        SDL_FillRect(wSurface, NULL, SDL_MapRGB(wSurface->format,0xFF,0xFF,0xFF));
        SDL_Rect stretchRect = createScaleRect(&sprite);
        SDL_BlitScaled(sprite.surface, NULL, wSurface, &stretchRect);
        SDL_UpdateWindowSurface(window);
    }
    SDL_FreeSurface(sprite.surface);
    SDL_FreeSurface(wSurface);
}
void incrementVelocity(struct Sprite * sprite, int key) {
    if(key == sprite->upKey) {
        sprite->v_y -= MAX_VELOCITY;
    }
    if(key == sprite->downKey) {
        sprite->v_y += MAX_VELOCITY;
    }
    if(key == sprite->leftKey) {
        sprite->v_x -= MAX_VELOCITY;
    }
    if(key == sprite->rightKey) {
        sprite->v_x += MAX_VELOCITY;
    }
}

void decrementVelocity(struct Sprite * sprite, int key) {
    if(key == sprite->upKey) {
        sprite->v_y += MAX_VELOCITY;
    }
    if(key == sprite->downKey) {
        sprite->v_y -= MAX_VELOCITY;
    }
    if(key == sprite->leftKey) {
        sprite->v_x += MAX_VELOCITY;
    }
    if(key == sprite->rightKey) {
        sprite->v_x -= MAX_VELOCITY;
    }
}

void moveSprite(struct Sprite * sprite) {
    sprite->x += sprite->v_x;
    sprite->y += sprite->v_y;
    if(sprite->x < 0) {
        sprite->x = 0;
    }
    if((sprite->x + sprite->w) > SCREEN_WIDTH) {
        sprite->x = SCREEN_WIDTH-sprite->w;
    }
    if(sprite->y < 0) {
        sprite->y = 0;
    }
    if(sprite->y + sprite->h > SCREEN_HEIGHT) {
        sprite->y = SCREEN_HEIGHT-sprite->h;
    }
}

int processEvents(struct Sprite * sprite) {
    SDL_Event e;
    int quit = 0;
    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT) {
            quit = 1;
        } else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            incrementVelocity(sprite, e.key.keysym.sym);
        } else if(e.type == SDL_KEYUP && e.key.repeat == 0) {
            decrementVelocity(sprite, e.key.keysym.sym);
        }
    }
    return quit; 
}
