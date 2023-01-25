#ifndef RIFLEMAN_H
#define RIFLEMAN_H
#include "Unit.h"
#include <SFML/Graphics.hpp>

class Rifleman : public Unit
{
    public:
        Rifleman(sf::Texture* texture, const float gameWidth, const float gameHeight);
        virtual void fire() override {} //Checks to see if closest enemy is in range and shoots
        virtual void reload() override {} //Checks to see if magazine is empty and reloads
        virtual void die() override {}
        virtual void advance() override {} //Moves forward at the units specific speed
        virtual void stop() override {} //Stops the unit from advancing
        virtual void takeDamage(float damageAmount) override {}
        int getBlock() { return blockNum; }

        virtual ~Rifleman(){}

    private:
        float health;
        float damage;
        float range; //Range out of 100 blocks
        float accuracy; //Percentage chance of hitting a shot
        float speed; //Blocks per minute
        float reloadTime; //Time it takes before being able to fire again
        int blockNum; //The current block that the soldier is in
};

#endif // RIFLEMAN_H
