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
    startTime = 0;
    
    sprite = resources->loadImageFromPath("sprite.png", "player-stand");
    
    startAction(STAND, NULL);
}

Player::Player(double x_, double y_)
{
    ResourceManager *resources = controller->getResourceManager();

    //Set Folder name
    resources->setFolderName("assets/");

    position.setPosition(x_, y_);
    hp = 5;
    speed = 5;
    startTime = 0;
    
    sprite = resources->loadImageFromPath("sprite.png", "player-stand");
    
    startAction(STAND, NULL);
}

Player::~Player()
{
    unsigned i = 0;
    
    for(i = 0; i < actions.size(); i++)
        actions.pop();
    
    for(i = 0; i < timeSpent.size(); i++)
        timeSpent.pop();
    
    for(i = 0; i < actionArg.size(); i++)
        actionArg.pop();
    
    delete[] currentArgs;
    delete sprite;
}

void Player::update()
{
    double x = position.getX();
    double y = position.getY();
    Engine *engine = controller->getEngine();
    
    //Follow the actions on the queue, watching the time
    //int delta = engine->getTimerTick() - startTime;
    int delta = counter;
    
    if(isClone() && currentAction != NOACTION)
    {
        if(!timeSpent.empty() && delta >= timeSpent.front()) //Start next action
        {
            //Move queue
            actions.pop();
            timeSpent.pop();
            actionArg.pop();
        }
    }
    else
    {
        //Animate death/puff
    }
    
    switch (currentAction)
    {
        case MOVE_LEFT:
            setPosition(x-speed, y);
            break;
            
        case MOVE_RIGHT:
            setPosition(x+speed, y);
            break;
            
        case MOVE_UP:   //a ladder for example
            setPosition(x, y-speed/2);
            break;
            
        case MOVE_DOWN:
            setPosition(x, y+speed/2);
            break;
            
        case STAND:
        default:
            //do nothing
            break;
    }
    
    counter++;
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
    //Se acao for igual a atual, a engine esta replicando um mesmo evento
    if(action_ != currentAction)
    {
        //End any other action that started before
        //endAction();
        
        actions.push(action_);
        currentAction = action_;
        
        actionArg.push(args_);
        currentArgs = args_;
        
        startTime = controller->getEngine()->getTimerTick();
        counter = 0;
    }
}

void Player::endAction()
{
    //int delta = controller->getEngine()->getTimerTick() - startTime;
    int delta = counter;
    timeSpent.push(delta);
}

void Player::getAction(Action *action_, int *timeSpent_, int *args_)
{
    if(!actions.empty() && !actionArg.empty() && !timeSpent.empty())
    {
        *action_ = actions.front();
        actions.pop();
        
        args_ = actionArg.front();
        actionArg.pop();
        
        *timeSpent_ = timeSpent.front();
        timeSpent.pop();
    }
    
}

int Player::getStartTime()
{
    return startTime;
}

void Player::copyActionQueue(std::queue<Action> copy_)
{
    //actions = std::queue<Action>(copy_);
    
    while(!copy_.empty())
    {
        actions.push(copy_.front());
        copy_.pop();
    }
}

void Player::copyTimeQueue(std::queue<int> copy_)
{
    //timeSpent = std::queue<int>(copy_);
    
    while(!copy_.empty())
    {
        timeSpent.push(copy_.front());
        copy_.pop();
    }
}

void Player::copyArgsQueue(std::queue<int*> copy_)
{
    //actionArg = std::queue<int*>(copy_);
    
    while(!copy_.empty())
    {
        actionArg.push(copy_.front());
        copy_.pop();
    }
}

void Player::clearQueue()
{
    for(unsigned i = 0; i < actions.size(); i++)
        actions.pop();
    
    for(unsigned i = 0; i < timeSpent.size(); i++)
        timeSpent.pop();
    
    for(unsigned i = 0; i < actionArg.size(); i++)
        actionArg.pop();
}

std::queue<Action> Player::getActionQueue()
{
    return actions;
}

std::queue<int> Player::getTimeQueue()
{
    return timeSpent;
}

std::queue<int*> Player::getArgsQueue()
{
    return actionArg;
}



