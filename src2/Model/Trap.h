//
//  Trap.h
//  VoltaOSX
//
//  Created by X S.G. on 10/7/14.
//  Copyright (c) 2014 Fellowship of the Game. All rights reserved.
//

#ifndef __TRAP_H__
#define __TRAP_H__

class Trap
{
protected:
    int x;
    int y;

public:
    Trap();
    ~Trap();
    virtual void activate() = 0;
};

class Spike : public Trap
{
private:

public:

    Spike();
    ~Spike();

    void activate()
    {

    }
};


#endif
