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
    

    //Set initial hp
    hp = 5;
    
    sprite = resources->loadImageFromPath("sprite.png", "player-stand");
}

Player::Player(int x_, int y_)
{
    ResourceManager *resources = controller->getResourceManager();

    //Set Folder name
    resources->setFolderName("assets/");

    position.setPosition(x_, y_);
    hp = 5;
    
    sprite = resources->loadImageFromPath("sprite.png", "player-stand");
}

Player::~Player()
{
    
}

void Player::setPosition(Dimension2D position_)
{
    position = position_;
    sprite->setPosition(position_.getX(), position_.getY());
}

void Player::setPosition(int x_, int y_)
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

