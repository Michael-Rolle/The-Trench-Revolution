#include "Animation.h"
#include <cmath>

Animation::Animation(sf::Texture* texture, unsigned int frameCount, float switchTime)
{
    this->frameCount = frameCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentFrame = 0;

    previousTexture = *texture;

    textRect.width = texture->getSize().x / float(frameCount);
    textRect.height = texture->getSize().y;
    textRect.top = 0;
}

void Animation::update(sf::Texture* texture, float deltaTime, bool facingRight)
{
    if(texture->getNativeHandle() != previousTexture.getNativeHandle())
    {
        currentFrame = 0;
        previousTexture = *texture;
        textRect.width = texture->getSize().x/float(frameCount);
        textRect.height = texture->getSize().y;
    }

    totalTime += deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentFrame++;

        if(currentFrame >= frameCount)
        {
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
