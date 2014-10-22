#include "view.h"

View::View(int width, int height, SDL_bool border, const char* title) {
	window = NULL;
	screen = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }

    //Create window

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 16);
    

    if (window == NULL) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
    }
    
	//Get this->window surface
    screen = SDL_GetWindowSurface(window);

    if(screen == NULL) {
		cout << "Error init screen" << endl;
    }

    // Fill the surface white
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

    View::update();
}

View::~View() {
	if(screen != NULL) {
        SDL_FreeSurface(screen);
        screen = NULL;
	}

	//Destroy this->window
    if(window != NULL) {
        SDL_DestroyWindow(window);
    	window = NULL;
    }

    //Quit SDL subsystems
    // IMG_Quit();
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
    View::setOffset(x, y);
	SDL_BlitSurface(*ptr, 0, screen, &offset);
}

// clear the surface
void View::clear() {   
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
}

void View::setBackground(int r, int g, int b) {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, r, g, b));
}