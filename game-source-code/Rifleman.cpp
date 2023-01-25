#include "Rifleman.h"
#include <cstdlib>

Rifleman::Rifleman(sf::Texture* texture, const float gameWidth, const float gameHeight, bool friendly):
    Unit{texture, friendly}
{
    unitSprite.setScale(0.06*gameWidth/unitSprite.getGlobalBounds().width, 0.06*gameWidth/unitSprite.getGlobalBounds().height);
    unitSprite.setOrigin(unitSprite.getGlobalBounds().left + 0.5*unitSprite.getGlobalBounds().width, unitSprite.getGlobalBounds().top + 0.5*unitSprite.getGlobalBounds().height);
    if(friendly)
        unitSprite.setPosition(0, (0.65+0.08*(row-1))*gameHeight);
    else
        unitSprite.setPosition(gameWidth, (0.65+0.08*(row-1))*gameHeight);
    this->health = 100;
    this->damage = 100;
    this->range = 10;
    this->accuracy = 50;
    this->speed = 100;
    this->reloadTime = 3;
}

void Rifleman::advance(const float deltaTime)
{
    if(this->canAdvance)
    {
        if(this->friendly)
            unitSprite.move(sf::Vector2f(this->speed * deltaTime, 0));
        else
            unitSprite.move(sf::Vector2f(-this->speed * deltaTime, 0));
    }
}

void Rifleman::fire(vector<shared_ptr<Unit>> enemyUnits)
{
    for(auto& enemy : enemyUnits)
    {
        if(abs(enemy->blockNum - this->blockNum) <= this->range)
        {
            this->stop();
            if(this->reloading == false)
            {
                if((1+rand()%100) <= this->accuracy)
                    enemy->takeDamage(this->damage);
                this->reloading = true;
            }
            return;
        }
    }
    this->canAdvance = true;
}

void Rifleman::takeDamage(float damageAmount)
{
    this->health -= damageAmount;
    if(health <= 0)
        this->die();
}

void Rifleman::die()
{
    this->health = 0;
    this->alive = false;
}

void Rifleman::reload(const float deltaTime)
{
    if(reloadTime <= 0)
    {
        reloadTime = 3;
        return;
    }
    reloadTime -= deltaTime;
    if(reloadTime <= 0)
        this->reloading = false;
}

void Rifleman::stop()
{
    canAdvance = false;
}
