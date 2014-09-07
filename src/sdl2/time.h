#ifndef _TIME
#define _TIME

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include "point.cpp"

typedef struct Player player;	// Players - pode se mover
typedef struct Object object;	// Objetos - fixos

int time();

void setPlayer(player *p, int ipx, int ipy, int vx, int vy);

void setObject(Object *o, int px, int py, bool a);

#endif // personagem
