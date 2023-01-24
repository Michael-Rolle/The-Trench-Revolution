#include "ButtonController.h"

ButtonController::ButtonController(const float gameWidth, const float gameHeight)
{
    //Load textures
    if(!startButtonText.loadFromFile("resources/startButton.png"))
        throw "Cannot laod texture";

    //Determine button positions
    int width = 0.05*gameWidth;
    int height = 0.05*gameHeight;
    int left = 0.5*gameWidth - 0.5*width;
    int top = 0.5*gameHeight - 0.5*height;
    auto startButtonRect = sf::IntRect{left, top, width, height};
    startButton = Button{&startButtonText, startButtonRect};
}

void ButtonController::checkButtonClicks(const sf::Event& event, sf::RenderWindow& window, GameState& gameState, const float gameWidth, const float gameHeight)
{
    if(gameState == GameState::StartScreen)
    {
        if(startButton.checkClicked(event, window, gameWidth, gameHeight))
        {
            ButtonController::startGame(gameState);
        }
    }
}

void ButtonController::draw(sf::RenderWindow& window, const GameState gameState)
{
    switch(gameState)
    {
        case GameState::StartScreen:
            startButton.draw(window, gameState);
            break;
        case GameState::Playing:
            //
            break;
        case GameState::EndScreen:
            //
            break;
        default:
            throw "Invalid game state";
    }
}
