#ifndef RIFLEMAN_H
#define RIFLEMAN_H
#include "Unit.h"

class Rifleman : public Unit
{
    public:
        Rifleman();
        virtual void fire() override {} //Checks to see if closest enemy is in range and shoots
        virtual void reload() override {} //Checks to see if magazine is empty and reloads
        virtual void die() override {}
        virtual void advance() override {} //Moves forward at the units specific speed
        virtual void stop() override {} //Stops the unit from advancing

        virtual ~Rifleman(){}

    private:
        float health;
        float damage;
        float range; //Range out of 100 blocks
        float accuracy; //Percentage chance of hitting a shot
        float speed; //Blocks per minute
};

#endif // RIFLEMAN_H
