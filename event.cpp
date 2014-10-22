#include "event.h"


Event::Event() {
	view = new View();
	Event::loop();
}

Event::~Event() {
	delete map;
	map = NULL;
}

void Event::loop() {
	
	while(control->isRunning()) {
	//Handle es on queue 
    while (SDL_PollEvent(&e) != 0) {
	      switch (e.type) {
	        	case SDL_QUIT: 
	                Event::quit();
	                break;

	            case SDL_KEYDOWN:
	            	Event::keyDown();
	            	break;

	        	case SDL_MOUSEBUTTONDOWN:
	        		Event::mouseButtonDown();
	        		break;
	   		}
		}
	}
}

void Event::keyDown() { 
	switch (e.key.keysym.sym) {
		case SDLK_ESCAPE:
        	map->quit();
    		break;

  }
}

void Event::mouseButtonDown() {
    // TODO
}

void Event::quit() {
    delete view;
    view = NULL;
}
