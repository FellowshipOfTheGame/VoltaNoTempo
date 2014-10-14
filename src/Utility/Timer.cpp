//
//  Timer.cpp
//  VoltaOSX
//
//  Created by Guilherme S.G. on 9/30/14.


#include "Timer.h"

Timer::Timer()
{
    startTicks = 0;
    pausedTicks = 0;
    status = STOP;
}

void Timer::start()
{
    status = START;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop()
{
    status = STOP;
    startTicks = pausedTicks = 0;
}

void Timer::pause()
{
    if(status == PAUSE) //unpause
    {
        status = START;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
    else
    {
        status = PAUSE;
        pausedTicks = SDL_GetTicks() - startTicks;
    }
    
}

int Timer::getTicks()
{
    int time = 0;
    
    if(status == START)
    {
        time = SDL_GetTicks() - startTicks;
    }
    else if(status == PAUSE)
        time = pausedTicks;
    
    return time;
}

TimerStatus Timer::getStatus()
{
    return status;
}
