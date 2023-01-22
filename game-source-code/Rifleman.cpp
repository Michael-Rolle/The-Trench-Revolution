#include "Rifleman.h"

Rifleman::Rifleman(sf::Texture* texture)
{
    this->health = 100;
    this->damage = 100;
    this->range = 10;
    this->accuracy = 50;
    this->speed = 100;
}
