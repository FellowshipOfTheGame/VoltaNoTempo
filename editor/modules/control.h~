#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <SDL2/SDL.h>
#include <iostream>
#include "map.h"

// EMPTY AND SELECT VALUES -- 1 - 9  is the images used by the editor
#define SELECT -2
#define EMPTY -1
#define MODE_UNDO 0
#define MODE_REDO 1
#define MODE_MAP 2

using namespace std;

class Control {
private:
    Map *map;
    Image *img;
    SDL_Event event; 	// Initialize event handler
    SDL_Point mPos;		// Matrix position
    int roll;
    void save(int mode);

public:
	Control();
	~Control();

	void loop();

	void keyDown();

	void mouseButtonDown();

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void update(int x, int y, int value);
};

#endif
