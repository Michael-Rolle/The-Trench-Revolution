#include "Button.h"

Button::Button(sf::Texture* texture, sf::IntRect positionDetails):
    buttonRect{positionDetails}
{
    buttonSprite.setTexture(*texture);
    buttonSprite.setScale(positionDetails.width/buttonSprite.getGlobalBounds().width, positionDetails.height/buttonSprite.getGlobalBounds().height);
    buttonSprite.setPosition(positionDetails.left, positionDetails.top);
}

bool Button::checkClicked(const sf::Event& event, sf::RenderWindow& window, const float gameWidth, const float gameHeight)
{
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        auto mouseX = sf::Mouse::getPosition(window).x*gameWidth/window.getSize().x;
        auto mouseY = sf::Mouse::getPosition(window).y*gameHeight/window.getSize().y;
        if((mouseX - buttonRect.left <= buttonRect.width) && (mouseX - buttonRect.left > 0) && (mouseY - buttonRect.top  <= buttonRect.height) && (mouseY - buttonRect.top  > 0))
            return true;
    }
    return false;
}

void Button::draw(sf::RenderWindow& window, const GameState gameState)
{
    window.draw(buttonSprite);
}
