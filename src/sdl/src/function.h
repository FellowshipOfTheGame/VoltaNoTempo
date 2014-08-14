#ifndef _FUNCTIONS
#define _FUNCTIONS

#define TOMICROSECONDS 100000
#define MAX_CONT_JUMP 3
#define OFFSET_MOVE_Y 30        // movimento do pulo
#define OFFSET_MOVE_X 10        // movimento direita/esquerda
#define PLATAFORMA_Y 316    /// altura da plataforma (onde o player anda)
#define WAIT 0.5            /// FLOAT   -- Tempo de espera
#define SCREEN_WIDTH 600           /// INT     -- Largura da tela
#define SCREEN_HEIGHT 450          /// INT     -- Altura da tela

#define DEVMODE true        /// ATIVA TESTE DE POSICAO (true atico, false inativo)

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <unistd.h>			/// Sleep

/// Seta o sdlRect na com offset.x = x e offset.y = y
void set_sdlRect(SDL_Rect *offset, int x, int y);

/// Inicializa o surface
SDL_Surface* set_sdlSurface(SDL_Rect *offset, SDL_Surface* screen, Uint32 key, const char* str);

/// Inicia *click
int *init_click(int *click);

/// Move para cima
int *function_up(int *vetor, int *click, SDL_Rect *offset, int lado);

// Verifica se está habilitado a pular (ou se já executo o maximo de pulos permitidos)

/// Move para baixo
void function_down(int *vetor);

/// Sai do game
void function_exit(bool *done);

/// Vira para a direita
int *function_right(int *vetor, int *click, SDL_Rect *offset, int *lado);

/// Vira para a esquerda
int *function_left(int *vetor, int *click, SDL_Rect *offset, int *lado);

bool initSDL_Surface(SDL_Surface** pointer, const char *str);

void imprimeVariaveisTeste(SDL_Rect offset, SDL_Rect amigo, SDL_Rect inimigo, int cont);

void freeSDL_Surface(SDL_Surface** pointer);

/// Executa um delay
void delay(float seconds);

/// Limpa tudo
void clean_up(SDL_Surface **surface, int *pointer, int qtde);

/// Load files -- Imagens
bool load_files(SDL_Surface **surface, const char **str, int qtde);
#endif
