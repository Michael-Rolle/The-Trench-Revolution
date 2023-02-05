#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include "AnimationMode.h"
#include "UnitType.h"
#include <memory>

using namespace std;

class Animation
{
    public:
        Animation(shared_ptr<sf::Texture> texture, unsigned int frameCount, float switchTime);
        Animation(){}
        void update(shared_ptr<sf::Texture> texture, AnimationMode animationMode, UnitType unitType, bool& shooting, bool& dying, bool &canShoot, float deltaTime, bool facingRight);
        sf::IntRect textRect;

    private:
        unsigned int frameCount;
        unsigned int currentFrame;
        AnimationMode prevAnimationMode;
        float totalTime; //time since last changed frame
        float switchTime; //time between switching frames
};

#endif // ANIMATION_H
