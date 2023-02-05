#include "Shotgunner.h"

int Shotgunner::shotgunnerCost = 100;
float Shotgunner::spawnTime = 4.0f;

Shotgunner::Shotgunner(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, bool friendly):
    Unit{texture, 10, 0.09, friendly}
{
    unitSprite.setScale(0.3*1920.0f/unitSprite.getLocalBounds().width, 0.03*1920.0f/unitSprite.getLocalBounds().height);
    if(friendly)
        unitSprite.setPosition(0, (0.72+0.0048*(row-1))*gameHeight);
    else
        unitSprite.setPosition(gameWidth, (0.72+0.0048*(row-1))*gameHeight);
    this->health = 150;
    this->maxHealth = 150;
    this->damage = 70;
    this->range = 5;
    this->accuracy = 70;
    this->speed = 50;
    this->reloadTime = 2;
    this->cost = shotgunnerCost;
    this->unitType = UnitType::Shotgunner;
}

void Shotgunner::fire(vector<shared_ptr<Unit>> enemyUnits)
{
    for(auto& enemy : enemyUnits)
    {
        if(enemy->dying || enemy->friendly == this->friendly)
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

void Shotgunner::reload(const float deltaTime)
{
    if(this->reloadTime <= 0)
    {
        this->reloadTime = 2;
        return;
    }
    this->reloadTime -= deltaTime;
    if(reloadTime <= 0)
        this->reloading = false;
}

void Shotgunner::die()
{
    this->animationMode = AnimationMode::Die;
    this->health = 0;
    this->alive = false;
    this->dying = true;
}

void Shotgunner::advance(const float deltaTime)
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

void Shotgunner::stop()
{
    this->canAdvance = false;
    this->animationMode = AnimationMode::Idle;
}

void Shotgunner::takeDamage(float damageAmount)
{
    this->health -= damageAmount;
    if(this->health <= 0)
        this->die();
}

void Shotgunner::update(vector<shared_ptr<Unit>> units, const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime, const float gameWidth, const float gameHeight)
{
    this->updateAnimation(textures, deltaTime);
    if(this->alive && !this->dying)
    {
        if(this->reloading)
            this->reload(deltaTime);
        if(this->friendly)
        {
            if(this->getPositionX() < (0.01*gameWidth)*this->blockNum)
                this->advance(deltaTime);
            else
                this->blockNum++;
        }
        else
        {
            if(this->getPositionX() > (0.01*gameWidth)*this->blockNum)
                this->advance(deltaTime);
            else
                this->blockNum--;
        }
        this->fire(units);
    }
}
