#include "control.h"

Control::Control() {	
	border = SDL_F;
	sWidth = 200;
	sHeight = 200;
	Control::init();
}

Control::~Control() {
	Control::destroy();
}


// Private
void Control::init() {
	view = new View(sWidth, sHeight, border, "Loading");
	event = new Event();
}

void Control::destroy() {
	delete view;
	delete event;
}



SDL_bool Control::convertToSDLbool(bool state) {
	return (state) ? SDL_TRUE : SDL_FALSE;
}

// Public
void Control::setBorder(bool state) {
	border = Control::convertToSDLbool(state);
}

void Control::setBorder(SDL_bool state) {
	border = state;
}

void Control::start() {
	Control::init();
}

void Control::quit() {
	Control::destroy();
}

// Get reference to the instance of view
View **Control::getViewReference() {
	return &view;
}


// Get reference to the instance of control
Event **Control::getEventReference() {
	return &event;
}

bool Control::isRunning() {
	return run;
}

void Control::setRunning() {
		this->run = run;	
}


