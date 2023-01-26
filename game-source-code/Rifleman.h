#ifndef RIFLEMAN_H
#define RIFLEMAN_H
#include "Unit.h"
#include <SFML/Graphics.hpp>
#include <memory>

using namespace std;

class Rifleman : public Unit
{
    public:
        Rifleman(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, unsigned int frameCount, float switchTime, bool friendly);
        virtual void fire(vector<shared_ptr<Unit>> enemyUnits) override; //Checks to see if closest enemy is in range and shoots
        virtual void reload(const float deltaTime) override; //Takes time off the reloadTime counter
        virtual void die() override;
        virtual void advance(const float deltaTime) override; //Moves forward at the units specific speed
        virtual void stop() override; //Stops the unit from advancing
        virtual void takeDamage(float damageAmount) override;

        virtual ~Rifleman(){}

    private:
        float health;
        float damage;
        int range; //Range out of 100 blocks
        float accuracy; //Percentage chance of hitting a shot
        float speed; //Blocks per minute
        float reloadTime; //Time it takes before being able to fire again
};

#endif // RIFLEMAN_H
