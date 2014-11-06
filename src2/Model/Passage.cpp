//
//  Passage.cpp
//  VoltaOSX
//
//  Created by Guilherme S.G. on 11/6/14.
//  Copyright (c) 2014 Fellowship of the Game. All rights reserved.
//

#include "Passage.h"

Door::Door() : Passage()
{
    
}

Door::~Door()
{
    
}

void Door::activate(Item *item_)
{
    Key *key = dynamic_cast<Key*>(item_);   //In the future, other items may open a door: hammer,lockpick, etc.
    bool correct = false;
    
    //Check conditions
    if(key) //object inserted is a key
    {
        correct = key->getColor() && color;
    }
    
    //If already opened lock it, else open it
    enabled = !enabled && correct;
}
