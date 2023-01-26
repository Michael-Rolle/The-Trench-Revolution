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
        float getPositionX() { return unitSprite.getPosition().x; }
        void updateAnimation(const vector<shared_ptr<sf::Texture>>& textures, const float deltaTime);
        int row; //rows 1-10
        int blockNum;
        int cost;
        bool alive;
        bool friendly;
        bool canAdvance;
        bool reloading;
        AnimationMode animationMode;
        UnitType unitType;

        //bool operator < (const Unit& unit) const
        //{
        //    return (this->row < unit.row);
        //}

        virtual ~Unit(){} // virtual desstructor, defaults to doing nothing

    protected:
        //sf::Texture idleText;
        //sf::Texture runText;
        //sf::Texture shootText;
        //sf::Texture dieText;
        sf::Sprite unitSprite;
        Animation animation;
};

#endif // UNIT_H
