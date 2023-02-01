#include "Button.h"

Button::Button(shared_ptr<sf::Texture> texture, sf::IntRect positionDetails)
{
    buttonSprite.setTexture(*texture);
    buttonSprite.setScale(positionDetails.width/buttonSprite.getGlobalBounds().width, positionDetails.height/buttonSprite.getGlobalBounds().height);
    buttonSprite.setPosition(positionDetails.left, positionDetails.top);
}

bool Button::checkClicked(const sf::Event& event, sf::RenderWindow& window, const float gameWidth, const float gameHeight)
{
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        auto mouseX = (window.getView().getCenter().x - 0.5f*window.getView().getSize().x) + sf::Mouse::getPosition(window).x*window.getView().getSize().x/window.getDefaultView().getSize().x;
        auto mouseY = (window.getView().getCenter().y - 0.5f*window.getView().getSize().y) + sf::Mouse::getPosition(window).y*window.getView().getSize().y/window.getDefaultView().getSize().y;
        auto bounds = buttonSprite.getGlobalBounds();
        if((mouseX - bounds.left <= bounds.width) && (mouseX - bounds.left > 0) && (mouseY - bounds.top <= bounds.height) && (mouseY - bounds.top > 0))
            return true;
    }
    return false;
}

void Button::setPosition(const sf::Vector2f& coordinates)
{
    buttonSprite.setPosition(coordinates.x - 0.5f*buttonSprite.getGlobalBounds().width, coordinates.y -0.5f*buttonSprite.getGlobalBounds().height);
}

sf::Vector2f Button::getPosition() const
{
    //return sf::Vector2f{buttonSprite.getPosition().x+0.5f*buttonSprite.getGlobalBounds().width, buttonSprite.getPosition().y+0.5f*buttonSprite.getGlobalBounds().height};
    return buttonSprite.getPosition();
}

sf::FloatRect Button::getGlobalBounds() const
{
    return buttonSprite.getGlobalBounds();
}

void Button::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(buttonSprite);
}
