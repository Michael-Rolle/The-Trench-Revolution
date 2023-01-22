#ifndef UNIT_H
#define UNIT_H

class Unit //Abstract Base Class, use pointer or reference for derived classes
{
    public:
        virtual void fire() = 0; //Checks to see if closest enemy is in range and shoots
        virtual void reload() = 0; //Checks to see if magazine is empty and reloads
        virtual void die() = 0;
        virtual void advance() = 0; //Moves forward at the units specific speed
        virtual void stop() = 0; //Stops the unit from advancing
        virtual void takeDamage(float damageAmount) = 0;

        virtual ~Unit(){} // virtual desstructor, defaults to doing nothing
};

#endif // UNIT_H
