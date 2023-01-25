#include "Rifleman.h"
#include <cstdlib>

Rifleman::Rifleman(sf::Texture* texture, const float gameWidth, const float gameHeight):
    Unit{texture}
{
    unitSprite.setScale(0.06*gameWidth/unitSprite.getGlobalBounds().width, 0.06*gameWidth/unitSprite.getGlobalBounds().height);
    unitSprite.setOrigin(unitSprite.getGlobalBounds().left + 0.5*unitSprite.getGlobalBounds().width, unitSprite.getGlobalBounds().top + 0.5*unitSprite.getGlobalBounds().height);
    unitSprite.setPosition(0, (0.65+0.08*(row-1))*gameHeight);
    this->health = 100;
    this->damage = 100;
    this->range = 10;
    this->accuracy = 50;
    this->speed = 100;
    this->reloadTime = 3;
}

void Rifleman::advance(const float deltaTime)
{
    unitSprite.move(sf::Vector2f(this->speed * deltaTime, 0));
}
