#include "Unit.h"

Unit::Unit(shared_ptr<sf::Texture> texture, unsigned int frameCount, float switchTime, bool friendly):
    animation{texture, frameCount, switchTime}
{
    unitSprite.setTexture(*texture);
    this->row = 1+rand()%10; //Random number between 1 and 10
    if(friendly)
        blockNum = 1;
    else
        blockNum = 100;
    this->alive = true;
    this->friendly = friendly;
    this->canAdvance = true;
    this->reloading = false;
    this->canShoot = true;
    this->shooting = false;
    this->dying = false;
    this->animationMode = AnimationMode::Idle;
}

void Unit::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(unitSprite);
}

void Unit::updateAnimation(const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime)
{
    switch(this->animationMode)
    {
        case AnimationMode::Idle:
            unitSprite.setTexture(*textures.at(0));
            animation.update(textures.at(0), AnimationMode::Idle, this->shooting, this->dying, this->canShoot, deltaTime, this->friendly);
            break;
        case AnimationMode::Run:
            unitSprite.setTexture(*textures.at(1));
            animation.update(textures.at(1), AnimationMode::Run, this->shooting, this->dying, this->canShoot, deltaTime, this->friendly);
            break;
        case AnimationMode::Shoot:
            unitSprite.setTexture(*textures.at(2));
            animation.update(textures.at(2), AnimationMode::Shoot, this->shooting, this->dying, this->canShoot, deltaTime, this->friendly);
            break;
        case AnimationMode::Die:
            unitSprite.setTexture(*textures.at(3));
            animation.update(textures.at(3), AnimationMode::Die, this->shooting, this->dying, this->canShoot, deltaTime, this->friendly);
            break;
        default:
            throw "Invalid animation mode";
    }
    unitSprite.setTextureRect(animation.textRect);
    unitSprite.setScale(0.03*1920.0f/unitSprite.getLocalBounds().width, 0.03*1920.0f/unitSprite.getLocalBounds().height);
    unitSprite.setOrigin(unitSprite.getLocalBounds().left + 0.5*unitSprite.getLocalBounds().width, unitSprite.getLocalBounds().top + 0.5*unitSprite.getLocalBounds().height);
}
