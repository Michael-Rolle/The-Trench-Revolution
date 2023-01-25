#include "Money.h"

Money::Money(const float gameWidth, const float gameHeight)
{
    money = 0;
    totalTime = 0;
    if(!font.loadFromFile("resources/HeadlinerNo45.ttf"))
        throw "Cannnot load font";
    moneyText.setFont(font);
    moneyText.setString(to_string(money));
    moneyText.setCharacterSize(60);
    moneyText.setFillColor(sf::Color::Black);
    moneyText.setOrigin(moneyText.getGlobalBounds().left + 0.5*moneyText.getGlobalBounds().width, moneyText.getGlobalBounds().top + 0.5*moneyText.getGlobalBounds().height);
    moneyText.setPosition(0.06*gameWidth, 0.06*gameHeight);
}

void Money::update(const float deltaTime)
{
    totalTime += deltaTime;
    if(totalTime >= 5)
    {
        totalTime = 0;
        money += 50;
        moneyText.setString(to_string(money));
    }
}

void Money::draw(sf::RenderWindow& window, const GameState gameState)
{
    if(gameState == GameState::Playing)
        window.draw(moneyText);
}
