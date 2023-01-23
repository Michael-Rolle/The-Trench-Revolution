#include "ScreenRenderer.h"

ScreenRenderer::ScreenRenderer(const float gameWidth, const float gameHeight)
{
    if(!startBackgroundText.loadFromFile("resources/startBackground.png"))
        throw "Cannot load background image";
    startBackground.setTexture(startBackgroundText);
    startBackground.setScale(gameWidth/startBackground.getLocalBounds().width, gameHeight/startBackground.getLocalBounds().height);

    if(!font.loadFromFile("resources/HeadlinerNo45.ttf"))
        throw "Cannot load font";
    title.setFont(font);
    title.setString("The  Trench  Revolution");
    title.setCharacterSize(150);
    title.setLetterSpacing(2);
    title.setOrigin(title.getLocalBounds().width/2, title.getLocalBounds().height/2);
    title.setPosition(0.5*gameWidth, 0.15*gameHeight);
    title.setColor(sf::Color::Black);
    title.setOutlineColor(sf::Color::White);
    title.setOutlineThickness(3);
}

void ScreenRenderer::draw(sf::RenderWindow& window, const GameState gameState)
{
    switch(gameState)
    {
        case GameState::StartScreen:
            window.draw(startBackground);
            window.draw(title);
            //window.draw(startButton);
            //window.draw(quitButton);
            break;
        case GameState::Playing:
            window.draw(playingFieldBackground);
            //Draw all necessary buttons for the game
            break;
        case GameState::EndScreen:
            window.draw(endBackground);
            window.draw(quitButton);
            break;
        default:
            throw "Invalid game state";
    }
}
