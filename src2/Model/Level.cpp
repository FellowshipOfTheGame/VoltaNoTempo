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
    
    mainChar = new Player(50, 150);
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
        if(code_ == KEY_SPACE)
        {
            //spawnChar(rand()%screenWidth, rand()%(screenHeight-150));
            spawnChar(50, 150);
            mainChar->startAction(NOACTION, NULL);
            
            //Copy current action queue to new clone
            unsigned last = (unsigned)(clones.size()-1);
            clones[last]->copyActionQueue(mainChar->getActionQueue());
            clones[last]->copyTimeQueue(mainChar->getTimeQueue());
            clones[last]->copyArgsQueue(mainChar->getArgsQueue());
            
            //Empty old action queue
            mainChar->clearQueue();
        }
        
        mainChar->endAction();
        mainChar->startAction(STAND, NULL);
    }
    else if(type_ == KEYDOWN)
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
        //mainChar->startAction(STAND, NULL);
    }
    
}

void Level::logic()
{
    Engine *engine = controller->getEngine();
    int screenWidth = engine->getGraphicsModule()->getScreenWidth();
    int screenHeight = engine->getGraphicsModule()->getScreenHeight();
    
    Game::writeToOutput("player pos: ");
    Game::writeToOutput(mainChar->getPosition().getX());
    Game::writeToOutput(" ");
    Game::writeToOutput(mainChar->getPosition().getY());
    Game::writeToOutput("\n");
    
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
        
        if(i >= 0)
        {
            //Follow the actions on the queue, watching the time
            Action currentAction = NOACTION;
            int currentTimeFrame = 0;
            int *currentArgs = NULL;
            
            clones[i]->getAction(&currentAction, &currentTimeFrame, currentArgs);
            if(currentAction == NOACTION)
            {
                //delete clones[i];
                //clones.erase(clones.begin()+i);
            }
        }
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

void Level::spawnChar(int posX_, int posY_)
{
    clones.push_back(new Player(posX_, posY_));
}




