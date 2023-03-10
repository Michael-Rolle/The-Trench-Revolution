#include "Animation.h"
#include <cmath>

Animation::Animation(shared_ptr<sf::Texture> texture, unsigned int frameCount, float switchTime)
{
    this->frameCount = frameCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentFrame = 0;

    prevAnimationMode = AnimationMode::Idle;

    textRect.width = texture->getSize().x / float(frameCount);
    textRect.height = texture->getSize().y;
    textRect.top = 0;
}

void Animation::update(shared_ptr<sf::Texture> texture, AnimationMode animationMode, UnitType unitType, bool& shooting, bool& dying, bool& canShoot, float deltaTime, bool facingRight)
{
    if(animationMode != prevAnimationMode)
    {
        currentFrame = 0;
        prevAnimationMode = animationMode;
        textRect.width = texture->getSize().x/float(frameCount);
        textRect.height = texture->getSize().y;
        if(unitType == UnitType::MachineGunner && animationMode == AnimationMode::Shoot)
        {
            this->switchTime = 0.02;
        }
        else if(unitType == UnitType::MachineGunner && animationMode != AnimationMode::Shoot)
        {
            this->switchTime = 0.12;
        }
    }

    totalTime += deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentFrame++;

        if(animationMode == AnimationMode::Shoot)
        {
            shooting = true;
            if(currentFrame == 2)
                canShoot = true;
            if(currentFrame >= frameCount)
            {
                shooting = false;
                currentFrame = 0;
            }
        }

        if(currentFrame >= frameCount)
        {
            if(dying)
                dying = false;
            currentFrame = 0;
        }
    }

    if(facingRight)
    {
        textRect.left = currentFrame * textRect.width;
        textRect.width = abs(textRect.width);
    }
    else //flips row of animation to face the other direction
    {
        textRect.left = (currentFrame + 1) * abs(textRect.width);
        textRect.width = -abs(textRect.width);
    }
}
