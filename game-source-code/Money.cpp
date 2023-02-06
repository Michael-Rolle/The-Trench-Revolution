#include "Money.h"

Money::Money(const float gameWidth, const float gameHeight)
{
    this->money = 1000;
    this->addAmount = 50;
    this->totalTime = 0;
    this->elapsedTime = 0;
    if(!font.loadFromFile("resources/HeadlinerNo45.ttf"))
        throw "Cannnot load font";
    moneyText.setFont(font);
    moneyText.setString(to_string(money));
    moneyText.setCharacterSize(30);
    moneyText.setFillColor(sf::Color::Yellow);
    moneyText.setOrigin(moneyText.getGlobalBounds().left + 0.5*moneyText.getGlobalBounds().width, moneyText.getGlobalBounds().top + 0.5*moneyText.getGlobalBounds().height);
    moneyText.setPosition(0.06*gameWidth, 0.06*gameHeight);
}

void Money::update(const float deltaTime)
{
    totalTime += deltaTime;
    if(totalTime > 360)
        addAmount = 200;
    else if(totalTime > 240)
        addAmount = 150;
    else if(totalTime > 120)
        addAmount = 100;

    elapsedTime += deltaTime;
    if(elapsedTime >= 5)
    {
        elapsedTime = 0;
        money += addAmount;
        moneyText.setString(to_string(money));
    }
}

void Money::draw(sf::RenderWindow& window, const GameState gameState)
{
    if(gameState == GameState::Playing)
    {
        moneyText.setPosition(sf::Vector2f{window.getView().getCenter().x-0.5f*window.getView().getSize().x+0.06f*window.getView().getSize().x, window.getView().getCenter().y-0.5f*window.getView().getSize().y+0.06f*window.getView().getSize().y});
        window.draw(moneyText);
    }
}
