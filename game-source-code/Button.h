#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button(){}
        Button(sf::Texture* texture, sf::IntRect positionDetails);
        bool checkClicked(const sf::Event& event, sf::RenderWindow& window);

    private:
        sf::IntRect buttonRect;
        sf::Sprite buttonSprite;
};

#endif // BUTTON_H
