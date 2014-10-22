#ifndef _CONTROL_H
#define _CONTROL_H

#include <string>

using namespace std;

class Control {
private:
	bool load;
	bool init;
	bool run;
	SDL_bool border;
public:
	Control();
	~Control();
	
	bool isRunning();	
	void setRunning(bool run);

};
#endif