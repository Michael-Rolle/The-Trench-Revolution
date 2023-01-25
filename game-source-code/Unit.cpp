#include "Unit.h"

Unit::Unit(sf::Texture* texture)
{
    unitSprite.setTexture(*texture);
}

void Unit::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(unitSprite);
}
