#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation(sf::Texture* texture, unsigned int frameCount, float switchTime);
        Animation(){}
        void update(sf::Texture* texture, float deltaTime, bool facingRight);
        sf::IntRect textRect;

    private:
        unsigned int frameCount;
        unsigned int currentFrame;
        sf::Texture previousTexture;
        float totalTime; //time since last changed frame
        float switchTime; //time between switching frames
};

#endif // ANIMATION_H
