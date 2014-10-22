#include "loading.h"
#include "view.h"
#include <string>

using namespace std;



class AttachedToMain {
private:
	Loading *load;
	string folder;
	string filename;
	int frames;
	int tries;
	int delay;

public:
	AttachedToMain() {
		frames = 4;
		filename = "wifi";
		folder = "frame/wifi";
		load = new Loading(folder, filename, frames);
	}
	~AttachedToMain() {
		delete load;
		load = NULL;
	}

	Loading** getReferenceLoading() {
		return &load;
	}

	void setTries(int num){
		tries = num;
	}

	int getTries() {
		return tries;
	}

	void setDelay(int t){
		delay = t;
	}

	int getDelay() {
		return delay;
	}

};

void quit(int tries, Loading **l) {
	(*l)->stopAnimate();
	tries = 0;
}

int main (int argc, char *argv[]) {
	AttachedToMain *atm = new AttachedToMain();
	atm->setTries(10);
	atm->setDelay(800);

	Loading **load = atm->getReferenceLoading();
	if(load == NULL) {
		cout << "Error ptr para NULL" << endl;
	}
	SDL_Event event;

	for(int tries = atm->getTries(); tries>0; tries--) {
			//Handle events on queue 
   		while (SDL_PollEvent(&event) != 0) {
	        switch (event.type) {
	        	case SDL_QUIT:
	        		quit(tries, load);     	
	                break;

	   		}
		}
		cout << "try: " << tries << endl;
		(*load)->animationLoop(atm->getDelay());
 	}

 	cout << "Exit" << endl;

  	delete atm;
 	atm = NULL;
	return 0;
}
