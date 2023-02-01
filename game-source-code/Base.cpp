#include "Base.h"

Base::Base():
    Unit{texture, frameCount, switchTime, friendly}
{
    unitSprite.setOrigin(0.5f*unitSprite.getGlobalBounds().width, 0.5f*unitSprite.getGlobalBounds().height);
    unitSprite.setScale(0.05f*gameWidth/unitSprite.getGlobalBounds().width, 0.05f*gameWidth/unitSprite.getGlobalBounds().height);
    if(friendly)
    {
        unitSprite.setPosition(0.05*gameWidth, 0.5*gameHeight);
    }
    else
    {
        unitSprite.setPosition(0.95*gameWidth, 0.5*gameHeight);
    }
    this->health = 10000;
    this->maxHealth = 10000;
    this->damage = 100;
    this->range = 20;
    this->accuracy = 100;
    this->speed = 0;
    this->reloadTime = 5;
    this->cost = 0;
    this->unitType = UnitType::Rifleman;
}

void Base::fire(vector<shared_ptr<Unit>> enemyUnits)
{

}

void Base::reload(const float deltaTime)
{

}

void Base::die()
{

}

void Base::advance(const float deltaTime)
{

}

void Base::stop()
{

}

void Base::takeDamage(float damageAmount)
{

}
