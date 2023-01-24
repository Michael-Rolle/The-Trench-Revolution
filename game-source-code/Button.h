#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"

class Button : public Drawable
{
    public:
        Button(){}
        Button(sf::Texture* texture, sf::IntRect positionDetails);
        bool checkClicked(const sf::Event& event, sf::RenderWindow& window);
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

    private:
        sf::IntRect buttonRect;
        sf::Sprite buttonSprite;
};

#endif // BUTTON_H
