#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <memory>

class Button
{
    public:
        Button(sf::Texture* texture, sf::IntRect positionDetails);
        bool checkClicked(sf::Event& event, sf::RenderWindow& window);

    private:
        sf::IntRect buttonRect;
        sf::Sprite buttonSprite;
};

#endif // BUTTON_H
