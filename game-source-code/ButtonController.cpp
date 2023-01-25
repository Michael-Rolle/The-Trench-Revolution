#include "ButtonController.h"

ButtonController::ButtonController(const float gameWidth, const float gameHeight)
{
    //Load textures
    if(!startButtonText.loadFromFile("resources/startButton.png"))
        throw "Cannot laod texture";
    if(!riflemanButtonText.loadFromFile("resources/Soldier-Guy-PNG/_Mode-Gun/01-Idle/E_E_Gun__Idle_000.png"))
        throw "Cannot load texture";
    if(!riflemanText.loadFromFile("resources/Soldier-Guy-PNG/_Mode-Gun/01-Idle/E_E_Gun__Idle_000.png"))
        throw "Cannot load texture";

    //Determine button positions
    int width = 0.05*gameWidth;
    int height = 0.05*gameHeight;
    int left = 0.5*gameWidth - 0.5*width;
    int top = 0.5*gameHeight - 0.5*height;
    startButton = Button{&startButtonText, sf::IntRect{left, top, width, height}};
    width = 0.05*gameWidth;
    height = 0.05*gameHeight;
    left = 0.05*gameWidth  - 0.5*width;
    top = 0.95*gameHeight - 0.5*height;
    riflemanButton = Button{&riflemanButtonText, sf::IntRect{left, top, width, height}};
}

void ButtonController::checkButtonClicks(const sf::Event& event, sf::RenderWindow& window, GameState& gameState, shared_ptr<UnitController> unitController, const float gameWidth, const float gameHeight)
{
    if(gameState == GameState::StartScreen)
    {
        if(startButton.checkClicked(event, window, gameWidth, gameHeight))
        {
            ButtonController::startGame(gameState);
        }
    }
    else if(gameState == GameState::Playing)
    {
        if(riflemanButton.checkClicked(event, window, gameWidth, gameHeight))
        {
            auto unit = make_shared<Rifleman>(&riflemanText, gameWidth, gameHeight);
            ButtonController::spawnFriendlyUnit(unitController, unit);
        }
    }
}

void ButtonController::spawnFriendlyUnit(shared_ptr<UnitController> unitController, shared_ptr<Unit> unit)
{
    unitController->addFriendlyUnit(unit);
}

void ButtonController::draw(sf::RenderWindow& window, const GameState gameState)
{
    switch(gameState)
    {
        case GameState::StartScreen:
            startButton.draw(window, gameState);
            break;
        case GameState::Playing:
            riflemanButton.draw(window, gameState);
            break;
        case GameState::EndScreen:
            //
            break;
        default:
            throw "Invalid game state";
    }
}
