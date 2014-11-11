//
//  Engine.h
//  VoltaOSX
//
//  Created by Guilherme S.G. on 9/30/14.

#ifndef __ENGINE_H__
#define __ENGINE_H__

#include "GraphicsModule.h"
#include "EventHandler.h"
#include "TTFmodule.h"
#include "AudioModule.h"
#include "../Utility/Timer.h"
#include "../syslibs.h"

class Engine
{
protected:
    GraphicsModule *graphics;
    EventHandler *event;
    TTFmodule *ttf;
    AudioModule *mixer;
    Timer fpsTimer;
    
public:
    virtual ~Engine() {}
    virtual bool init() = 0;
    virtual void pollEvent(EventType *type_, EventCode *code_) = 0;
    virtual bool shouldRender() = 0;
    virtual void updateContext() = 0;
    virtual void clear() = 0;
    
    virtual void startTimer()   {fpsTimer.start();}
    virtual int getTimerTick()  {return fpsTimer.getTicks();}
    
    virtual GraphicsModule* getGraphicsModule() {return graphics;}
    virtual EventHandler* getEventHandler()     {return event;}
    virtual TTFmodule* getTTFmodule()           {return ttf;}
    virtual AudioModule* getAudioModule()       {return mixer;}
    
};

#endif
