/* 
* CREATED BY Lucas Vieira Costa Nicolau - USP
* Used amoung with SDL2 
* -- (good tutorial tip : SDL LAZY FOO --there's other, but this was the most 
* used by me on learning)
*
* -- Open Source, Open to learn, Open to distribute. 
* Just don't misrepresent my credits and time spend to make this library. Thanks.
*/
#include "editor_mapa.h"


/* --------      IMPORTANT     -----------        *
 * - IMAGE DIMENSION (SQUARE_SIZE X SQUARE_SIZE)  *
 * - DO NOT REMOVE ANY DEFINE -- JUST EDIT VALUES */

// SIZE OF MATRIZ
#define COL 30
#define LIN 25

// DIMENSION OF IMG (ONE SIDE -- NOTE: IMAGE MUST HAVE A SQUARE DIMENSION)
#define SQUARE_SIZE 20          // TAMANHO DO LADO DO QUADRADO


#define FILE_SOURCE "file/mapa.bin"
#define UNDO_SOURCE "file/undo.bin"
#define REDO_SOURCE "file/redo.bin"

// EMPTY AND SELECT VALUES -- 1 - 9  is the images used by the editor
#define SELECT -1
#define EMPTY -2

// IMAGES SOURCES
#define IMG_EMPTY "img/tiles/quad_pont.png"
#define IMG_SELECT "img/tiles/sel_quad_pont.png"
#define IMG_0 "img/tiles/img_0.png"
#define IMG_1 "img/tiles/img_1.png"
#define IMG_2 "img/tiles/img_2.png"
#define IMG_3 "img/tiles/img_3.png"
#define IMG_4 "img/tiles/img_4.png"
#define IMG_5 "img/tiles/img_5.png"
#define IMG_6 "img/tiles/img_6.png"
#define IMG_7 "img/tiles/img_7.png"
#define IMG_8 "img/tiles/img_8.png"
#define IMG_9 "img/tiles/img_9.png"

#define IMG_10 "img/tiles/img_10.png"
#define IMG_11 "img/tiles/img_11.png"
#define IMG_12 "img/tiles/img_12.png"
#define IMG_13 "img/tiles/img_13.png"
#define IMG_14 "img/tiles/img_14.png"
#define IMG_15 "img/tiles/img_15.png"
#define IMG_16 "img/tiles/img_16.png"
#define IMG_17 "img/tiles/img_17.png"
#define IMG_18 "img/tiles/img_18.png"
#define IMG_19 "img/tiles/img_19.png"

#define IMG_20 "img/tiles/img_20.png"
#define IMG_21 "img/tiles/img_21.png"
#define IMG_22 "img/tiles/img_22.png"
#define IMG_23 "img/tiles/img_23.png"
#define IMG_24 "img/tiles/img_24.png"
#define IMG_25 "img/tiles/img_25.png"
#define IMG_26 "img/tiles/img_26.png"
#define IMG_27 "img/tiles/img_27.png"
#define IMG_28 "img/tiles/img_28.png"
#define IMG_29 "img/tiles/img_29.png"

 #define MAX_ROLL 3
// -- GLOBAL VARIABLES --
int mapa[COL][LIN]; // Draw map
SDL_Point mem; // Save mouse point
int mem_value; // Save value to restore

// -- MAIN OF FUNCTION -- 

bool editor_mapa() {
    int img_roll = 0;
    bool quit = false;
    bool empty = true;
    bool redo = false;
    bool undo = true;


    // The window we'll be rendering to
    SDL_Window* window = NULL;

    // The surface contained by the window
    SDL_Surface* screen = NULL;

    // Load images surfaces
    SDL_Surface* img = NULL;
    if (!set_sdlSurface(&img, IMG_EMPTY, false)) {
        fprintf(stderr, "Erro na execucao - %s\n", IMG_EMPTY);
        return false;
    }

    SDL_Rect offset;

    if (!load_up(&window, &screen, &img)) {
        fprintf(stderr, "Erro na load\n");
        if (save_mapa()) {
            printf("Erro na load\n");
        }
        return false;
    }

    //Get window surface
    screen = SDL_GetWindowSurface(window);

    // Fill the surface white
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait 0.1 seconds
    SDL_Delay(100);

    //Mouse position
    SDL_Point mPosition;

    // Mouse position to matriz
    SDL_Point mPositionMatriz;

    // Initialize event handler
    SDL_Event event;

    while (!quit) {
        if(undo) {
            save_undo();
            undo = false;
        }
        if (empty) {
            save_undo();
            if (!empty_mapa()) {
                fprintf(stderr, "ERRO\n");
                return false;
            }
            save_redo();
            empty = false;
        }


        // clear screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

        if (!matrizToImage(&offset, img, screen)) {
            fprintf(stderr, "Error matriz to image\n");
            return false;
        }

        //Update the screen
        SDL_UpdateWindowSurface(window);


        //Handle events on queue 
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                    
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym) {

                        case SDLK_LALT:
                            if(img_roll != 0) {
                                img_roll--; 
                            } else {
                                img_roll = MAX_ROLL - 1;
                            }
                            printf("%d\n", img_roll);
                            break;

                        case SDLK_RALT:
                            if(img_roll != MAX_ROLL - 1) {
                                img_roll++; 
                            } else {
                                img_roll = 0;
                            }
                            printf("%d\n", img_roll);
                            break;

                            // Exit
                        case SDLK_ESCAPE:
                            quit = true;
                            break;

                            // Reset mapa
                        case SDLK_INSERT:
                            empty = true;
                            break;

                        case SDLK_DELETE:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = EMPTY;
                            redo = true;
                            break;

                        case SDLK_0:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 0 + img_roll * 10;
                            redo = true;
                            break;
                        case SDLK_1:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 1 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_2:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 2 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_3:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 3 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_4:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 4 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_5:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 5 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_6:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 6 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_7:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 7 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_8:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 8 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_9:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 9 + img_roll * 10;
                            redo = true;
                            break;

                        case SDLK_UP:
                            if (mapa[mPositionMatriz.x][mPositionMatriz.y] == SELECT) {
                                mapa[mPositionMatriz.x][mPositionMatriz.y] = mem_value;
                            }
                            if (mPositionMatriz.y != 0) {
                                mPositionMatriz.y--;
                            } else {
                                mPositionMatriz.y = LIN-1;
                                if(mPositionMatriz.x != 0) {
                                    mPositionMatriz.x--;
                                } else {
                                    mPositionMatriz.x = COL - 1;
                                }
                            }

                            mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = SELECT;

                            break;

                        case SDLK_DOWN:
                            if (mapa[mPositionMatriz.x][mPositionMatriz.y] == SELECT) {
                                mapa[mPositionMatriz.x][mPositionMatriz.y] = mem_value;
                            }
                            if (mPositionMatriz.y != LIN - 1) {
                                mPositionMatriz.y++;
                            } else {
                                mPositionMatriz.y = 0;
                                if(mPositionMatriz.x != COL - 1) {
                                    mPositionMatriz.x++;
                                } else {
                                    mPositionMatriz.x = 0;
                                }
                            }

                            mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = SELECT;
                            break;
                        case SDLK_LEFT:
                            if (mapa[mPositionMatriz.x][mPositionMatriz.y] == SELECT) {
                                mapa[mPositionMatriz.x][mPositionMatriz.y] = mem_value;
                            }
                            if (mPositionMatriz.x != 0) {
                                mPositionMatriz.x--;
                            } else {
                                mPositionMatriz.x = COL-1;
                                if(mPositionMatriz.y != 0) {
                                    mPositionMatriz.y--;
                                } else {
                                    mPositionMatriz.y = LIN-1;
                                }
                            }

                            mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = SELECT;
                            break;

                        case SDLK_RIGHT:
                            if (mapa[mPositionMatriz.x][mPositionMatriz.y] == SELECT) {
                                mapa[mPositionMatriz.x][mPositionMatriz.y] = mem_value;
                            }
                            if (mPositionMatriz.x != COL - 1) {
                                mPositionMatriz.x++;
                            } else {
                                mPositionMatriz.x = 0;
                                if(mPositionMatriz.y != LIN - 1) {
                                    mPositionMatriz.y++;
                                } else {
                                    mPositionMatriz.y = 0;
                                }
                            }

                            mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = SELECT;
                            break;

                            // special fill line with select img
                        case SDLK_d:
                            save_undo();
                            set_down(mPositionMatriz, mem_value);
                            save_redo();
                            break;
                        case SDLK_u:
                            save_undo();
                            set_up(mPositionMatriz, mem_value);
                            save_redo();
                            break;

                            // special fill line with select img
                        case SDLK_f:
                            save_undo();
                            set_right(mPositionMatriz, mem_value);
                            save_redo();
                            break;

                        case SDLK_b:
                            save_undo();
                            set_left(mPositionMatriz, mem_value);
                            save_redo();
                            break;    

                            // Load file
                        case SDLK_l:
                            if (load_mapa(FILE_SOURCE)) {
                                printf("Load Image");
                                save_undo();
                            }
                            break;
                            // Save file
                        case SDLK_s:
			    limpa_selecao();	
                            if (save_mapa()) {
                                printf("Save Image");
                            }
                            break;

                            // Undo 
                        case SDLK_z:
                            if (load_undo()) {
                                printf("Load Image");
                            }
                            break;

                            // Redo 
                        case SDLK_y:
                            if (load_redo()) {
                                printf("Load Image");
                            }
                            break;

                        case SDLK_a:
                            save_undo();
                            set_all(mPositionMatriz, mem_value);
                            save_redo();
                            break;


                    }
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:

                    limpa_selecao();

                    mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                    mPosition.x = event.motion.x;
                    mPosition.y = event.motion.y;

                    mPositionMatriz = toMatrizPosition(mPosition);

                    printf("%d %d\n", mPositionMatriz.x, mPositionMatriz.y);
                    break;

                default:
                    break;
            }
        }
        if (redo) {
            save_redo();
            redo = false;
            undo = true;
        }
    }

    if (save_mapa()) {
        printf("Load Image");
    }

    return clean_up(&window, &screen, &img);
}

// Load everthing

bool load_up(SDL_Window **window, SDL_Surface **screen, SDL_Surface **img) {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Create window
    *window = SDL_CreateWindow("Editor de Mapas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, COL*SQUARE_SIZE, LIN*SQUARE_SIZE, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());

        return false;
    }

    return true;
}

// Clean everthing

bool clean_up(SDL_Window **window, SDL_Surface **screen, SDL_Surface **img) {

    // Free surfaces
    freeSDL_Surface(img);
    freeSDL_Surface(screen);

    //Destroy window
    SDL_DestroyWindow(*window);

    //Quit SDL subsystems
    SDL_Quit();

    return true;
}

// Clean selection point

void limpa_selecao() {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            if (mapa[i][j] == SELECT) {
                mapa[i][j] = EMPTY;
            }
        }
    }
}

// Set mouse on click point

SDL_Point toMatrizPosition(SDL_Point mPosition) {
    mPosition.x /= SQUARE_SIZE;
    mPosition.y /= SQUARE_SIZE;

    mapa[mem.x][mem.y] = mem_value;
    mem_value = mapa[mPosition.x][mPosition.y];
    mem = mPosition;
    mapa[mPosition.x][mPosition.y] = SELECT;
    return mPosition;
}

// Change image

bool tradeImage(SDL_Surface **surface, const char *str) {
    if (!set_sdlSurface(surface, str, false)) {
        fprintf(stderr, "Erro na execucao - %s\n", IMG_EMPTY);
        return false;
    }
    return true;
}

// Set image for every value of mapa[COL][LIN]

bool matrizToImage(SDL_Rect *offset, SDL_Surface *surface, SDL_Surface *screen) {
    bool draw = false;

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {

            if (mapa[i][j] == EMPTY) {

                if (!tradeImage(&surface, IMG_EMPTY)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == SELECT) {

                if (!tradeImage(&surface, IMG_SELECT)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 0) {
                if (!tradeImage(&surface, IMG_0)) {
                    return false;

                }
                draw = true;
            } else if (mapa[i][j] == 1) {
                if (!tradeImage(&surface, IMG_1)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 2) {
                if (!tradeImage(&surface, IMG_2)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 3) {
                if (!tradeImage(&surface, IMG_3)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 4) {
                if (!tradeImage(&surface, IMG_4)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 5) {
                if (!tradeImage(&surface, IMG_5)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 6) {
                if (!tradeImage(&surface, IMG_6)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 7) {
                if (!tradeImage(&surface, IMG_7)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 8) {
                if (!tradeImage(&surface, IMG_8)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 9) {
                if (!tradeImage(&surface, IMG_9)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 10) {
                if (!tradeImage(&surface, IMG_10)) {
                    return false;
                }
                draw = true;
 
            } else if (mapa[i][j] == 11) {
                if (!tradeImage(&surface, IMG_11)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 12) {
                if (!tradeImage(&surface, IMG_12)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 13) {
                if (!tradeImage(&surface, IMG_13)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 14) {
                if (!tradeImage(&surface, IMG_14)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 15) {
                if (!tradeImage(&surface, IMG_15)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 16) {
                if (!tradeImage(&surface, IMG_16)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 17) {
                if (!tradeImage(&surface, IMG_17)) {
                    return false;
                }
                draw = true;

            }  else if (mapa[i][j] == 18) {
                if (!tradeImage(&surface, IMG_18)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 19) {
                if (!tradeImage(&surface, IMG_19)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 20) {
                if (!tradeImage(&surface, IMG_20)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 21) {
                if (!tradeImage(&surface, IMG_21)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 22) {
                if (!tradeImage(&surface, IMG_22)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 23) {
                if (!tradeImage(&surface, IMG_23)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 24) {
                if (!tradeImage(&surface, IMG_24)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 25) {
                if (!tradeImage(&surface, IMG_25)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 26) {
                if (!tradeImage(&surface, IMG_26)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 27) {
                if (!tradeImage(&surface, IMG_27)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 28) {
                if (!tradeImage(&surface, IMG_28)) {
                    return false;
                }
                draw = true;

            } else if (mapa[i][j] == 29) {
                if (!tradeImage(&surface, IMG_29)) {
                    return false;
                }
                draw = true;

            } 
            if (draw) {
                set_sdlRect(offset, i * SQUARE_SIZE, j * SQUARE_SIZE);
                SDL_BlitSurface(surface, 0, screen, offset);
                draw = false;
            }
        }
    }
    return true;
}

// -- SPECIAL FEATURES --

// Repeat selected image to every point right the selection

void set_right(SDL_Point mPoint, int value) {
    for (int i = mPoint.x; i < COL; i++) {
        mapa[i][mPoint.y] = value;
    }
}

// Repeat selected image to every point down the selection

void set_down(SDL_Point mPoint, int value) {
    for (int i = mPoint.y; i < LIN; i++) {
        mapa[mPoint.x][i] = value;
    }
}

void set_left(SDL_Point mPoint, int value) {
    for (int i = mPoint.x; i >=0; i--) {
        mapa[i][mPoint.y] = value;
    }
}

void set_up(SDL_Point mPoint, int value) {
    for (int i = mPoint.y; i >= 0; i--) {
        mapa[mPoint.x][i] = value;
    }
}

void set_all(SDL_Point mPoint, int value) {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            mapa[i][j] = value;
        }
    }
}
// Reset mapa[COL][LIN] with EMPTY

bool empty_mapa() {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            mapa[i][j] = EMPTY;
        }
    }
    return true;
}

// Fill mapa[COL][[LIN] with select image

bool fill_mapa() {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            mapa[i][j] = mem_value;
        }
    }
    return true;
}


// -- SAVE --

bool save_mapa() {
    FILE *file = fopen(FILE_SOURCE, "wb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- save\n");
        return false;
    }

    limpa_selecao();

    mapa[mem.x][mem.y] = mem_value;

    fwrite(mapa, COL * LIN * sizeof (int), 1, file);

    fclose(file);
    return true;
}

bool save_undo() {
    FILE *file = fopen(UNDO_SOURCE, "wb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- save\n");
        return false;
    }

    limpa_selecao();

    fwrite(mapa, COL * LIN * sizeof (int), 1, file);

    fclose(file);

    return true;
}

bool save_redo() {
    FILE *file = fopen(REDO_SOURCE, "wb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- save\n");
        return false;
    }

    limpa_selecao();

    fwrite(mapa, COL * LIN * sizeof (int), 1, file);

    fclose(file);
    return true;
}

// -- LOAD --
bool load_mapa(const char *src) {
    FILE *file = fopen(src, "rb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- load\n");
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < COL * LIN) {
        fprintf(stderr, "Erro - arquivo corrompido!\n");
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(mapa, COL * LIN * sizeof (int), 1, file);

    fclose(file);

    return true;
}

bool load_undo() {
    FILE *file = fopen(UNDO_SOURCE, "rb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- load\n");
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < COL * LIN) {
        fprintf(stderr, "Erro - arquivo corrompido!\n");
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(mapa, COL * LIN * sizeof (int), 1, file);

    fclose(file);

    return true;
}

bool load_redo() {
    FILE *file = fopen(REDO_SOURCE, "rb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- load\n");
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < COL * LIN) {
        fprintf(stderr, "Erro - arquivo corrompido!\n");
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(mapa, COL * LIN * sizeof (int), 1, file);

    fclose(file);
    return true;
}

bool external_load_map(SDL_Surface **screen) {

    // Load images surfaces
    SDL_Surface* img = NULL;

    if (!set_sdlSurface(&img, IMG_EMPTY, false)) {
        fprintf(stderr, "Erro na execucao - %s\n", IMG_EMPTY);
        return false;
    }
    
    // Load map created
    load_mapa(FILE_SOURCE);
    
    SDL_Rect offset;

    // clear screen
    SDL_FillRect(*screen, NULL, SDL_MapRGB((*screen)->format, 0xFF, 0xFF, 0xFF));

    // Seta image from matriz loaded
    if (!matrizToImage(&offset, img, *screen)) {
       fprintf(stderr, "Error matriz to image\n");
       return false;
    }
	
    freeSDL_Surface(&img);
    
    return true;
}
