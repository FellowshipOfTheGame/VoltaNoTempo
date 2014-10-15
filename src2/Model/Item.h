//
//  Item.h
//  VoltaOSX
//
//  Created by Guilherme S.G. on 10/7/14.
//  Copyright (c) 2014 Fellowship of the Game. All rights reserved.
//

#ifndef __ITEM_H__
#define __ITEM_H__

class Item
{
protected:
    int x;
    int y;
    
public:
    Item();
    ~Item();
    virtual void activate() = 0;
};

class Key : public Item
{
private:
    int color;
    
public:
    Key();
    ~Key();
    
    void activate()
    {
        
    }
};


#endif
