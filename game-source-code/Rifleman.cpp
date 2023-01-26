#include "Rifleman.h"
#include <cstdlib>

Rifleman::Rifleman(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, unsigned int frameCount, float switchTime, bool friendly):
    Unit{texture, frameCount, switchTime, friendly}
{
    //unitSprite.setScale(0.06*gameWidth/unitSprite.getGlobalBounds().width, 0.06*gameWidth/unitSprite.getGlobalBounds().height);
    //unitSprite.setOrigin(unitSprite.getGlobalBounds().left + 0.5*unitSprite.getGlobalBounds().width, unitSprite.getGlobalBounds().top + 0.5*unitSprite.getGlobalBounds().height);
    if(friendly)
        unitSprite.setPosition(0, (0.65+0.024*(row-1))*gameHeight);
    else
        unitSprite.setPosition(gameWidth, (0.65+0.024*(row-1))*gameHeight);
    this->health = 100;
    this->damage = 100;
    this->range = 10;
    this->accuracy = 50;
    this->speed = 100;
    this->reloadTime = 3;
    this->cost = 50;
    this->unitType = UnitType::Rifleman;

    //Textures
    /*if(!this->idleText.loadFromFile("resources/Rifleman/Idle.png"))
        throw "Cannot load texture";
    if(!this->runText.loadFromFile("resources/Rifleman/Run.png"))
        throw "Cannot load texture";
    if(!this->shootText.loadFromFile("resources/Rifleman/Shoot.png"))
        throw "Cannot load texture";
    if(!this->dieText.loadFromFile("resources/Rifleman/Die.png"))
        throw "Cannot load texture";*/
}

void Rifleman::advance(const float deltaTime)
{
    if(this->canAdvance)
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
            this->stop();
            if(this->reloading == false)
            {
                this->animationMode = AnimationMode::Shoot;
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
    this->animationMode = AnimationMode::Die;
    this->health = 0;
    this->alive = false;
    this->dying = true;
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
