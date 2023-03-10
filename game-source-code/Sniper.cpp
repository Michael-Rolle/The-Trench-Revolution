#include "Sniper.h"

int Sniper::sniperCost = 150;
float Sniper::spawnTime = 6.0f;

Sniper::Sniper(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, bool friendly):
    Unit{texture, 10, 0.11, friendly}
{
    unitSprite.setScale(0.2*1920.0f/unitSprite.getLocalBounds().width, 0.02*1920.0f/unitSprite.getLocalBounds().height);
    unitSprite.setOrigin(0.5f*unitSprite.getGlobalBounds().width, unitSprite.getGlobalBounds().height);
    if(friendly)
        unitSprite.setPosition(0, (0.72+0.0048*(row-1))*gameHeight);
    else
        unitSprite.setPosition(gameWidth, (0.72+0.0048*(row-1))*gameHeight);
    this->health = 50;
    this->maxHealth = 50;
    this->damage = 100;
    this->range = 20;
    this->accuracy = 80;
    this->speed = 30;
    this->reloadTime = 8;
    this->cost = sniperCost;
    this->unitType = UnitType::Sniper;
}

void Sniper::fire(vector<shared_ptr<Unit>> enemyUnits)
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

void Sniper::reload(const float deltaTime)
{
    if(this->reloadTime <= 0)
    {
        this->reloadTime = 8;
        return;
    }
    this->reloadTime -= deltaTime;
    if(reloadTime <= 0)
        this->reloading = false;
}

void Sniper::die()
{
    this->animationMode = AnimationMode::Die;
    this->health = 0;
    this->alive = false;
    this->dying = true;
}

void Sniper::advance(const float deltaTime)
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

void Sniper::stop()
{
    this->canAdvance = false;
    this->animationMode = AnimationMode::Idle;
}

void Sniper::takeDamage(float damageAmount)
{
    this->health -= damageAmount;
    if(this->health <= 0)
        this->die();
}

void Sniper::update(vector<shared_ptr<Unit>> units, const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime, const float gameWidth, const float gameHeight)
{
    this->updateAnimation(textures, deltaTime);
    if(this->alive && !this->dying)
    {
        if(this->reloading)
            this->reload(deltaTime);
        if(this->friendly)
        {
            if(this->getPosition().x < (0.01*gameWidth)*this->blockNum)
                this->advance(deltaTime);
            else
                this->blockNum++;
        }
        else
        {
            if(this->getPosition().x > (0.01*gameWidth)*this->blockNum)
                this->advance(deltaTime);
            else
                this->blockNum--;
        }
        this->fire(units);
    }
}

void Sniper::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(unitSprite);
    window.draw(redHealthBar);
    window.draw(greenHealthBar);
}
