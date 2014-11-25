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
    
    spawnX = 50;
    spawnY = 300;
    mainChar = new Player(spawnX, spawnY);
    mainChar->setCloned(false);
}

Level::~Level()
{
    for(unsigned long i = 0; i < clones.size(); i++)
    {
        delete clones[i];
    }
    clones.clear();
    delete mainChar;
    
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
        //Spawn the player on the past/future and make its previous self a clone
        if(code_ == KEY_SPACE)
        {
            mainChar->endAction();
            mainChar->setCloned(true);
            clones.push_back(mainChar);
            
            mainChar = spawnChar(spawnX, spawnY);
            mainChar->setCloned(false);
            
            //Reset clones spawn point
            for(int i = 0; i < clones.size(); i++)
                clones[i]->setPosition(spawnX, spawnY);
        }
    }
    else if(type_ == KEYDOWN || type_ == KEYHOLD)
    {
        switch (code_)
        {
            case KEY_ARROWLEFT:
                mainChar->startAction(MOVE_LEFT, NULL);
                break;
                
            case KEY_ARROWRIGHT:
                mainChar->startAction(MOVE_RIGHT, NULL);
                break;
                
            case KEY_ARROWUP:
                //Check for ladders, etc
                break;
                
            case KEY_ARROWDOWN:
                //Check for ladders, etc
                break;
                
            default:
                break;
        }
    }
    else //no event has occured
    {
        mainChar->startAction(STAND, NULL);
    }
    
}

void Level::logic()
{
    Engine *engine = controller->getEngine();
    int screenWidth = engine->getGraphicsModule()->getScreenWidth();
    int screenHeight = engine->getGraphicsModule()->getScreenHeight();
    
    /*Game::writeToOutput("player pos: ");
    Game::writeToOutput(mainChar->getPosition().getX());
    Game::writeToOutput(" ");
    Game::writeToOutput(mainChar->getPosition().getY());
    Game::writeToOutput("\n");*/
    
    //Apply gravity
    for(int i = -1; i < (int)clones.size(); i++)
    {
        Player *p;
        
        if(i == -1)
            p = mainChar;
        else
            p = clones[i];
        
        Dimension2D newPos = p->getPosition();
        
        newPos.setPosition(newPos.getX(), newPos.getY()+2);
        
        if(newPos.getY() > screenHeight-150)
            newPos.setPosition(newPos.getX(), screenHeight-150);
        
        p->setPosition(newPos);
        p->update();
    }
    
}

void Level::render()
{
    controller->addToQueue(spawnText);
    
    //Add clones to drawing queue
    for(unsigned long i = 0; i < clones.size(); i++)
    {
        controller->addToQueue(clones[i]->getSprite());
    }
    
    //Add main character
    controller->addToQueue(mainChar->getSprite());
}

Player* Level::spawnChar(int posX_, int posY_)
{
    return new Player(posX_, posY_);
}




