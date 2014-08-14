#include "vnt.h"
#include "sdl_basics.h"

int *init_click(int *click) {
    //int click[13] = {0, -1, -1, -1, 0, -1, -1, -1, 0, -1, -1 ,-1, 0};

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

int *function_up(int *vetor, int *click, SDL_Rect *offset, int lado, bool canJump) {
    if ((*offset).y < SCREEN_HEIGHT) {
        if (canJump) {
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
    }
    return click;
}

bool isAbleToJump(int *cont) {
    if (*cont < MAX_CONT_JUMP) {
        *cont += 1;
        return true;
    } else {
        *cont = MAX_CONT_JUMP;
        return false;
    }
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
    if ((*offset).x < SCREEN_WIDTH - 3 * OFFSET_MOVE_X) {
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
    } else {
        (*offset).x = SCREEN_WIDTH - 3 * OFFSET_MOVE_X;
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
    }
    return click;
}

int updateVector(int *vetor_x, int *vetor_y, int size) {
    for (int i = 0; i < size; i++) {
        if (vetor_x[i] == 0 && vetor_y[i] == 0) {
            return i;
        }
    }
    return -1;
}

void imprimeVariaveisTeste(SDL_Rect offset, SDL_Rect amigo, SDL_Rect inimigo, int cont) {
    if (DEVMODE) {
        printf("cont = %d\na.x = %d  e a.y = %d\no.x = %d  e o.y = %d\ni.x = %d  e i.y = %d\n", cont, amigo.x, amigo.y, offset.x, offset.y, inimigo.x, inimigo.y);
        printf("==========================================================\n");
    }
}
