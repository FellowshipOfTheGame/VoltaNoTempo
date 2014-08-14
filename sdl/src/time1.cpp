#include "time2.h"
#include "function.h"

int time1() {
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    SDL_Surface* screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (screen == NULL) {
        fprintf(stderr, "Erro na execucao - screen not created successfully\n");
        return -1;
    }

    SDL_Surface* original = NULL;
    SDL_Surface* linha = NULL;
    SDL_Surface* copia1 = NULL;
    SDL_Surface* tardis = NULL;
    SDL_Surface* copia2 = NULL;

    SDL_Surface * spikeImg[2]; // Vetor de imagens de espinhos
    spikeImg[0] = NULL;
    spikeImg[1] = NULL;

    SDL_Surface * buttonImg[2]; // Vetor de imagens de botoes
    buttonImg[0] = NULL;
    buttonImg[1] = NULL;
    // SDL_Surface* botao2 = NULL;

    /// Verifica se todas imagens carregadas existem
    if (!initSDL_Surface(&original, "img/1.bmp") && !initSDL_Surface(&original, "src/img/000.bmp")) { /// Voce tinha posto 0.bmp (mas nao existe tal imagem) - verificar depois
        fprintf(stderr, "Erro na execucao - 0002\n");
        return -1;
    }
    if (!initSDL_Surface(&linha, "img/linha.bmp") && !initSDL_Surface(&linha, "src/img/linha.bmp")) {
        fprintf(stderr, "Erro na execucao - 0003\n");
        return -1;
    }
    if (!initSDL_Surface(&copia1, "img/1.bmp") && !initSDL_Surface(&copia1, "src/img/000.bmp")) {
        fprintf(stderr, "Erro na execucao - 0004\n");
        return -1;
    }
    if (!initSDL_Surface(&tardis, "img/tardis.bmp") && !initSDL_Surface(&tardis, "src/img/tardis.bmp")) {
        fprintf(stderr, "Erro na execucao - 0005\n");
        return -1;
    }
    if (!initSDL_Surface(&copia2, "img/1.bmp") && !initSDL_Surface(&copia2, "src/img/00000.bmp")) {
        fprintf(stderr, "Erro na execucao - 0006\n");
        return -1;
    }
    if (!initSDL_Surface(&spikeImg[0], "img/spikes1.bmp") && !initSDL_Surface(&spikeImg[0], "src/img/spikes1.bmp")) {
        fprintf(stderr, "Erro na execucao - 0007\n");
        return -1;
    }
    if (!initSDL_Surface(&spikeImg[1], "img/spikes2.bmp") && !initSDL_Surface(&spikeImg[1], "src/img/spikes2.bmp")) {
        fprintf(stderr, "Erro na execucao - 0008\n");
        return -1;
    }
    if (!initSDL_Surface(&buttonImg[0], "img/botao1.bmp") && !initSDL_Surface(&buttonImg[0], "src/img/botao1.bmp")) {
        fprintf(stderr, "Erro na execucao - 0009\n");
        return -1;
    }
    if (!initSDL_Surface(&buttonImg[1], "img/botao2.bmp") && !initSDL_Surface(&buttonImg[1], "src/img/botao2.bmp")) {
        fprintf(stderr, "Erro na execucao - 0010\n");
        return -1;
    }

    /// Se continuou todas imagens devem existir

//    b2Vec2 gravity(0, -9.8); //normal earth gravity, 9.8 m/s/s straight down!
//    bool doSleep = true;
//    b2World* myWorld = new b2World(gravity, doSleep);


    SDL_Rect pato1;
    set_sdlRect(&pato1, 120, PLATAFORMA_Y);

    SDL_Rect grama;
    set_sdlRect(&grama, 0, 350);


    SDL_Rect timespace;
    set_sdlRect(&timespace, 100, 178);

    SDL_Rect pato2;
    set_sdlRect(&pato2, 120, PLATAFORMA_Y);

    SDL_Rect pato3;
    set_sdlRect(&pato3, 120, PLATAFORMA_Y);

    SDL_Rect espinhos[2];

    set_sdlRect(&espinhos[0], 400, 138);
    set_sdlRect(&espinhos[1], 416, 98);

    SDL_Rect botao[2];

    set_sdlRect(&botao[0], 30, 330);

    set_sdlRect(&botao[1], 210, 330);

    int q, ger, i, p, espelho, reg, grav, start, m, r, s;
    int lado, startrad, rad, mirror, u, graviole, l, nap;

    int *click = (int *) calloc(13, sizeof (int));

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
        //Get the keystates
        Uint8 *keystates = SDL_GetKeyState(NULL);
        if (pato1.y >= PLATAFORMA_Y) {
            delay(0.01);

            cont = 0;
        }


        if (keystates[ SDLK_LEFT ]) { //If left is pressed
            delay(WAIT);
            click = function_left(&vetor[i], click, &pato1, &lado);
            imprimeVariaveisTeste(pato1, pato2, pato3, cont);
        }
        if (keystates[ SDLK_RIGHT ]) { //If right is pressed
            delay(WAIT);
            click = function_right(&vetor[i], click, &pato1, &lado);
            imprimeVariaveisTeste(pato1, pato2, pato3, cont);
        }

        //Update the screen
        if (SDL_Flip(screen) == -1) {
            return 1;
        }

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
                            click = function_up(&vetor[i], click, &pato1, lado);
                            imprimeVariaveisTeste(pato1, pato2, pato3, cont);
                            break;

                        case SDLK_DOWN:
                            function_down(&vetor[i]);
                            imprimeVariaveisTeste(pato1, pato2, pato3, cont);
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
        if (pato1.y < PLATAFORMA_Y) {
            if (reg == 15) {
                pato1.y += 10;
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
            pato2.x = 120;
            pato2.y = PLATAFORMA_Y;
            q = 0;
        }
        if (start > 0) {
            if (ger == 5) {
                ger = 0;
                q = q + 1;
                if (q < l) {
                    if (vetor[q] == 0) {
                        pato2.x = pato2.x;
                    }
                    if (vetor[q] == 4) {
                        espelho = 1;
                        if (pato2.y < PLATAFORMA_Y) {
                            click[5] = -1;
                            click[4] = -1;
                            click[6] = -1;
                            click[7]++;
                            pato2.x -= 10;
                        }
                        if (pato2.y >= PLATAFORMA_Y) {
                            click[5]++;
                            click[4] = -1;
                            click[6] = -1;
                            click[7] = -1;
                            pato2.x -= 10;
                        }
                    }
                    if (vetor[q] == 3) {
                        espelho = 2;

                        if (pato2.y < PLATAFORMA_Y) {
                            click[5] = -1;
                            click[4] = -1;
                            click[7] = -1;
                            click[6]++;
                            pato2.x += 10;
                        }
                        if (pato2.y >= PLATAFORMA_Y) {
                            click[4]++;
                            click[5] = -1;
                            click[6] = -1;
                            click[7] = -1;
                            pato2.x += 10;
                        }
                    }
                    if (vetor[q] == 1) {
                        if (espelho == 2) {
                            pato2.y = pato2.y - 20;
                            click[4] = -1;
                            click[5] = -1;
                            click[6]++;
                            click[7] = -1;
                        }
                        if (espelho == 1) {
                            pato2.y -= 20;
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
                    pato2.y = 600;
                    pato2.x = 1000;
                }
            }
        }
        if (ger < 5) {
            ger++;
        }

        if (vetor[i] == 2) {
            startrad++;

            if (startrad == 1) {
                pato3.x = pato1.x;
                pato3.y = pato1.y;
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
                        if (pato3.y < PLATAFORMA_Y) {
                            click[9] = -1;
                            click[8] = -1;
                            click[10] = -1;
                            click[11]++;
                            pato3.x -= 10;
                        }

                        if (pato3.y >= PLATAFORMA_Y) {
                            click[9]++;
                            click[8] = -1;
                            click[10] = -1;
                            click[11] = -1;
                            pato3.x -= 10;
                        }
                    }

                    if (vetor[u] == 3) {
                        mirror = 2;

                        if (pato3.y < PLATAFORMA_Y) {
                            click[9] = -1;
                            click[8] = -1;
                            click[11] = -1;
                            click[10]++;
                            pato3.x += 10;
                        }
                        if (pato3.y >= PLATAFORMA_Y) {
                            click[8]++;
                            click[9] = -1;
                            click[10] = -1;
                            click[11] = -1;
                            pato3.x += 10;
                        }
                    }
                    if (vetor[u] == 1) {
                        if (mirror == 2) {
                            pato3.y -= 20;
                            click[8] = -1;
                            click[9] = -1;
                            click[10]++;
                            click[11] = -1;
                        }

                        if (mirror == 1) {
                            pato3.y -= 20;
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
            pato3.y = 20;
            pato3.x = 2000;
        }

        if (rad < 5) {
            rad++;
        }

        if (pato2.y < PLATAFORMA_Y) {
            if (grav == 15) {
                pato2.y += 10;
                grav = 0;
            }
            if (grav < 15) {
                grav++;
            }
        }

        if (pato3.y < PLATAFORMA_Y && startrad > 5) {
            if (graviole == 15) {
                pato3.y += 10;
                graviole = 0;
            }
            if (graviole < 15) {
                graviole++;
            }
        }
        if (pato1.x == 20 && pato1.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (pato2.x == 20 && pato2.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (pato3.x == 20 && pato3.y == PLATAFORMA_Y) {
            r++;
            if (r < 2) {
                click[12]++;
            }
        }

        if (pato1.x == 200 && pato1.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (pato2.x == 200 && pato2.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (pato3.x == 200 && pato3.y == PLATAFORMA_Y) {
            s++;
            if (s < 2) {
                click[12]++;
            }
        }

        if (q > 0 && (pato1.x == pato2.x && pato1.y == pato2.y)) {
            free(click);
            return 0;
        }


        if (u > 0 && ((pato1.x == pato3.x && pato1.y == pato3.y) || (pato2.x == pato3.x && pato2.y == pato3.y))) {
            free(click);
            return 0;
        }


        // DRAWING STARTS HERE
        // clear screen
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

        // draw bitmap
        SDL_BlitSurface(linha, 0, screen, &grama);
        SDL_BlitSurface(tardis, 0, screen, &timespace);
        Uint32 colorkey = SDL_MapRGB(tardis->format, 255, 255, 255);
        SDL_SetColorKey(tardis, SDL_SRCCOLORKEY, colorkey);

        if (click[12] % 4 == 0) {
            if (pato1.x > 375) {
                if (pato1.y > 70) {
                    free(click);
                    return 0;
                }
            }

            SDL_Surface* spike1 = SDL_LoadBMP("img/spikes1.bmp");
            SDL_SetColorKey(spike1, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(spike1, 0, screen, &espinhos[0]);

        }

        if (click[12] % 4 == 1) {
            if (pato1.x > 375) {
                if (pato1.y > 70) {
                    free(click);
                    return 0;
                }
            }
            SDL_Surface* spike1 = SDL_LoadBMP("img/spikes1.bmp");
//            SDL_SetColorKey(spike1, SDL_SRCCOLORKEY, colorkey);
            SDL_SetColorKey(spike1, SDL_TRUE, SDL_MapRGB(spike1->format, 0, 0xFF, 0xFF ) );
            SDL_BlitSurface(spike1, 0, screen, &espinhos[0]);
        }
        SDL_Surface* spike2 = SDL_LoadBMP("img/spikes2.bmp");
        SDL_SetColorKey(spike2, SDL_SRCCOLORKEY, colorkey);
        SDL_BlitSurface(spike2, 0, screen, &espinhos[1]);

        SDL_Surface* botao1 = SDL_LoadBMP("img/botao1.bmp");
        SDL_SetColorKey(botao1, SDL_SRCCOLORKEY, colorkey);
        SDL_BlitSurface(botao1, 0, screen, &botao[0]);

        SDL_Surface* botao2 = SDL_LoadBMP("img/botao2.bmp");
        SDL_SetColorKey(botao2, SDL_SRCCOLORKEY, colorkey);
        SDL_BlitSurface(botao2, 0, screen, &botao[1]);


        if (click[0] % 4 == 0) {
            SDL_Surface* original = SDL_LoadBMP("img/1.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }

        if (click[0] % 4 == 1) {
            SDL_Surface* original = SDL_LoadBMP("img/2.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }

        if (click[0] % 4 == 2) {
            SDL_Surface* original = SDL_LoadBMP("img/3.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (click[0] % 4 == 3) {
            SDL_Surface* original = SDL_LoadBMP("img/4.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }

        if (click[1] % 4 == 0) {
            SDL_Surface* original = SDL_LoadBMP("img/5.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (click[1] % 4 == 1) {
            SDL_Surface* original = SDL_LoadBMP("img/6.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (click[1] % 4 == 2) {
            SDL_Surface* original = SDL_LoadBMP("img/7.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (click[1] % 4 == 3) {
            SDL_Surface* original = SDL_LoadBMP("img/8.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (click[2] % 2 == 0) {
            SDL_Surface* original = SDL_LoadBMP("img/01.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (click[2] % 2 == 1) {
            SDL_Surface* original = SDL_LoadBMP("img/02.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (click[3] % 2 == 0) {
            SDL_Surface* original = SDL_LoadBMP("img/03.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (click[3] % 2 == 1) {
            SDL_Surface* original = SDL_LoadBMP("img/04.bmp");
            Uint32 colorkey = SDL_MapRGB(original->format, 255, 255, 255);
            SDL_SetColorKey(original, SDL_SRCCOLORKEY, colorkey);
            SDL_BlitSurface(original, 0, screen, &pato1);
        }
        if (q > 0) {
            if (click[4] % 4 == 0) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/1.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }

            if (click[4] % 4 == 1) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/2.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }

            if (click[4] % 4 == 2) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/3.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[4] % 4 == 3) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/4.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[5] % 4 == 0) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/5.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[5] % 4 == 1) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/6.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[5] % 4 == 2) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/7.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[5] % 4 == 3) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/8.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[6] % 2 == 0) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/01.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[6] % 2 == 1) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/02.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[7] % 2 == 0) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/03.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
            if (click[7] % 2 == 1) {
                SDL_Surface* copia1 = SDL_LoadBMP("img/04.bmp");
                Uint32 colorkey = SDL_MapRGB(copia1->format, 255, 255, 255);
                SDL_SetColorKey(copia1, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia1, 0, screen, &pato2);
            }
        }

        if (u > 0) {
            if (click[8] % 4 == 0) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/1.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[8] % 4 == 1) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/2.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[8] % 4 == 2) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/3.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[8] % 4 == 3) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/4.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[9] % 4 == 0) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/5.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[9] % 4 == 1) {
                SDL_Surface *copia2 = SDL_LoadBMP("img/6.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[9] % 4 == 2) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/7.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[9] % 4 == 3) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/8.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[10] % 2 == 0) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/01.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[10] % 2 == 1) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/02.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[11] % 2 == 0) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/03.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
            if (click[11] % 2 == 1) {
                SDL_Surface* copia2 = SDL_LoadBMP("img/04.bmp");
                Uint32 colorkey = SDL_MapRGB(copia2->format, 255, 255, 255);
                SDL_SetColorKey(copia2, SDL_SRCCOLORKEY, colorkey);
                SDL_BlitSurface(copia2, 0, screen, &pato3);
            }
        }

        SDL_Flip(screen);
    }
    int j;
    for (j = 0; j < i; j++) {
        printf("\n%d", vetor[j]);
    }

    freeSDL_Surface(&original);
    freeSDL_Surface(&tardis);
    freeSDL_Surface(&copia1);
    freeSDL_Surface(&copia2);
    freeSDL_Surface(&spikeImg[0]);
    freeSDL_Surface(&spikeImg[1]);
    freeSDL_Surface(&buttonImg[0]);
    freeSDL_Surface(&buttonImg[1]);
    original = NULL;
    tardis = NULL;
    copia1 = NULL;
    copia2 = NULL;
    spikeImg[0] = NULL;
    spikeImg[1] = NULL;
    buttonImg[0] = NULL;
    buttonImg[1] = NULL;

//    delete myWorld;

    free(click);
    return 1;
}
