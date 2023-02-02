#include "Base.h"

Base::Base(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, unsigned int frameCount, float switchTime, bool friendly):
    Unit{texture, frameCount, switchTime, friendly}
{
    unitSprite.setOrigin(0.5f*unitSprite.getLocalBounds().width, 0.5f*unitSprite.getLocalBounds().height);
    unitSprite.setScale(0.1f*gameWidth/unitSprite.getGlobalBounds().width, 0.05f*gameWidth/unitSprite.getGlobalBounds().height);
    if(friendly)
        unitSprite.setPosition(0.05*gameWidth, 0.8*gameHeight);
    else
        unitSprite.setPosition(0.95*gameWidth, 0.8*gameHeight);
    this->health = 10000;
    this->maxHealth = 10000;
    this->damage = 100;
    this->range = 20;
    this->accuracy = 100;
    this->speed = 0;
    this->reloadTime = 5;
    this->cost = 0;
    this->unitType = UnitType::Base;
    this->row = 19;
}

void Base::fire(vector<shared_ptr<Unit>> enemyUnits)
{
    return;
}

void Base::reload(const float deltaTime)
{
    return;
}

void Base::die()
{
    this->health = 0;
    this->alive = false;
    //this->dying = true;
}

void Base::advance(const float deltaTime)
{
    return;
}

void Base::stop()
{
    return;
}

void Base::takeDamage(float damageAmount)
{
    this->health -= damageAmount;
    if(this->health <= 0)
    {
        this->die();
    }
}
