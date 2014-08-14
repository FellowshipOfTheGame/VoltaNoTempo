/* CASO ESTEJA DANDO ERROS NA IMAGENS TROQUE O DIRETORIO "src/img/" POR "img/"*/
/*"src/img/" -- compila no code::blocks */
/* "img/" -- compila no NetBeans*/
#include "time2.h"
#include "sdl_basics.h"
#include "vnt.h"
#define NUM_CLONES 3
#define NUM_MOVIMENTOS 10

void shift_para_direita(int *vetor_x, int *vetor_y) {
    int aux = NUM_CLONES * NUM_MOVIMENTOS - 1;
    for (int i = aux; i > 0; i--) {
        vetor_x[i] = vetor_x[i - 1];
        vetor_y[i] = vetor_y[i - 1];
    }
}

int time1() {
    //SDL2
    int *vetX = (int *) calloc(NUM_CLONES * NUM_MOVIMENTOS, sizeof (int));
    int *vetY = (int *) calloc(NUM_CLONES * NUM_MOVIMENTOS, sizeof (int));

    // The window we'll be rendering to
    SDL_Window* window = NULL;

    // The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    } else {
        //Create window
        window = SDL_CreateWindow("Volta no Tempo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
            return -1;
        } else {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            // Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            // Update the surface
            SDL_UpdateWindowSurface(window);

            // Wait 0.1 seconds
            SDL_Delay(100);
        }

    }

    // load an image
    SDL_Surface* bmp = NULL;
    SDL_Surface* linha = NULL;
    SDL_Surface* badbmp = NULL;
    SDL_Surface* tardis = NULL;
    SDL_Surface* goodbmp = NULL;

    SDL_Surface * spikeImg[2]; // Vetor de imagens de espinhos
    spikeImg[0] = NULL;
    spikeImg[1] = NULL;

    SDL_Surface * buttonImg[2]; // Vetor de imagens de botoes
    buttonImg[0] = NULL;
    buttonImg[1] = NULL;
    // SDL_Surface* botao2 = NULL;

    /// Verifica se todas imagens carregadas existem
    if (!set_sdlSurface(&bmp, "img/000.bmp", false) && !set_sdlSurface(&bmp, "src/img/000.bmp", false)) { /// Voce tinha posto 0.bmp (mas nao existe tal imagem) - verificar depois
        fprintf(stderr, "Erro na execucao - 0002\n");
        return -1;
    }
    if (!set_sdlSurface(&linha, "img/linha.bmp", false) && !set_sdlSurface(&linha, "src/img/linha.bmp", false)) {
        fprintf(stderr, "Erro na execucao - 0003\n");
        return -1;
    }
    if (!set_sdlSurface(&badbmp, "img/000.bmp", false) && !set_sdlSurface(&badbmp, "src/img/000.bmp", false)) {
        fprintf(stderr, "Erro na execucao - 0004\n");
        return -1;
    }
    if (!set_sdlSurface(&tardis, "img/tardis.bmp", false) && !set_sdlSurface(&tardis, "src/img/tardis.bmp", false)) {
        fprintf(stderr, "Erro na execucao - 0005\n");
        return -1;
    }
    if (!set_sdlSurface(&goodbmp, "img/00000.bmp", false) && !set_sdlSurface(&goodbmp, "src/img/00000.bmp", false)) {
        fprintf(stderr, "Erro na execucao - 0006\n");
        return -1;
    }
    if (!set_sdlSurface(&spikeImg[0], "img/spikes1.bmp", false) && !set_sdlSurface(&spikeImg[0], "src/img/spikes1.bmp", false)) {
        fprintf(stderr, "Erro na execucao - 0007\n");
        return -1;
    }
    if (!set_sdlSurface(&spikeImg[1], "img/spikes2.bmp", false) && !set_sdlSurface(&spikeImg[1], "src/img/spikes2.bmp", false)) {
        fprintf(stderr, "Erro na execucao - 0008\n");
        return -1;
    }
    if (!set_sdlSurface(&buttonImg[0], "img/botao1.bmp", false) && !set_sdlSurface(&buttonImg[0], "src/img/botao1.bmp", false)) {
        fprintf(stderr, "Erro na execucao - 0009\n");
        return -1;
    }
    if (!set_sdlSurface(&buttonImg[1], "img/botao2.bmp", false) && !set_sdlSurface(&buttonImg[1], "src/img/botao2.bmp", false)) {
        fprintf(stderr, "Erro na execucao - 0010\n");
        return -1;
    }

    /// Se continuou todas imagens devem existir

    SDL_Rect offset;
    set_sdlRect(&offset, 120, PLATAFORMA_Y);

    SDL_Rect grama;
    set_sdlRect(&grama, 0, 350);


    SDL_Rect timespace;
    set_sdlRect(&timespace, 100, 178);

    SDL_Rect inimigo;
    set_sdlRect(&inimigo, 120, PLATAFORMA_Y);

    SDL_Rect amigo;
    set_sdlRect(&amigo, 120, PLATAFORMA_Y);

    SDL_Rect espinhos[2];

    set_sdlRect(&espinhos[0], 400, 138);
    set_sdlRect(&espinhos[1], 416, 98);

    SDL_Rect botao[2];

    set_sdlRect(&botao[0], 30, 330);
    set_sdlRect(&botao[1], 210, 330);

    int q, ger, i, p, espelho, reg, grav, start, m, r, s;
    int lado, startrad, rad, mirror, u, graviole, l, nap;

    int *click = (int *) calloc(13, sizeof (int));

    // Inicia click
    click = init_click(click);

    int cont = 0;

    int vetor[10000];
    vetor[0] = 0;
    start = 0;
    startrad = 0;
    lado = 0;
    reg = 0;
    grav = 0;
    i = 0; //o nÃºmero de i tem que ser par, e metade do valor + 1 serÃ¡ a diferenÃ§a
    p = 0;
    q = 0;
    r = 0;
    s = 0;
    l = 0;
    m = 0;
    ger = 0;
    espelho = 0;
    mirror = 0;
    bool done = false;

    while (!done) {
        if (offset.y >= PLATAFORMA_Y) {
            SDL_Delay(1);
            cont = 0;
        }

        // Set texture based on current keystate 
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (currentKeyStates[ SDL_SCANCODE_LEFT ]) {
            SDL_Delay(WAIT);
            click = function_left(&vetor[i], click, &offset, &lado);
            imprimeVariaveisTeste(offset, amigo, inimigo, cont);
            vetX[0] = offset.x;
            vetY[0] = offset.y;
        } else if (currentKeyStates[ SDL_SCANCODE_RIGHT ]) {
            SDL_Delay(WAIT);
            click = function_right(&vetor[i], click, &offset, &lado);
            imprimeVariaveisTeste(offset, amigo, inimigo, cont);
            vetX[0] = offset.x;
            vetY[0] = offset.y;
        }

        //Update the screen
        SDL_UpdateWindowSurface(window);


        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            p++;
            i++;
            vetor[i] = 0;
            switch (event.type) {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            click = function_up(&vetor[i], click, &offset, lado, isAbleToJump(&cont));
                            imprimeVariaveisTeste(offset, amigo, inimigo, cont);
                            vetX[0] = offset.x;
                            vetY[0] = offset.y;
                            break;

                        case SDLK_DOWN:
                            function_down(&vetor[i]);
                            imprimeVariaveisTeste(offset, amigo, inimigo, cont);
                            vetX[0] = offset.x;
                            vetY[0] = offset.y;
                            break;

                        case SDLK_ESCAPE:
                            function_exit(&done);
                            break;

                        default:
                            break;

                    }
                }
            }

        }
        if (offset.y < PLATAFORMA_Y) {
            if (reg == 15) {
                offset.y += 5;
                reg = 0;
            }
            if (reg < 15) {
                reg++;
            }
        }

        if (vetor[i] >= 20) {
            start++;
        }
        if (start == 1) {
            l = i;
            m = i;
        }
        if (start == 5) {
            inimigo.x = 120;
            inimigo.y = PLATAFORMA_Y;
            q = 0;
        }
        if (start > 0) {
            if (ger == 5) {
                ger = 0;
                q = q + 1;
                if (q < l) {
                    if (vetor[q] == 0) {
                        inimigo.x = inimigo.x;
                    }
                    if (vetor[q] == 4) {
                        espelho = 1;
                        if (inimigo.y < PLATAFORMA_Y) {
                            click[5] = -1;
                            click[4] = -1;
                            click[6] = -1;
                            click[7]++;
                            inimigo.x -= 10;
                        }
                        if (inimigo.y >= PLATAFORMA_Y) {
                            click[5]++;
                            click[4] = -1;
                            click[6] = -1;
                            click[7] = -1;
                            inimigo.x -= 10;
                        }
                    }
                    if (vetor[q] == 3) {
                        espelho = 2;

                        if (inimigo.y < PLATAFORMA_Y) {
                            click[5] = -1;
                            click[4] = -1;
                            click[7] = -1;
                            click[6]++;
                            inimigo.x += 10;
                        }
                        if (inimigo.y >= PLATAFORMA_Y) {
                            click[4]++;
                            click[5] = -1;
                            click[6] = -1;
                            click[7] = -1;
                            inimigo.x += 10;
                        }
                    }
                    if (vetor[q] == 1) {
                        if (espelho == 2) {
                            inimigo.y = inimigo.y - 20;
                            click[4] = -1;
                            click[5] = -1;
                            click[6]++;
                            click[7] = -1;
                        }
                        if (espelho == 1) {
                            inimigo.y -= 20;
                            click[4] = -1;
                            click[5] = -1;
                            click[7]++;
                            click[6] = -1;
                        }
                    }
                }
                if (q > m) {
                    click[4] = -1;
                    click[5] = -1;
                    click[6] = -1;
                    click[7] = -1;
                    inimigo.y = 600;
                    inimigo.x = 1000;
                }
            }
        }
        if (ger < 5) {
            ger++;
        }

        if (vetor[i] == 2) {
            startrad++;

            if (startrad == 1) {
                amigo.x = offset.x;
                amigo.y = offset.y;
            }
        }
        if (startrad > 5) {
            if (startrad == 6) {
                nap = i;
                startrad++;
            }

            if (rad == 5) {
                rad = 0;
                u = l;
                l++;

                if (u < nap) {
                    if (vetor[u] == 4) {
                        mirror = 1;
                        if (amigo.y < PLATAFORMA_Y) {
                            click[9] = -1;
                            click[8] = -1;
                            click[10] = -1;
                            click[11]++;
                            amigo.x -= 10;
                        }

                        if (amigo.y >= PLATAFORMA_Y) {
                            click[9]++;
                            click[8] = -1;
                            click[10] = -1;
                            click[11] = -1;
                            amigo.x -= 10;
                        }
                    }

                    if (vetor[u] == 3) {
                        mirror = 2;

                        if (amigo.y < PLATAFORMA_Y) {
                            click[9] = -1;
                            click[8] = -1;
                            click[11] = -1;
                            click[10]++;
                            amigo.x += 10;
                        }
                        if (amigo.y >= PLATAFORMA_Y) {
                            click[8]++;
                            click[9] = -1;
                            click[10] = -1;
                            click[11] = -1;
                            amigo.x += 10;
                        }
                    }
                    if (vetor[u] == 1) {
                        if (mirror == 2) {
                            amigo.y -= 20;
                            click[8] = -1;
                            click[9] = -1;
                            click[10]++;
                            click[11] = -1;
                        }

                        if (mirror == 1) {
                            amigo.y -= 20;
                            click[8] = -1;
                            click[9] = -1;
                            click[11]++;
                            click[10] = -1;
                        }
                    }

                }
            }
        }
        if (u > nap) {
            click[8] = -1;
            click[9] = -1;
            click[10] = -1;
            click[11] = -1;
            amigo.y = 20;
            amigo.x = 2000;
        }

        if (rad < 5) {
            rad++;
        }

        if (inimigo.y < PLATAFORMA_Y) {
            if (grav == 15) {
                inimigo.y += 10;
                grav = 0;
            }
            if (grav < 15) {
                grav++;
            }
        }

        if (amigo.y < PLATAFORMA_Y && startrad > 5) {
            if (graviole == 15) {
                amigo.y += 10;
                graviole = 0;
            }
            if (graviole < 15) {
                graviole++;
            }
        }

        if (offset.x == 20 && offset.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (inimigo.x == 20 && inimigo.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (amigo.x == 20 && amigo.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (offset.x == 200 && offset.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (inimigo.x == 200 && inimigo.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (amigo.x == 200 && amigo.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (q > 0 && (offset.x == inimigo.x && offset.y == inimigo.y)) {
            free(click);
            return 0;
        }


        if (u > 0 && ((offset.x == amigo.x && offset.y == amigo.y) || (inimigo.x == amigo.x && inimigo.y == amigo.y))) {
            free(click);
            return 0;
        }


        // DRAWING STARTS HERE
        // clear screen
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 255, 255));

        // draw bitmap
        SDL_BlitSurface(linha, 0, screenSurface, &grama);
        SDL_BlitSurface(tardis, 0, screenSurface, &timespace);
        SDL_SetColorKey(tardis, SDL_TRUE, SDL_MapRGB(tardis->format, 0, 0xFF, 0xFF));
        if (click[12] % 4 == 0) {
            if (offset.x > 375) {
                if (offset.y > 70) {
                    free(click);
                    return 0;
                }
            }

            SDL_Surface* spike1 = SDL_LoadBMP("img/spikes1.bmp");
            SDL_SetColorKey(spike1, SDL_TRUE, SDL_MapRGB(spike1->format, 0, 0xFF, 0xFF));
            SDL_BlitSurface(spike1, 0, screenSurface, &espinhos[0]);

        }

        if (click[12] % 4 == 1) {
            if (offset.x > 375) {
                if (offset.y > 70) {
                    free(click);
                    return 0;
                }
            }
            SDL_Surface* spike1 = SDL_LoadBMP("img/spikes1.bmp");
            SDL_SetColorKey(spike1, SDL_TRUE, SDL_MapRGB(spike1->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(spike1, 0, screenSurface, &espinhos[0]);
        }
        SDL_Surface* spike2 = SDL_LoadBMP("img/spikes2.bmp");
        SDL_SetColorKey(spike2, SDL_TRUE, SDL_MapRGB(spike2->format, 0xFF, 0xFF, 0xFF));
        SDL_BlitSurface(spike2, 0, screenSurface, &espinhos[1]);

        SDL_Surface* botao1 = SDL_LoadBMP("img/botao1.bmp");
        SDL_SetColorKey(botao1, SDL_TRUE, SDL_MapRGB(botao1->format, 0xFF, 0xFF, 0xFF));
        SDL_BlitSurface(botao1, 0, screenSurface, &botao[0]);

        SDL_Surface* botao2 = SDL_LoadBMP("img/botao2.bmp");
        SDL_SetColorKey(botao2, SDL_TRUE, SDL_MapRGB(botao2->format, 0xFF, 0xFF, 0xFF));
        SDL_BlitSurface(botao2, 0, screenSurface, &botao[1]);


        if (click[0] % 4 == 0) {
            SDL_Surface* bmp = SDL_LoadBMP("img/1.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }

        if (click[0] % 4 == 1) {
            SDL_Surface* bmp = SDL_LoadBMP("img/2.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }

        if (click[0] % 4 == 2) {
            SDL_Surface* bmp = SDL_LoadBMP("img/3.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (click[0] % 4 == 3) {
            SDL_Surface* bmp = SDL_LoadBMP("img/4.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }

        if (click[1] % 4 == 0) {
            SDL_Surface* bmp = SDL_LoadBMP("img/11.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (click[1] % 4 == 1) {
            SDL_Surface* bmp = SDL_LoadBMP("img/22.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (click[1] % 4 == 2) {
            SDL_Surface* bmp = SDL_LoadBMP("img/33.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (click[1] % 4 == 3) {
            SDL_Surface* bmp = SDL_LoadBMP("img/44.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (click[2] % 2 == 0) {
            SDL_Surface* bmp = SDL_LoadBMP("img/010.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (click[2] % 2 == 1) {
            SDL_Surface* bmp = SDL_LoadBMP("img/020.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (click[3] % 2 == 0) {
            SDL_Surface* bmp = SDL_LoadBMP("img/110.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (click[3] % 2 == 1) {
            SDL_Surface* bmp = SDL_LoadBMP("img/220.bmp");
            SDL_SetColorKey(bmp, SDL_TRUE, SDL_MapRGB(bmp->format, 0xFF, 0xFF, 0xFF));
            SDL_BlitSurface(bmp, 0, screenSurface, &offset);
        }
        if (q > 0) {
            if (click[4] % 4 == 0) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/000.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }

            if (click[4] % 4 == 1) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/111.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }

            if (click[4] % 4 == 2) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/222.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[4] % 4 == 3) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/333.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[5] % 4 == 0) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/0000.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[5] % 4 == 1) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/1111.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[5] % 4 == 2) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/2222.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[5] % 4 == 3) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/3333.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[6] % 2 == 0) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/1010.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[6] % 2 == 1) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/2020.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[7] % 2 == 0) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/1110.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
            if (click[7] % 2 == 1) {
                SDL_Surface* badbmp = SDL_LoadBMP("img/2220.bmp");
                SDL_SetColorKey(badbmp, SDL_TRUE, SDL_MapRGB(badbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(badbmp, 0, screenSurface, &inimigo);
            }
        }

        if (u > 0) {
            if (click[8] % 4 == 0) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/00000.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[8] % 4 == 1) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/11111.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[8] % 4 == 2) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/22222.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[8] % 4 == 3) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/33333.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[9] % 4 == 0) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/000000.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[9] % 4 == 1) {
                SDL_Surface *goodbmp = SDL_LoadBMP("img/111111.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[9] % 4 == 2) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/222222.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[9] % 4 == 3) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/333333.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[10] % 2 == 0) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/01010.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[10] % 2 == 1) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/02020.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[11] % 2 == 0) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/01110.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
            if (click[11] % 2 == 1) {
                SDL_Surface* goodbmp = SDL_LoadBMP("img/02220.bmp");
                SDL_SetColorKey(goodbmp, SDL_TRUE, SDL_MapRGB(goodbmp->format, 0xFF, 0xFF, 0xFF));
                SDL_BlitSurface(goodbmp, 0, screenSurface, &amigo);
            }
        }
        //        SDL_Flip(screenSurface);
        SDL_UpdateWindowSurface(window);

        shift_para_direita(vetX, vetY);
        //        int aux = updateVector(vetX, vetY, NUM_CLONES * NUM_MOVIMENTOS);
        //        if (aux != -1) {
        //            aux %= 30;
        //            int clone = aux / 10;
        //            int movimento = aux % 10;
        //            while(clone > 0) {
        //                for(int i = 1; i< movimento)
        //                vetX[clone * movimento] = vetX[(clone-1) * movimento];
        //                vetY[clone * movimento] = vetY[(clone-1) * movimento];
        //            }

    }
    //    int j;
    //    for (j = 0; j < i; j++) {
    //        printf("\n%d", vetor[j]);
    //    }
    for (int i = 0; i < NUM_CLONES * NUM_MOVIMENTOS; i++) {
        printf("\nx:%d y:%d", vetX[i], vetY[i]);
    }

    freeSDL_Surface(&bmp);
    freeSDL_Surface(&tardis);
    freeSDL_Surface(&badbmp);
    freeSDL_Surface(&goodbmp);
    freeSDL_Surface(&spikeImg[0]);
    freeSDL_Surface(&spikeImg[1]);
    freeSDL_Surface(&buttonImg[0]);
    freeSDL_Surface(&buttonImg[1]);
    bmp = NULL;
    tardis = NULL;
    badbmp = NULL;
    goodbmp = NULL;
    spikeImg[0] = NULL;
    spikeImg[1] = NULL;
    buttonImg[0] = NULL;
    buttonImg[1] = NULL;


    free(click);
    free(vetX);
    free(vetY);

    // SDL2
    //Destroy window
    SDL_DestroyWindow(window);

    //    delete world;

    //Quit SDL subsystems
    SDL_Quit();

    return 1;
}