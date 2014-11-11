//
//  Player.cpp
//  VoltaOSX

#include "Player.h"
#include "../Utility/ResourceManager.h"
#include "../Controller/Game.h"

Player::Player(Dimension2D position_)
{
    ResourceManager *resources = controller->getResourceManager();
    
    //Set Folder name
    resources->setFolderName("assets/");

    //Set initial position
    position = position_;
    

    //Set initial stats
    hp = 5;
    speed = 5;
    
    sprite = resources->loadImageFromPath("sprite.png", "player-stand");
}

Player::Player(double x_, double y_)
{
    ResourceManager *resources = controller->getResourceManager();

    //Set Folder name
    resources->setFolderName("assets/");

    position.setPosition(x_, y_);
    hp = 5;
    speed = 5;
    
    sprite = resources->loadImageFromPath("sprite.png", "player-stand");
}

Player::~Player()
{
    unsigned i = 0;
    
    for(i = 0; i < actions.size(); i++)
        actions.pop();
    
    for(i = 0; i < timeSpent.size(); i++)
        timeSpent.pop();
    
    for(int i = 0; i < actionArg.size(); i++)
        actionArg.pop();
    
    delete[] currentArgs;
    delete sprite;
    //delete footsteps;
}

void Player::update()
{
    double x = position.getX();
    double y = position.getY();
    
    switch (currentAction)
    {
        case MOVE_LEFT:
            position.setPosition(x-speed, y);
            break;
            
        case MOVE_RIGHT:
            position.setPosition(x+speed, y);
            break;
            
        case MOVE_UP:   //a ladder for example
            position.setPosition(x, y-speed/2);
            break;
            
        case MOVE_DOWN:
            position.setPosition(x, y+speed/2);
            break;
            
        case STAND:
        default:
            
            break;
    }
}

void Player::setPosition(Dimension2D position_)
{
    position = position_;
    sprite->setPosition(position_.getX(), position_.getY());
}

void Player::setPosition(double x_, double y_)
{
    position.setPosition(x_, y_);
    sprite->setPosition(x_, y_);
}

void Player::setHP(int hp)
{
    this->hp = hp;
}

Dimension2D Player::getPosition()
{
    return position;
}

int Player::getHP()
{
    return hp;
}

void Player::startAction(Action action_, int *args_)
{
    actions.push(action_);
    currentAction = action_;
    
    actionArg.push(args_);
    currentArgs = args_;
    
    startTime = controller->getEngine()->getTimerTick();
}

void Player::endAction()
{
    int delta = controller->getEngine()->getTimerTick() - startTime;
    timeSpent.push(delta);
}

void Player::storeAction()
{
    
}

void Player::getAction(Action *action_, int *timeSpent_, int **args_)
{
    if(!actions.empty() && !actionArg.empty() && !timeSpent.empty())
    {
        action_ = &actions.front();
        actions.pop();
        
        args_ = &actionArg.front();
        actionArg.pop();
        
        timeSpent_ = &timeSpent.front();
        timeSpent.pop();
    }
    
}



