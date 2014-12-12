#include "modules/view.h"
#include "modules/image.h"

#define MENU_SPACE 0

View::View() {
    this->window = NULL;
    this->screen = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }
    //Create this->window
    this->window = SDL_CreateWindow("Editor de Mapas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT + MENU_SPACE, SDL_WINDOW_SHOWN);
    if (this->window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
    }

    //Get this->window surface
    this->screen = SDL_GetWindowSurface(this->window);

    if (this->screen == NULL) {
        cout << "Error init screen" << endl;
    }

    // Fill the surface white
    SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0xFF, 0xFF, 0xFF));

    View::update();
}

View::~View() {
    if (this->screen != NULL) {
        SDL_FreeSurface(this->screen);
        this->screen = NULL;
    }

    //Destroy this->window
    SDL_DestroyWindow(this->window);
    if (this->window != NULL) {
        this->window = NULL;
    }

    //Quit SDL subsystems
    SDL_Quit();
}

void View::update() {
    // Update the surface
    SDL_UpdateWindowSurface(window);
}

void View::setOffset(int x, int y) {
    this->offset.x = x;
    this->offset.y = y;
}

void View::setImage(SDL_Surface **ptr, int x, int y) {
    View::setOffset(x, y + MENU_SPACE);
    SDL_BlitSurface(*ptr, 0, screen, &offset);
}

// clear the surface

void View::clear() {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
}

int View::getMenuSpace() {
    return MENU_SPACE;
}
