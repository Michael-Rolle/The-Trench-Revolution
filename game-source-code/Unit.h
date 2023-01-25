#ifndef UNIT_H
#define UNIT_H

#include "Drawable.h"
#include <SFML/Graphics.hpp>

class Unit : public Drawable //Abstract Base Class, use pointer or reference for derived classes
{
    public:
        Unit(sf::Texture* texture); //Scaling of sprite left for derived classes
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;
        virtual void fire() = 0; //Checks to see if closest enemy is in range and shoots
        virtual void reload() = 0; //Checks to see if magazine is empty and reloads
        virtual void die() = 0;
        virtual void advance() = 0; //Moves forward at the units specific speed
        virtual void stop() = 0; //Stops the unit from advancing
        virtual void takeDamage(float damageAmount) = 0;

        virtual ~Unit(){} // virtual desstructor, defaults to doing nothing

    protected:
        sf::Sprite unitSprite;
};

#endif // UNIT_H
