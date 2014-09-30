#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

typedef enum {NOEVENT, MOUSEDOWN, MOUSEUP, KEYDOWN, KEYUP} EventType;
typedef enum {CODE_NULL, KEY_ESC, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5} EventCode;

class EventHandler
{
protected:
	bool enableRendering;

public:
	virtual bool init() = 0;
	virtual void pollEvent(EventType *type_, EventCode *code_) = 0;
	virtual bool shouldRender() {return enableRendering;}
};

#endif
