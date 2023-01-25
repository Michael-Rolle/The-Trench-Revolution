#include "Unit.h"

Unit::Unit(sf::Texture* texture)
{
    unitSprite.setTexture(*texture);
    row = 1+rand()%3; //Random number between 1 and 3
    blockNum = 1;
    alive = true;
}

void Unit::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(unitSprite);
}
