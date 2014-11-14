#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

typedef enum {NOEVENT, MOUSEDOWN, MOUSEUP, KEYDOWN, KEYUP, KEYPRESSED} EventType;

typedef enum {CODE_NULL, KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_SPACE, KEY_ARROWLEFT, KEY_ARROWUP, KEY_ARROWRIGHT, KEY_ARROWDOWN} EventCode;

class EventHandler
{
protected:
	bool enableRendering;

public:
	virtual bool init() = 0;
	virtual void pollEvent(EventType *type_, EventCode *code_) = 0;
	virtual bool shouldRender() {return enableRendering;}   //TODO: add timer
};

#endif
