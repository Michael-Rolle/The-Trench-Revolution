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
    int width = 0.1*gameWidth;
    int height = 0.05*gameHeight;
    int left = 0.5*gameWidth - 0.5*width;
    int top = 0.5*gameHeight - 0.5*height;
    startButton = Button{startButtonText, sf::IntRect{left, top, width, height}};
    width = 0.02*gameWidth;
    height = 0.0234*gameHeight;
    left = 0.05*gameWidth  - 0.5*width;
    top = 0.95*gameHeight - 0.5*height;
    riflemanButton = Button{riflemanButtonText, sf::IntRect{left, top, width, height}};
    if(!pointsFont.loadFromFile("resources/HeadlinerNo45.ttf"))
        throw "Cannot load font";
    riflemanPoints.setFont(pointsFont);
    riflemanPoints.setString(to_string(Rifleman::riflemanCost));
    riflemanPoints.setCharacterSize(15);
    riflemanPoints.setFillColor(sf::Color::White);
    riflemanPoints.setOrigin(riflemanPoints.getGlobalBounds().left+0.5f*riflemanPoints.getGlobalBounds().width, riflemanPoints.getGlobalBounds().top+0.5f*riflemanPoints.getGlobalBounds().height);
    riflemanPoints.setPosition(riflemanButton.getPosition().x+0.5f*riflemanButton.getGlobalBounds().width, riflemanButton.getPosition().y+0.5f*riflemanButton.getGlobalBounds().height);
}

void ButtonController::checkButtonClicks(const sf::Event& event, sf::RenderWindow& window, sf::Clock& clock, GameState& gameState, shared_ptr<UnitController> unitController, shared_ptr<Money> money, const float gameWidth, const float gameHeight)
{
    if(gameState == GameState::StartScreen)
    {
        if(startButton.checkClicked(event, window, gameWidth, gameHeight))
        {
            ButtonController::startGame(gameState);
            auto scaleFactor = 0.4f;
            window.setView(sf::View{sf::FloatRect{0.0f, 0.6f*gameHeight, scaleFactor*gameWidth, scaleFactor*gameHeight}});
            clock.restart();
        }
    }
    else if(gameState == GameState::Playing)
    {
        if(riflemanButton.checkClicked(event, window, gameWidth, gameHeight) && money->getMoney() >= Rifleman::riflemanCost)
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
            startButton.setPosition(sf::Vector2f{0.5f*window.getView().getSize().x, 0.5f*window.getView().getSize().y});
            startButton.draw(window, gameState);
            break;
        case GameState::Playing:
            riflemanButton.setPosition(sf::Vector2f{(window.getView().getCenter().x - 0.5f*window.getView().getSize().x) + 0.05f*window.getView().getSize().x, (window.getView().getCenter().y - 0.5f*window.getView().getSize().y) + 0.95f*window.getView().getSize().y});
            riflemanPoints.setPosition(riflemanButton.getPosition());
            riflemanButton.draw(window, gameState);
            window.draw(riflemanPoints);
            break;
        case GameState::EndScreen:
            //
            break;
        default:
            throw "Invalid game state";
    }
}
