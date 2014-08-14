#include "function.h"

int *init_click(int *click) {

    click[0] = 0;
    click[1] = -1;
    click[2] = -1;
    click[3] = -1;
    click[4] = 0;
    click[5] = -1;
    click[6] = -1;
    click[7] = -1;
    click[8] = 0;
    click[9] = -1;
    click[10] = -1;
    click[11] = -1;
    click[12] = 0;

    return click;
}

void set_sdlRect(SDL_Rect *offset, int x, int y) {
    (*offset).x = x;
    (*offset).y = y;
}

// BUG
SDL_Surface* set_sdlSurface(SDL_Rect *offset, SDL_Surface* screen, Uint32 key, const char* str) {
    SDL_Surface *img = SDL_LoadBMP(str);
    SDL_SetColorKey(img, SDL_SRCCOLORKEY, key);
    SDL_BlitSurface(img, 0, screen, offset);
    return img;
}

int *function_up(int *vetor, int *click, SDL_Rect *offset, int lado) {
    if ((*offset).y < SCREEN_HEIGHT) {
            (*vetor)++;
            if (lado < 1) {
                click[1] = -1;
                click[0] = -1;
                click[2]++;
                click[3] = -1;
                (*offset).y -= OFFSET_MOVE_Y;
            }
            if (lado > 1) {
                click[0] = -1;
                click[1] = -1;
                click[3]++;
                click[2] = -1;
                (*offset).y -= OFFSET_MOVE_Y;
            }
        }
    return click;
}

void function_down(int *vetor) {
        *vetor = 0;
}

void function_exit(bool *done) {
    if (*done == false) {
        *done = true;
    }
}

int *function_right(int *vetor, int *click, SDL_Rect *offset, int *lado) {
    if ((*offset).x < SCREEN_WIDTH - 3*OFFSET_MOVE_X) {
        *vetor += 3;
        *lado = 0;
        if ((*offset).y < 316) {
            click[0] = -1;
            click[1] = -1;
            click[3] = -1;
            click[2]++;
            (*offset).x += 10;
        }
        if ((*offset).y >= 316) {
            click[3] = -1;
            click[2] = -1;
            click[1] = -1;
            click[0]++;
            (*offset).x += 10;
        }

        if((*offset).y + 3 < PLATAFORMA_Y) {
            (*offset).y += 3;
        }
    } else {
        (*offset).x  = SCREEN_WIDTH - 3*OFFSET_MOVE_X;
        printf("Passou de fase...\n");
    }
    return click;
}

int *function_left(int *vetor, int *click, SDL_Rect *offset, int *lado) {
    if ((*offset).x > 0) {
        *vetor += 4;
        *lado = 2;
        if ((*offset).y < 316) {
            click[0] = -1;
            click[1] = -1;
            click[2] = -1;
            click[3]++;
            (*offset).x -= OFFSET_MOVE_X;
        }
        if ((*offset).y >= 316) {
            click[3] = -1;
            click[2] = -1;
            click[0] = -1;
            click[1]++;
            (*offset).x -= OFFSET_MOVE_X;
        }
        if((*offset).y + 3 < PLATAFORMA_Y) {
            (*offset).y += 3;
        }
    }
    return click;
}

void imprimeVariaveisTeste(SDL_Rect offset, SDL_Rect amigo, SDL_Rect inimigo, int cont) {
    if (DEVMODE) {
        printf("cont = %d\na.x = %d  e a.y = %d\no.x = %d  e o.y = %d\ni.x = %d  e i.y = %d\n", cont, amigo.x, amigo.y, offset.x, offset.y, inimigo.x, inimigo.y);
        printf("==========================================================\n");
    }
}

bool initSDL_Surface(SDL_Surface** pointer, const char *str) {

    *pointer = SDL_LoadBMP(str);
    return (*pointer != NULL) ? true : false;
}

void freeSDL_Surface(SDL_Surface** pointer) {


    if (*pointer != NULL) {
        SDL_FreeSurface(*pointer);
        *pointer = NULL;
    }
}

void delay(float seconds) {
    usleep(seconds * TOMICROSECONDS);
}

void clean_up(SDL_Surface **surface, int *pointer, int qtde) {
    for (int i = 0; i < qtde; i++) {
        if (surface[i] != NULL) {
            freeSDL_Surface(&surface[i]);
            surface[i] = NULL;
        }
    }

    if (pointer != NULL) {
        free(pointer);
        pointer = NULL;
    }
}

bool load_files(SDL_Surface **surface, const char **str, int qtde) {
    for(int i=0; i<qtde; i++) {
        surface[i] = SDL_LoadBMP(str[i]);
        if(surface[i] == NULL) {
            return false;
        }
    }

    return true;
}
