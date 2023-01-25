#include "Unit.h"

Unit::Unit(sf::Texture* texture, bool friendly)
{
    unitSprite.setTexture(*texture);
    row = 1+rand()%3; //Random number between 1 and 3
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
