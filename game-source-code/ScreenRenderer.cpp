#include "ScreenRenderer.h"

ScreenRenderer::ScreenRenderer(const float gameWidth, const float gameHeight)
{
    if(!startBackgroundText.loadFromFile("resources/startBackground.png"))
        throw "Cannot load background image";
    startBackground.setTexture(startBackgroundText);
    startBackground.setScale(gameWidth/startBackground.getLocalBounds().width, gameHeight/startBackground.getLocalBounds().height);

    gameState = GameState::StartScreen;
}

void ScreenRenderer::draw(sf::RenderWindow& window)
{
    switch(gameState)
    {
        case GameState::StartScreen:
            window.draw(startBackground);
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

/*void ScreenRenderer::renderStartScreen()
{

}

void ScreenRenderer::renderPlayingField()
{

}*/
