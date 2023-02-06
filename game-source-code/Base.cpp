#include "Base.h"

Base::Base(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, bool friendly):
    Unit{texture, 1, 1, friendly}
{
    unitSprite.setOrigin(0.5f*unitSprite.getLocalBounds().width, unitSprite.getLocalBounds().height);
    unitSprite.setScale(0.1f*gameWidth/unitSprite.getGlobalBounds().width, 0.05f*gameWidth/unitSprite.getGlobalBounds().height);
    this->row = 25;
    if(friendly)
        unitSprite.setPosition(0.05*gameWidth, (0.72+0.0048*(row-1))*gameHeight);
    else
        unitSprite.setPosition(0.95*gameWidth, (0.72+0.0048*(row-1))*gameHeight);
    this->blockNum = (int)this->getPositionX()/(0.01*gameWidth);
    this->health = 10000;
    this->maxHealth = 10000;
    this->damage = 100;
    this->range = 20;
    this->accuracy = 100;
    this->speed = 0;
    this->reloadTime = 5;
    this->cost = 0;
    this->unitType = UnitType::Base;
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

void Base::update(vector<shared_ptr<Unit>> units, const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime, const float gameWidth, const float gameHeight)
{
    this->updateAnimation(textures, deltaTime);
}
