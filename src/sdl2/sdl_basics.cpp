#include "sdl_basics.h"

/* SET VALUE TO OFFSET */
bool set_sdlRect(SDL_Rect *offset, int x, int y) {
    (*offset).x = x;
    (*offset).y = y;
    return true;
}

/* SET VALUE TO SURFACE */
bool set_sdlSurface(SDL_Surface** surface, const char *str, bool bmp) {
    if (bmp) {
        *surface = SDL_LoadBMP(str);
    } else {
        *surface = IMG_Load(str);
    }
    return (*surface != NULL) ? true : false;

}

/* SET TTF_FONT */
bool set_sdlFont(TTF_Font **font, const char *font_type, int font_size) {
    
    *font = NULL;
    TTF_OpenFont("Tahoma.ttf", 20);
    if(DEVMODE && *font == NULL) {
        fprintf(stderr, "-------------------------------\n>>> [ ! ] ERROR : [ ! ] <<<\n # at funtion: set_sdlFont \n # Check if parameters are correct:\n #   -> font_type (const char *) : %s\n #   -> font_size (int) : %d\n-------------------------------\n", font_type, font_size);
    }
    return (*font != NULL);
}

/* FREE SURFACE */
bool freeSDL_Surface(SDL_Surface** surface) {

    if (*surface != NULL) {
        SDL_FreeSurface(*surface);
        *surface = NULL;
    }
    return true;
}

/* CLEAN UP EVERTHING */
bool clean_up(SDL_Surface **surface, int *ptr, int qtde) {
    for (int i = 0; i < qtde; i++) {
        if (surface[i] != NULL) {
            freeSDL_Surface(&surface[i]);
            surface[i] = NULL;
        }
    }

    if (ptr != NULL) {
        free(ptr);
        ptr = NULL;
    }

    return true;
}

/* LOAD UP EVERTHING */
bool load_files(SDL_Surface **surface, const char **str, int qtde) {
    for (int i = 0; i < qtde; i++) {
        surface[i] = SDL_LoadBMP(str[i]);
        if (surface[i] == NULL) {
            return false;
        }
    }
    return true;
}