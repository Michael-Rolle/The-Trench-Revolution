#include "Unit.h"

Unit::Unit(sf::Texture* texture, unsigned int frameCount, float switchTime, bool friendly):
    animation{texture, frameCount, switchTime}
{
    unitSprite.setTexture(*texture);
    row = 1+rand()%10; //Random number between 1 and 10
    if(friendly)
        blockNum = 1;
    else
        blockNum = 100;
    alive = true;
    this->friendly = friendly;
    canAdvance = true;
    reloading = false;
}

void Unit::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(unitSprite);
}

void Unit::updateAnimation(AnimationMode animationMode, sf::Texture* texture, const float deltaTime)
{
    switch(animationMode)
    {
        case AnimationMode::Idle:
            unitSprite.setTexture(*texture);
            animation.update(texture, AnimationMode::Idle, deltaTime, this->friendly);
            break;
        case AnimationMode::Run:
            unitSprite.setTexture(*texture);
            animation.update(texture, AnimationMode::Run, deltaTime, this->friendly);
            break;
        case AnimationMode::Shoot:
            unitSprite.setTexture(*texture);
            animation.update(texture, AnimationMode::Shoot, deltaTime, this->friendly);
            break;
        case AnimationMode::Die:
            unitSprite.setTexture(*texture);
            animation.update(texture, AnimationMode::Die, deltaTime, this->friendly);
            break;
        default:
            throw "Invalid animation mode";
    }
    unitSprite.setTextureRect(animation.textRect);
    unitSprite.setScale(0.06*1920.0f/unitSprite.getLocalBounds().width, 0.06*1920.0f/unitSprite.getLocalBounds().height);
    unitSprite.setOrigin(unitSprite.getLocalBounds().left + 0.5*unitSprite.getLocalBounds().width, unitSprite.getLocalBounds().top + 0.5*unitSprite.getLocalBounds().height);
}
