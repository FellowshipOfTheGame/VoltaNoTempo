#ifndef _IMAGE_H
#define _IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Image {
private:
	int pos;
	int size;
	int real_size;
	string folder;
	vector<SDL_Surface *> vImg;
	SDL_Surface* img;

	SDL_Surface* loadIMG(string src);
	SDL_Surface* loadBMP(string src);

	void load(string bFilename);
	void clean();
	SDL_Surface* loadImage(string src, int num);

public:
	Image(string folder, string bFilename, int size);
	~Image();

	SDL_Surface** getImage(int pos);

	// Metodos particulares para animação de imagens 
	SDL_Surface** getNextAnimation();
	void nextAnimation();
	SDL_Surface** getImageError();
	SDL_Surface** getImageSucess();
};	

#endif