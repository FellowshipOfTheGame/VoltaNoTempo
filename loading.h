#ifndef _LOADING_H
#define _LOADING_H

#include <string>
#include <iostream>
#include "image.h"
#include "view.h"

using namespace std;

class Loading {
private:
	int size;		// animation
	Image *img;
	SDL_Surface** ptr_surface;
	View *view;
	bool stop;

public:
	Loading(string folder, string src, int size);
	~Loading();
	void animationLoop(int delay);
	void stopAnimate();
	void setImageError();	
	void setImageSucess();	

};

#endif