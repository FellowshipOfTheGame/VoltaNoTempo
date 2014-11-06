//
//  Mechanism.h
//  VoltaOSX
//
//  Created by Guilherme S.G. on 11/6/14.
//  Copyright (c) 2014 Fellowship of the Game. All rights reserved.
//

#ifndef __MECHANISM_H__
#define __MECHANISM_H__

class Mechanism
{
protected:
    bool enable = false;
    
public:
    
    virtual void activate() = 0;
    
};

class Switch : public Mechanism
{
private:
    
    
public:
    Switch();
    ~Switch();
    
    void activate();
};

class Lever : public Mechanism
{
private:
    
    
public:
    Lever();
    ~Lever();
    
    void activate();
    
};

class Handle : public Mechanism
{
private:
    
    
public:
    Handle();
    ~Handle();
    
    void activate();
    
};

#endif
