/* 
* CREATED BY Lucas Vieira Costa Nicolau - USP
* Used amoung with SDL2 
* -- (good tutorial tip : SDL LAZY FOO --there's other, but this was the most 
* used by me on learning)
*
* -- Open Source, Open to learn, Open to distribute. 
* Just don't misrepresent my credits and time spend to make this library. Thanks.

#include "editor_mapa.h"*/
#include <SDL2/SDL.h>

int main(int argc, char *argv[])
{
    /*
    int num = 0;
    if (!editor_mapa()) {
        fprintf(stderr, "Error on execution\n");
        num = 1;
    }
    return num;*/
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return -1;
    
    printf("Editor");
    
    return 0;
}

