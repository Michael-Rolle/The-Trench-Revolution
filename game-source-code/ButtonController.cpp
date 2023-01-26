#include "ButtonController.h"

ButtonController::ButtonController(const float gameWidth, const float gameHeight):
    startButtonText{make_shared<sf::Texture>()},
    riflemanButtonText{make_shared<sf::Texture>()},
    riflemanText{make_shared<sf::Texture>()}
{
    //Load textures
    if(!startButtonText->loadFromFile("resources/startButton.png"))
        throw "Cannot laod texture";
    if(!riflemanButtonText->loadFromFile("resources/Rifleman/Icon.png"))
        throw "Cannot load texture";
    if(!riflemanText->loadFromFile("resources/Rifleman/Idle.png"))
        throw "Cannot load texture";

    //Determine button positions
    int width = 0.05*gameWidth;
    int height = 0.0584*gameHeight;
    int left = 0.5*gameWidth - 0.5*width;
    int top = 0.5*gameHeight - 0.5*height;
    startButton = Button{startButtonText, sf::IntRect{left, top, width, height}};
    width = 0.05*gameWidth;
    height = 0.05*gameHeight;
    left = 0.05*gameWidth  - 0.5*width;
    top = 0.95*gameHeight - 0.5*height;
    riflemanButton = Button{riflemanButtonText, sf::IntRect{left, top, width, height}};
}

void ButtonController::checkButtonClicks(const sf::Event& event, sf::RenderWindow& window, GameState& gameState, shared_ptr<UnitController> unitController, shared_ptr<Money> money, const float gameWidth, const float gameHeight)
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
        if(riflemanButton.checkClicked(event, window, gameWidth, gameHeight) && money->getMoney() >= 50)
        {
            auto unit = make_shared<Rifleman>(riflemanText, gameWidth, gameHeight, 10, 0.1, true);
            ButtonController::spawnFriendlyUnit(unitController, unit, money);
        }
    }
}

void ButtonController::spawnFriendlyUnit(shared_ptr<UnitController> unitController, shared_ptr<Unit> unit, shared_ptr<Money> money)
{
    if(money->getMoney() >= unit->cost)
    {
        unitController->addFriendlyUnit(unit);
        money->subtract(unit->cost);
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
            riflemanButton.draw(window, gameState);
            break;
        case GameState::EndScreen:
            //
            break;
        default:
            throw "Invalid game state";
    }
}
