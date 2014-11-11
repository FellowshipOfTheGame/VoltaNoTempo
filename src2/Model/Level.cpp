//
//  Trap.cpp
//  VoltaOSX
//
//  Created by X S.G. on 10/7/14.
//  Copyright (c) 2014 Fellowship of the Game. All rights reserved.
//

#include "Level.h"
#include "../Utility/ResourceManager.h"
#include "../Controller/Game.h"

Level::Level()
{
    //Set Folder name
    ResourceManager *resources = controller->getResourceManager();
    resources->setFolderName("assets/");
    
    Engine *engine = controller->getEngine();
    
    //Load
    fontArial = resources->loadFontFromPath("Arial.ttf", "font-arial-16", 16);
    bgMusic = resources->loadAudioFromPath("music.ogg", "bg-music", MUSIC);
    
    spawnText = engine->getTTFmodule()->makeText("Press 'space' to spawn", fontArial, 128, 255, 128, 255);
    spawnText->setPosition(100, 50);
    
    bgMusic->play();
    //bgMusic->setVolume(0.5);

}

Level::~Level()
{
    for(unsigned long i = 0; i < clones.size(); i++)
    {
        delete clones[i];
    }
    clones.clear();
    
    bgMusic->stop();
    delete bgMusic;
    delete fontArial;
    delete spawnText;
}

void Level::handleEvents(EventType type_, EventCode code_)
{
    Engine *engine = controller->getEngine();
    int screenWidth = engine->getGraphicsModule()->getScreenWidth();
    int screenHeight = engine->getGraphicsModule()->getScreenHeight();
    
    if(type_ == KEYUP)
    {
        if(code_ == KEY_SPACE)
        {
            spawnChar(rand()%screenWidth, rand()%(screenHeight-150));
        }
    }
}

void Level::logic()
{
    Engine *engine = controller->getEngine();
    int screenWidth = engine->getGraphicsModule()->getScreenWidth();
    int screenHeight = engine->getGraphicsModule()->getScreenHeight();
    
    for(unsigned long i = 0; i < clones.size(); i++)
    {
        Player *p = clones[i];
        Dimension2D newPos = p->getPosition();
        
        //Apply gravity
        newPos.setPosition(newPos.getX(), newPos.getY()+2);
        
        if(newPos.getY() > screenHeight-150)
            newPos.setPosition(newPos.getX(), screenHeight-150);
        
        p->setPosition(newPos);
    }

}

void Level::render()
{
    controller->addToQueue(spawnText);
    
    for(unsigned long i = 0; i < clones.size(); i++)
    {
        //Add clone to drawing queue
        controller->addToQueue(clones[i]->getSprite());
    }
}

void Level::spawnChar(int posX_, int posY_)
{
    clones.push_back(new Player(posX_, posY_));
}




