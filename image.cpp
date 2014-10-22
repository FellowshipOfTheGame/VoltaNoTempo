#include "image.h"

Image::Image(string folder, string bFilename, int size) {
	pos = 0;		// Initial position
	this->size = size;
	this->folder = folder;
	cout <<"size: " << size << endl;

	Image::load(folder+'/'+bFilename);
}

Image::~Image() {
	Image::clean();
}


// PRIVATE METHODS

SDL_Surface* Image::loadIMG(string src) {
	return IMG_Load(src.c_str());
}

SDL_Surface* Image::loadBMP(string src) {
    return SDL_LoadBMP(src.c_str());
}

void Image::load(string bFilename) {
	vImg.reserve(size);

	// aloca imagens no vetor
	for(int i=0; i<size; i++) {
		vImg.push_back(loadImage(bFilename, i));  
	}
}	

void Image::clean() {
	// Percorre desalocando todas as imagens do vetor
	for(int i=0; i<vImg.size(); i++) {
		if (vImg.at(i) != NULL) {
        	SDL_FreeSurface(vImg.at(i));
        	vImg[i] = NULL;
    	}
	}
	// Limpa vetor
	vImg.clear();
}

SDL_Surface* Image::loadImage(string src, int num) {
	string str;
	if(num < 0) {
		str = src+".png";
	} else {
		char c = (char)(((int)'0')+num);
		str = src+c+".png";
	}
	cout << "string: " << str << endl;
	return Image::loadIMG(str);
}


// PUBLIC METHODS

SDL_Surface** Image::getImage(int pos) {
	if(vImg.size() < pos) {
		cout << "Erro ao pegar imagem..." << endl;
		return NULL;
	}
	return &vImg.at(pos);
}

SDL_Surface** Image::getNextAnimation() {
	Image::nextAnimation();
	return &vImg.at(pos);
}

void Image::nextAnimation() {
	pos++;
	if(pos >= size) {
		pos = 0;
	}
}

SDL_Surface** Image::getImageError() {
	return &vImg.at(size-2);
}
SDL_Surface** Image::getImageSucess() {
	return &vImg.at(size-1);
}