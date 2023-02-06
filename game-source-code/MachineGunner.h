#ifndef MACHINEGUNNER_H
#define MACHINEGUNNER_H

#include <SFML/Graphics.hpp>
#include "Unit.h"

class MachineGunner : public Unit
{
    public:
        MachineGunner();
        MachineGunner(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, bool friendly);
        virtual void fire(vector<shared_ptr<Unit>> enemyUnits) override; //Checks to see if closest enemy is in range and shoots
        virtual void reload(const float deltaTime) override; //Takes time off the reloadTime counter
        virtual void die() override;
        virtual void advance(const float deltaTime) override; //Moves forward at the units specific speed
        virtual void stop() override; //Stops the unit from advancing
        virtual void takeDamage(float damageAmount) override;
        virtual void update(vector<shared_ptr<Unit>> units, const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime, const float gameWidth, const float gameHeight) override;
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

        static int machineGunnerCost;
        static float spawnTime; //time you have to wait between spawning units

        virtual ~MachineGunner(){}
};

#endif // MACHINEGUNNER_H
