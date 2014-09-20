/* 
* CREATED BY Lucas Vieira Costa Nicolau - USP
* Used amoung with SDL2 
* -- (good tutorial tip : SDL LAZY FOO --there's other, but this was the most 
* used by me on learning)
*
* -- Open Source, Open to learn, Open to distribute. 
* Just don't misrepresent my credits and time spend to make this library. Thanks.
*/

#ifndef EDITOR_MAPA_H
#define	EDITOR_MAPA_H

#include "sdl_basics.h"

bool editor_mapa();

bool empty_mapa();

bool tradeImage(SDL_Surface **surface, const char *str);

SDL_Point toMatrizPosition(SDL_Point mPosition);

bool matrizToImage(SDL_Rect *offset, SDL_Surface *surface, SDL_Surface *screen);

bool load_up(SDL_Window **window, SDL_Surface **screen, SDL_Surface **img);

bool clean_up(SDL_Window **window, SDL_Surface **screen, SDL_Surface **img);

bool save_mapa();

bool save_undo();

bool save_redo();

bool load_undo();

bool load_redo();

bool load_mapa(const char *src);

void limpa_selecao();

void set_right(SDL_Point mPoint, int value);

void set_down(SDL_Point mPoint, int value);

void set_left(SDL_Point mPoint, int value);

void set_up(SDL_Point mPoint, int value);

void set_all(SDL_Point mPoint, int value);

bool external_load_map(SDL_Surface **screen);

//void retorna_valor_anterior(SDL_Point mPositionMatriz);
                    
#endif	/* EDITOR_MAPA_H */

