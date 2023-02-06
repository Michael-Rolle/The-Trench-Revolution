#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics.hpp>
#include "Unit.h"
#include <memory>

class Tank : public Unit
{
    public:
        Tank(shared_ptr<sf::Texture> texture, const float gameWidth, const float gameHeight, bool friendly);
        virtual void fire(vector<shared_ptr<Unit>> enemyUnits) override; //Checks to see if closest enemy is in range and shoots
        virtual void reload(const float deltaTime) override; //Takes time off the reloadTime counter
        virtual void die() override;
        virtual void advance(const float deltaTime) override; //Moves forward at the units specific speed
        virtual void stop() override; //Stops the unit from advancing
        virtual void takeDamage(float damageAmount) override;
        virtual void update(vector<shared_ptr<Unit>> units, const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime, const float gameWidth, const float gameHeight) override;
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

        vector<shared_ptr<Unit>> enemiesHitByShot(vector<shared_ptr<Unit>>& enemies, const int shotBlockNum, const int shotRow);

        static int tankCost;
        static float spawnTime; //time you have to wait between spawning units

        virtual ~Tank(){}

    private:
        sf::IntRect explosionTextRect;
        sf::Texture explosionText;
        sf::Sprite explosion;
        float switchTime;
        float totalTime;
        unsigned int currentFrame;
        int radius;
        bool exploding;
};

#endif // TANK_H
