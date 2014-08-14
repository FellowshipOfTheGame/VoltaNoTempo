#ifndef VNT_H
#define	VNT_H

#include "sdl_basics.h"

#define MAX_CONT_JUMP 2          // Pulo seguidos       
#define OFFSET_MOVE_Y 30        // movimento do pulo
#define OFFSET_MOVE_X 10        // movimento direita/esquerda
#define PLATAFORMA_Y 316    /// altura da plataforma (onde o player anda)
#define WAIT 100            /// FLOAT   -- Tempo de espera
#define SCREEN_WIDTH 600           /// INT     -- Largura da tela
#define SCREEN_HEIGHT 450          /// INT     -- Altura da tela
#define PTM_RATIO 32.0


int *init_click(int *click);

/// Move para cima
int *function_up(int *vetor, int *click, SDL_Rect *offset, int lado, bool canJump);

// Verifica se está habilitado a pular (ou se já executo o maximo de pulos permitidos)
bool isAbleToJump(int *cont);

/// Move para baixo
void function_down(int *vetor);

/// Sai do game
void function_exit(bool *done);

/// Vira para a direita
int *function_right(int *vetor, int *click, SDL_Rect *offset, int *lado);

/// Vira para a esquerda
int *function_left(int *vetor, int *click, SDL_Rect *offset, int *lado);

int updateVector(int *vetor_x, int *vetor_y, int size);

void imprimeVariaveisTeste(SDL_Rect offset, SDL_Rect amigo, SDL_Rect inimigo, int cont);

#endif	/* VNT_H */

