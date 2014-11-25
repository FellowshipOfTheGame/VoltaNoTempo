//
//  Level.h
//  VoltaOSX
//
//  Created by X S.G. on 10/7/14.
//  Copyright (c) 2014 Fellowship of the Game. All rights reserved.
//

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "../syslibs.h"
#include "../View/Engine.h"
#include "Player.h"

class Level
{
private:
    Player *mainChar;
    std::vector<Player*> clones;
    Font *fontArial;
    Text *spawnText;
    Audio *bgMusic;
    int spawnX, spawnY;
    
    Player* spawnChar(int posX_, int posY_);

public:
    Level();
    ~Level();
    
    void handleEvents(EventType type_, EventCode code_);
    void logic();
    void render();
};


#endif
