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

typedef enum {NOACTION, STAND, MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, JUMP, FALL, USE_ITEM, SELECT_ITEM, ACTIVATE} Action;

class Player
{
private:
    Action currentAction;
    int *currentArgs;
    int startTime;
    int timeCounter;
    
protected:
    Dimension2D position;
    int hp, speed;
    bool cloned = true;
    std::vector<Item*> inventory;
    
    //Time mechanism
    Player *previousSelf;
    std::queue<Action> actions;
    std::queue<int> timeSpent;
    std::queue<int*> actionArg;
    
    //Partes da View
    Image *sprite;
    Audio *footsteps;
    
    
public:
    Player(Dimension2D position_);
    Player(double x_, double y_);
    ~Player();
    
    void update();
    
    void setPosition(Dimension2D position_);
    void setPosition(double x_, double y_);
    void setHP(int hp_);
    
    Dimension2D getPosition();
    int getHP();
    Image *getSprite() {return sprite;}
    
    void startAction(Action action_, int *args_);
    void endAction();
    void getAction(Action *action_, int *timeSpent_, int *args_);
    int getStartTime();
    int getCurrentTimeFrame();
    
    void copyActionQueue(std::queue<Action> copy_);
    void copyTimeQueue(std::queue<int> copy_);
    void copyArgsQueue(std::queue<int*> copy_);
    void clearQueue();
    
    std::queue<Action> getActionQueue();
    std::queue<int> getTimeQueue();
    std::queue<int*> getArgsQueue();
    
    bool isClone()                  {return cloned;}
    void setCloned(bool cloned_)    {cloned = cloned_;}
};

//
//List here the classes
//

class Thief : public Player
{
private:
    Item *lockpick;
    
public:
    Thief() : Player(0,0)
    {
        
    }
    
    ~Thief()
    {
        
    }
    
};





#endif