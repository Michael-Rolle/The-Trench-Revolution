#ifndef SNIPER_H
#define SNIPER_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class Sniper : public Unit
{
    public:
        Sniper(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, bool friendly);
        virtual void fire(vector<shared_ptr<Unit>> enemyUnits) override; //Checks to see if closest enemy is in range and shoots
        virtual void reload(const float deltaTime) override; //Takes time off the reloadTime counter
        virtual void die() override;
        virtual void advance(const float deltaTime) override; //Moves forward at the units specific speed
        virtual void stop() override; //Stops the unit from advancing
        virtual void takeDamage(float damageAmount) override;

        static int sniperCost;
        static float spawnTime; //time you have to wait between spawning units

        virtual ~Sniper(){}
};

#endif // SNIPER_H
