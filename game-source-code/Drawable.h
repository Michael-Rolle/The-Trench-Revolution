#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "GameState.h"
#include <SFML/Graphics.hpp>

class Drawable //Abstract Base Class for drawable objects
{
    public:
        virtual void draw(sf::RenderWindow& window, const GameState gameState) = 0;
        virtual ~Drawable(){}
};

#endif // DRAWABLE_H
