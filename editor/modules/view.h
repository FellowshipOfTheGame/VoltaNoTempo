#ifndef _VIEW_H_
#define _VIEW_H_

// SIZE OF MATRIZ
#define COL 20
#define LIN 30

#define SQUARE_SIZE 20         // TAMANHO DO LADO DO QUADRADO

// EMPTY AND SELECT VALUES -- 1 - 9  is the images used by the editor
#define SELECT -2
#define EMPTY -1
#define WIDTH SQUARE_SIZE*COL
#define HEIGHT SQUARE_SIZE*LIN

#include "image.h"
#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


using namespace std;

class View {
private:
    SDL_Window *window;
    SDL_Surface *screen;
    SDL_Rect offset;

    void setOffset(int x, int y);
public:
    View();
    ~View();
    void update();
    void clear();
    void setImage(SDL_Surface **ptr, int x, int y);
    int getMenuSpace();
};

#endif
