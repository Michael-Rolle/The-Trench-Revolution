#include "MachineGunner.h"

int MachineGunner::machineGunnerCost = 200;
float MachineGunner::spawnTime = 8.0f;

MachineGunner::MachineGunner(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, bool friendly):
    Unit{texture, 10, 0.12, friendly}
{
    unitSprite.setScale(0.3*1920.0f/unitSprite.getLocalBounds().width, 0.03*1920.0f/unitSprite.getLocalBounds().height);
    if(friendly)
        unitSprite.setPosition(0, (0.72+0.0048*(row-1))*gameHeight);
    else
        unitSprite.setPosition(gameWidth, (0.72+0.0048*(row-1))*gameHeight);
    this->health = 200;
    this->maxHealth = 200;
    this->damage = 10;
    this->range = 10;
    this->accuracy = 60;
    this->speed = 20;
    this->reloadTime = 0.2;
    this->cost = machineGunnerCost;
    this->unitType = UnitType::MachineGunner;
}

void MachineGunner::fire(vector<shared_ptr<Unit>> enemyUnits)
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

void MachineGunner::reload(const float deltaTime)
{
    if(this->reloadTime <= 0)
    {
        this->reloadTime = 0.2;
        return;
    }
    this->reloadTime -= deltaTime;
    if(reloadTime <= 0)
        this->reloading = false;
}

void MachineGunner::die()
{
    this->animationMode = AnimationMode::Die;
    this->health = 0;
    this->alive = false;
    this->dying = true;
}

void MachineGunner::advance(const float deltaTime)
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

void MachineGunner::stop()
{
    this->canAdvance = false;
    this->animationMode = AnimationMode::Idle;
}

void MachineGunner::takeDamage(float damageAmount)
{
    this->health -= damageAmount;
    if(this->health <= 0)
        this->die();
}
