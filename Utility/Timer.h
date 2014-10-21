//
//  Timer.h
//  VoltaOSX
//
//  Created by Guilherme S.G. on 9/30/14.

#ifndef __TIMER_H__
#define __TIMER_H__

#include "../syslibs.h"
#include "SDL2/SDL.h"

typedef enum {STOP, START, PAUSE} TimerStatus;

class Timer
{
private:
    int startTicks;
    int pausedTicks;
    TimerStatus status;
    
public:
    Timer();
    
    void start();
    void stop();
    void pause();
    
    int getTicks();
    TimerStatus getStatus();
};

#endif
