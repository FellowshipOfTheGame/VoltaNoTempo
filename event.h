#ifndef _EVENT_H_
#define _EVENT_H_

#include <SDL2/SDL.h>
#include <iostream>
#include "view.h"
#include "control.h"	

using namespace std;

class Event {
private:
	SDL_Event e; 	// Initialize event handler
	View **view;		
    Control *control;
public:
	Event();
	~Event();

	void loop();

	void keyDown();

	void mouseButtonDown();

	void quit();

#endif