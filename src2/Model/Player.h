//
//  Player.h
//  VoltaOSX

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../syslibs.h"
#include "../Utility/Tools.h"
#include "Item.h"
#include "../View/GraphicsModule.h"
#include "../View/AudioModule.h"

class Player
{
private:
    Dimension2D position;
    int hp;
    std::vector<Item*> inventory;
    
    //Partes da View
    Image *sprite;
    Audio *footsteps;
    
    
public:
    Player(Dimension2D position_);
    Player(int x_, int y_);
    ~Player();
    
    void setPosition(Dimension2D position_);
    void setPosition(int x_, int y_);
    void setHP(int hp_);
    
    Dimension2D getPosition();
    int getHP();
    
    Image *getSprite() {return sprite;}
    
};


#endif
