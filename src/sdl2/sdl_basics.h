#ifndef _SDL_BASICS
#define _SDL_BASICS


#define TOMICROSECONDS 100000

#define DEVMODE true        /// ATIVA TESTE DE POSICAO (true atico, false inativo)

#include <stdio.h>
#include <stdlib.h> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/* SET VALUE TO OFFSET */
bool set_sdlRect(SDL_Rect *offset, int x, int y);

/* SET VALUE TO SURFACE */
bool set_sdlSurface(SDL_Surface** surface, const char *str, bool bmp);

/* SET TTF_FONT -- not working yet */
bool set_sdlFont(TTF_Font **font, const char *font_type, int font_size);

/* FREE SURFACE */
bool freeSDL_Surface(SDL_Surface** surface);

/* CLEAN UP EVERTHING */
bool clean_up(SDL_Surface **surface, int *ptr, int qtde);

/* LOAD UP EVERTHING */
bool load_files(SDL_Surface **surface, const char **str, int qtde);
#endif
