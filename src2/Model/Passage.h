//
//  Passage.h
//  VoltaOSX
//
//  Created by Guilherme S.G. on 11/6/14.


#ifndef __PASSAGE_H__
#define __PASSAGE_H__

#include "../Utility/Tools.h"
#include "Item.h"
#include "Mechanism.h"

class Passage
{
protected:
    Dimension2D dim;
    bool enabled = true;
    
public:
    
    virtual void enable(bool open_) {enabled = open_;}
    virtual void activate() = 0;
    
};

class Door : public Passage
{
private:
    int color;
    Key *key;
    
public:
    Door();
    ~Door();
    
    void activate(Item *item_);
    void activate(Mechanism *mechanism_);
};

class Bridge : public Passage
{
private:
    Lever *lever;
    
public:
    Bridge();
    ~Bridge();
    
    void activate();
};

class Trapdoor : public Passage
{
private:
    Handle *handle;
    
public:
    Trapdoor();
    ~Trapdoor();
    
    void activate();
};

#endif
