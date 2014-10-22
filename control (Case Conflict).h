#ifndef _CONTROL_H
#define _CONTROL_H

class Control {
private:
	View *view;
	Event *event;
	bool run;
	int sWidth;
	int sHeight;
	bool border;

	void init();	 // on start call
	void destroy();  // on exit call
public:
	Control();
	~Control();

	View** getViewReference();
	Event** getEventReference();

};
#endif