#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "Drawable.h"
#include <memory>

using namespace std;

class Button : public Drawable
{
    public:
        Button(){}
        Button(shared_ptr<sf::Texture> texture, sf::IntRect positionDetails);
        bool checkClicked(const sf::Event& event, sf::RenderWindow& window, const float gameWidth, const float gameHeight);
        void setPosition(const sf::Vector2f& coordinates);
        sf::Vector2f getPosition() const;
        sf::FloatRect getGlobalBounds() const;
        virtual void draw(sf::RenderWindow& window, const GameState gameState) override;

    private:
        sf::Sprite buttonSprite;
};

#endif // BUTTON_H
