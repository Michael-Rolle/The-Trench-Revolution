#ifndef UNIT_H
#define UNIT_H

#include "Drawable.h"
#include "Animation.h"
#include "AnimationMode.h"
#include "UnitType.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <memory>

using namespace std;

class Unit : public Drawable //Abstract Base Class, use pointer or reference for derived classes
{
    public:
        Unit(shared_ptr<sf::Texture> texture, unsigned int frameCount, float switchTime, bool friendly); //Scaling of sprite left for derived classes
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;
        virtual void fire(vector<shared_ptr<Unit>> enemyUnits) = 0; //Checks to see if closest enemy is in range and shoots
        virtual void reload(const float deltaTime) = 0; //Checks to see if magazine is empty and reloads
        virtual void die() = 0;
        virtual void advance(const float deltaTime) = 0; //Moves forward at the units specific speed to the next block
        virtual void stop() = 0; //Stops the unit from advancing
        virtual void takeDamage(float damageAmount) = 0;
        virtual void update(vector<shared_ptr<Unit>> units, const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime, const float gameWidth, const float gameHeight) = 0;

        sf::Vector2f getPosition() { return unitSprite.getPosition(); }
        int row; //rows 1-10
        int blockNum;
        int cost;
        bool alive;
        bool friendly;
        bool canAdvance;
        bool reloading;
        bool canShoot;
        bool shooting;
        bool dying;
        AnimationMode animationMode;
        UnitType unitType;

        virtual ~Unit(){} // virtual destructor, defaults to doing nothing

    protected:
        void updateAnimation(const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime);
        float health;
        float maxHealth;
        float damage;
        int range; //Range out of 100 blocks
        float accuracy; //Percentage chance of hitting a shot
        float speed; //Blocks per minute
        float reloadTime;
        sf::Sprite unitSprite;
        sf::RectangleShape greenHealthBar;
        sf::RectangleShape redHealthBar;
        Animation animation;
};

#endif // UNIT_H
