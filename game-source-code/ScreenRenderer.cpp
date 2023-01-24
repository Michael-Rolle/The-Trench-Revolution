#include "ScreenRenderer.h"

ScreenRenderer::ScreenRenderer(const float gameWidth, const float gameHeight)
{
    if(!startBackgroundText.loadFromFile("resources/startBackground.png"))
        throw "Cannot load starting background image";
    startBackground.setTexture(startBackgroundText);
    startBackground.setScale(gameWidth/startBackground.getGlobalBounds().width, gameHeight/startBackground.getGlobalBounds().height);

    if(!font.loadFromFile("resources/HeadlinerNo45.ttf"))
        throw "Cannot load font";
    title.setFont(font);
    title.setString("The  Trench  Revolution");
    title.setCharacterSize(150);
    title.setLetterSpacing(2);
    title.setOrigin(title.getGlobalBounds().left + title.getGlobalBounds().width/2.0f, title.getGlobalBounds().top + title.getGlobalBounds().height/2.0f);
    title.setPosition(0.5*gameWidth, 0.15*gameHeight);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(3);

    if(!playingFieldBackgroundText.loadFromFile("resources/playingFieldBackground.png"))
        throw "Cannot load playing field background";
    playingFieldBackground.setTexture(playingFieldBackgroundText);
    playingFieldBackground.setScale(gameWidth/playingFieldBackground.getLocalBounds().width, gameHeight/playingFieldBackground.getLocalBounds().height);
}

void ScreenRenderer::draw(sf::RenderWindow& window, const GameState gameState)
{
    switch(gameState)
    {
        case GameState::StartScreen:
            window.draw(startBackground);
            window.draw(title);
            break;
        case GameState::Playing:
            window.draw(playingFieldBackground);
            break;
        case GameState::EndScreen:
            window.draw(endBackground);
            break;
        default:
            throw "Invalid game state";
    }
}
