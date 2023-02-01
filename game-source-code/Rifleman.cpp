#include "Rifleman.h"
#include <cstdlib>

int Rifleman::riflemanCost = 50;
float Rifleman::spawnTime = 0.0f;

Rifleman::Rifleman(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, unsigned int frameCount, float switchTime, bool friendly):
    Unit{texture, frameCount, switchTime, friendly}
{
    if(friendly)
        unitSprite.setPosition(0, (0.72+0.0048*(row-1))*gameHeight);
    else
        unitSprite.setPosition(gameWidth, (0.72+0.0048*(row-1))*gameHeight);
    this->health = 100;
    this->maxHealth = 100;
    this->damage = 50;
    this->range = 10;
    this->accuracy = 50;
    this->speed = 30;
    this->reloadTime = 3;
    this->cost = riflemanCost;
    this->unitType = UnitType::Rifleman;


}

void Rifleman::advance(const float deltaTime)
{
    if(this->canAdvance && !this->shooting)
    {
        this->animationMode = AnimationMode::Run;
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
        if(enemy->dying)
            continue;
        if(abs(enemy->blockNum - this->blockNum) <= this->range)
        {
            if(!this->shooting)
                this->stop();
            if(!this->reloading)
            {
                this->animationMode = AnimationMode::Shoot;
                this->shooting = true;
                if(this->canShoot) //Set to true at the correct spot in the animation
                {
                    if((1+rand()%100) <= this->accuracy)
                        enemy->takeDamage(this->damage);
                    this->reloading = true;
                    this->canShoot = false;
                }
            }
            return;
        }
    }
    if(!this->shooting) //not shooting and no enemies in range
    {
        this->canAdvance = true;
    }
}

void Rifleman::takeDamage(float damageAmount)
{
    this->health -= damageAmount;
    if(this->health <= 0)
        this->die();
}

void Rifleman::die()
{
    this->animationMode = AnimationMode::Die;
    this->health = 0;
    this->alive = false;
    this->dying = true;
}

void Rifleman::reload(const float deltaTime)
{
    if(this->reloadTime <= 0)
    {
        this->reloadTime = 3;
        return;
    }
    this->reloadTime -= deltaTime;
    if(reloadTime <= 0)
        this->reloading = false;
}

void Rifleman::stop()
{
    this->canAdvance = false;
    this->animationMode = AnimationMode::Idle;
}
