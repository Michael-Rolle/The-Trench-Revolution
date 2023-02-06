#include "Tank.h"
#include <cmath>
#include <iostream>

int Tank::tankCost = 500;
float Tank::spawnTime = 15.0f;

Tank::Tank(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, bool friendly):
    Unit{texture, 1, 1, friendly}
{
    unitSprite.setScale(0.07*1920.0f/unitSprite.getLocalBounds().width, 0.031*1920.0f/unitSprite.getLocalBounds().height);
    unitSprite.setOrigin(0.5f*unitSprite.getGlobalBounds().width, unitSprite.getGlobalBounds().height);
    if(friendly)
        unitSprite.setPosition(0, (0.72+0.0048*(row-1))*gameHeight);
    else
        unitSprite.setPosition(gameWidth, (0.72+0.0048*(row-1))*gameHeight);
    this->health = 1000;
    this->maxHealth = 1000;
    this->damage = 300;
    this->range = 10;
    this->accuracy = 80;
    this->speed = 20;
    this->reloadTime = 10;
    this->cost = tankCost;
    this->unitType = UnitType::Tank;

    if(!explosionText.loadFromFile("resources/Explosion.png"))
        throw "Cannot load texture";
    this->exploding = false;
    this->switchTime = 0.15f;
    this->currentFrame = 0;
    this->totalTime = 0.0f;
    this->radius = 60; //radius of explosion
    explosion.setTexture(explosionText);
    explosion.setOrigin(explosion.getLocalBounds().left + 0.5f*explosion.getLocalBounds().width, explosion.getLocalBounds().top + 0.5f*explosion.getLocalBounds().height);
    explosion.setScale(1.5*6*2*this->radius/explosion.getLocalBounds().width, 1.5*2*this->radius/explosion.getLocalBounds().height);
    explosionTextRect.width = explosion.getLocalBounds().width/6.0f;
    explosionTextRect.height = explosion.getLocalBounds().height;
    explosion.setTextureRect(explosionTextRect);
}

vector<shared_ptr<Unit>> Tank::enemiesHitByShot(vector<shared_ptr<Unit>>& enemies, const int shotBlockNum, const int shotRow)
{
    vector<shared_ptr<Unit>> enemiesHit;
    for(auto& enemy : enemies)
    {
        if(enemy->friendly == this->friendly)
            continue;
        if(sqrt(pow(abs((0.01f*1920.0f)*(shotBlockNum-enemy->blockNum)), 2) + pow(abs((0.0048*1080.0f)*(shotRow-enemy->row)), 2)) <= this->radius)
            enemiesHit.push_back(enemy);
    }
    return enemiesHit;
}

void Tank::fire(vector<shared_ptr<Unit>> enemyUnits)
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
                this->exploding = true;
                this->animationMode = AnimationMode::Shoot;
                this->shooting = true;
                auto shotBlockNum = enemy->blockNum - rand()%4 + rand()%4; //can vary by 3 from original blockNum
                auto shotRow = enemy->row - rand()%11 + rand()%11; //can vary by 10 from original blockNum
                explosion.setPosition(sf::Vector2f{shotBlockNum*0.01f*1920.0f, (0.72f+0.0048f*(shotRow-1))*1080.0f});
                explosion.setOrigin(explosion.getLocalBounds().left + 0.5f*explosion.getLocalBounds().width, explosion.getLocalBounds().top + 0.5f*explosion.getLocalBounds().height);
                auto enemiesHit = enemiesHitByShot(enemyUnits, shotBlockNum, shotRow);
                for(auto& hitEnemy : enemiesHit)
                    hitEnemy->takeDamage(this->damage);
                this->reloading = true;
                this->canShoot = false;
            }
            return;
        }
    }
    if(!this->shooting) //not shooting and no enemies in range
    {
        this->canAdvance = true;
    }
}

void Tank::reload(const float deltaTime)
{
    if(this->reloadTime <= 0)
    {
        this->reloadTime = 10;
        return;
    }
    this->reloadTime -= deltaTime;
    if(reloadTime <= 0)
        this->reloading = false;
}

void Tank::die()
{
    this->animationMode = AnimationMode::Die;
    this->health = 0;
    this->alive = false;
    this->dying = true;
}

void Tank::advance(const float deltaTime)
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

void Tank::stop()
{
    this->canAdvance = false;
    this->animationMode = AnimationMode::Idle;
}

void Tank::takeDamage(float damageAmount)
{
    this->health -= damageAmount;
    if(this->health <= 0)
        this->die();
}

void Tank::update(vector<shared_ptr<Unit>> units, const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime, const float gameWidth, const float gameHeight)
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
    if(this->exploding)
    {
        this->totalTime += deltaTime;
        if(this->totalTime >= this->switchTime)
        {
            this->totalTime -= this->switchTime;
            this->currentFrame++;
            if(this->currentFrame >= 6)
            {
                this->exploding = false;
                this->currentFrame = 0;
            }
        }
        this->explosionTextRect.left = this->currentFrame*this->explosionTextRect.width;
        this->explosion.setTextureRect(this->explosionTextRect);
        cout << "Tank x position: " + to_string(this->unitSprite.getPosition().x) + "\nTank y position: " + to_string(this->unitSprite.getPosition().y) << endl;
        cout << "Explosion x position: " + to_string(this->explosion.getPosition().x) + "\nExplosion y position: " + to_string(this->explosion.getPosition().y) << endl;
    }
}

void Tank::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(unitSprite);
    window.draw(redHealthBar);
    window.draw(greenHealthBar);
    if(this->exploding)
        window.draw(explosion);
}
