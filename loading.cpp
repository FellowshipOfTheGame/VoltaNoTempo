#include "loading.h"

Loading::Loading(string folder, string src, int size) {
	view = new View(200, 200, SDL_FALSE, "loading");
	
	// Verifica se o tamanho não é zero
	if(size == 0) cout << "Erro, size = 0..." << endl;
	
	this->size = size;

	img = new Image(folder, src, size);		// Inicial src
	stop = false;
}

Loading::~Loading() {
	delete img;
	delete view;
	img = NULL;
	view = NULL;
	ptr_surface = NULL;
}

void Loading::animationLoop(int delay) {
	if(stop) {
		cout << "Stopped" << endl;
		return;
	}	
	for(int i = 0; i<size; i++) {
		ptr_surface = img->getNextAnimation();
		view->clear();	
		view->setImage(ptr_surface, 30, 30);
		view->update();
		SDL_Delay(delay);
	}
}

void Loading::stopAnimate() {
	stop = true;
}

void Loading::setImageError() {
	ptr_surface = img->getImageError();
	view->clear();	
	view->setImage(ptr_surface, 30, 30);
	view->update();	
}
void Loading::setImageSucess() {
	ptr_surface = img->getImageSucess();
	view->clear();	
	view->setImage(ptr_surface, 30, 30);
	view->update();	
}