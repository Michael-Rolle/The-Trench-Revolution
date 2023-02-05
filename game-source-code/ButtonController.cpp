#include "ButtonController.h"

ButtonController::ButtonController(const float gameWidth, const float gameHeight):
    startButtonText{make_shared<sf::Texture>()},
    riflemanButtonText{make_shared<sf::Texture>()},
    riflemanText{make_shared<sf::Texture>()},
    sniperButtonText{make_shared<sf::Texture>()},
    sniperText{make_shared<sf::Texture>()},
    shotgunnerButtonText{make_shared<sf::Texture>()},
    shotgunnerText{make_shared<sf::Texture>()},
    machineGunnerButtonText{make_shared<sf::Texture>()},
    machineGunnerText{make_shared<sf::Texture>()}
{
    //Load textures
    if(!startButtonText->loadFromFile("resources/startButton.png"))
        throw "Cannot laod texture";
    if(!pointsFont.loadFromFile("resources/HeadlinerNo45.ttf"))
        throw "Cannot load font";
    if(!riflemanButtonText->loadFromFile("resources/Rifleman/Icon.png"))
        throw "Cannot load texture";
    if(!riflemanText->loadFromFile("resources/Rifleman/Idle.png"))
        throw "Cannot load texture";
    if(!sniperButtonText->loadFromFile("resources/Sniper/Icon.png"))
        throw "Cannot load texture";
    if(!sniperText->loadFromFile("resources/Sniper/Idle.png"))
        throw "Cannot load texture";
    if(!shotgunnerButtonText->loadFromFile("resources/Shotgunner/Icon.png"))
        throw "Cannot load texture";
    if(!shotgunnerText->loadFromFile("resources/Shotgunner/Idle.png"))
        throw "Cannot load texture";
    if(!machineGunnerButtonText->loadFromFile("resources/MachineGunner/Icon.png"))
        throw "Cannot load texture";
    if(!machineGunnerText->loadFromFile("resources/MachineGunner/Idle.png"))
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
    riflemanPoints.setFont(pointsFont);
    riflemanPoints.setString(to_string(Rifleman::riflemanCost));
    riflemanPoints.setCharacterSize(15);
    riflemanPoints.setFillColor(sf::Color::White);
    riflemanPoints.setOrigin(riflemanPoints.getGlobalBounds().left+0.5f*riflemanPoints.getGlobalBounds().width, riflemanPoints.getGlobalBounds().top+0.5f*riflemanPoints.getGlobalBounds().height);
    riflemanPoints.setPosition(riflemanButton.getPosition().x+0.5f*riflemanButton.getGlobalBounds().width, riflemanButton.getPosition().y+0.5f*riflemanButton.getGlobalBounds().height);

    left += 1.5*width;
    shotgunnerButton = Button{shotgunnerButtonText, sf::IntRect{left, top, width, height}};
    shotgunnerPoints.setFont(pointsFont);
    shotgunnerPoints.setString(to_string(Shotgunner::shotgunnerCost));
    shotgunnerPoints.setCharacterSize(15);
    shotgunnerPoints.setFillColor(sf::Color::White);
    shotgunnerPoints.setOrigin(sniperPoints.getGlobalBounds().left+0.5f*shotgunnerPoints.getGlobalBounds().width, shotgunnerPoints.getGlobalBounds().top+0.5f*shotgunnerPoints.getGlobalBounds().height);
    shotgunnerPoints.setPosition(shotgunnerButton.getPosition().x+0.5f*shotgunnerButton.getGlobalBounds().width, shotgunnerButton.getPosition().y+0.5f*shotgunnerButton.getGlobalBounds().height);

    left += 1.5f*width;
    sniperButton = Button{sniperButtonText, sf::IntRect{left, top, width, height}};
    sniperPoints.setFont(pointsFont);
    sniperPoints.setString(to_string(Sniper::sniperCost));
    sniperPoints.setCharacterSize(15);
    sniperPoints.setFillColor(sf::Color::White);
    sniperPoints.setOrigin(sniperPoints.getGlobalBounds().left+0.5f*sniperPoints.getGlobalBounds().width, sniperPoints.getGlobalBounds().top+0.5f*sniperPoints.getGlobalBounds().height);
    sniperPoints.setPosition(sniperButton.getPosition().x+0.5f*sniperButton.getGlobalBounds().width, sniperButton.getPosition().y+0.5f*sniperButton.getGlobalBounds().height);

    left += 1.5f*width;
    machineGunnerButton = Button{machineGunnerButtonText, sf::IntRect{left, top, width, height}};
    machineGunnerPoints.setFont(pointsFont);
    machineGunnerPoints.setString(to_string(MachineGunner::machineGunnerCost));
    machineGunnerPoints.setCharacterSize(15);
    machineGunnerPoints.setFillColor(sf::Color::White);
    machineGunnerPoints.setOrigin(machineGunnerPoints.getGlobalBounds().left+0.5f*machineGunnerPoints.getGlobalBounds().width, machineGunnerPoints.getGlobalBounds().top+0.5f*machineGunnerPoints.getGlobalBounds().height);
    machineGunnerPoints.setPosition(machineGunnerButton.getPosition().x+0.5f*machineGunnerButton.getGlobalBounds().width, machineGunnerButton.getPosition().y+0.5f*machineGunnerButton.getGlobalBounds().height);
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
        if(riflemanButton.checkClicked(event, window, gameWidth, gameHeight) && money->getMoney() >= Rifleman::riflemanCost && Rifleman::spawnTime <= 0)
        {
            Rifleman::spawnTime = 2; //2 second spawn time
            riflemanPoints.setFillColor(sf::Color::White);
            auto unit = make_shared<Rifleman>(riflemanText, gameWidth, gameHeight, true);
            ButtonController::spawnFriendlyUnit(unitController, unit, money);
        }
        if(shotgunnerButton.checkClicked(event, window, gameWidth, gameHeight) && money->getMoney() >= Shotgunner::shotgunnerCost && Shotgunner::spawnTime <= 0)
        {
            Shotgunner::spawnTime = 4; //4 second spawn time
            shotgunnerPoints.setFillColor(sf::Color::White);
            auto unit = make_shared<Shotgunner>(shotgunnerText, gameWidth, gameHeight, true);
            ButtonController::spawnFriendlyUnit(unitController, unit, money);
        }
        if(sniperButton.checkClicked(event, window, gameWidth, gameHeight) && money->getMoney() >= Sniper::sniperCost && Sniper::spawnTime <= 0)
        {
            Sniper::spawnTime = 6; //6 second spawn time
            sniperPoints.setFillColor(sf::Color::White);
            auto unit = make_shared<Sniper>(sniperText, gameWidth, gameHeight, true);
            ButtonController::spawnFriendlyUnit(unitController, unit, money);
        }
        if(machineGunnerButton.checkClicked(event, window, gameWidth, gameHeight) && money->getMoney() >= MachineGunner::machineGunnerCost && MachineGunner::spawnTime <= 0)
        {
            MachineGunner::spawnTime = 8; //8 second spawn time
            machineGunnerPoints.setFillColor(sf::Color::White);
            auto unit = make_shared<MachineGunner>(machineGunnerText, gameWidth, gameHeight, true);
            ButtonController::spawnFriendlyUnit(unitController, unit, money);
        }
    }
}

void ButtonController::changeIconPointColor(UnitType unitType, sf::Color color)
{
    switch(unitType)
    {
        case UnitType::Rifleman:
            riflemanPoints.setFillColor(color);
            break;
        case UnitType::Sniper:
            sniperPoints.setFillColor(color);
            break;
        case UnitType::Shotgunner:
            shotgunnerPoints.setFillColor(color);
            break;
        case UnitType::MachineGunner:
            machineGunnerPoints.setFillColor(color);
            break;
        default:
            throw "Invalid unit type";
    }
}

void ButtonController::spawnFriendlyUnit(shared_ptr<UnitController> unitController, shared_ptr<Unit> unit, shared_ptr<Money> money)
{
    if(money->getMoney() >= unit->cost)
    {
        unit->friendly = true;
        unitController->addUnit(unit);
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
            shotgunnerButton.setPosition(sf::Vector2f{(window.getView().getCenter().x - 0.5f*window.getView().getSize().x) + 0.05f*window.getView().getSize().x + 1.5f*riflemanButton.getGlobalBounds().width, (window.getView().getCenter().y - 0.5f*window.getView().getSize().y) + 0.95f*window.getView().getSize().y});
            shotgunnerPoints.setPosition(shotgunnerButton.getPosition());
            shotgunnerButton.draw(window, gameState);
            window.draw(shotgunnerPoints);
            sniperButton.setPosition(sf::Vector2f{(window.getView().getCenter().x - 0.5f*window.getView().getSize().x) + 0.05f*window.getView().getSize().x + 3.0f*riflemanButton.getGlobalBounds().width, (window.getView().getCenter().y - 0.5f*window.getView().getSize().y) + 0.95f*window.getView().getSize().y});
            sniperPoints.setPosition(sniperButton.getPosition());
            sniperButton.draw(window, gameState);
            window.draw(sniperPoints);
            machineGunnerButton.setPosition(sf::Vector2f{(window.getView().getCenter().x - 0.5f*window.getView().getSize().x) + 0.05f*window.getView().getSize().x + 4.5f*machineGunnerButton.getGlobalBounds().width, (window.getView().getCenter().y - 0.5f*window.getView().getSize().y) + 0.95f*window.getView().getSize().y});
            machineGunnerPoints.setPosition(machineGunnerButton.getPosition());
            machineGunnerButton.draw(window, gameState);
            window.draw(machineGunnerPoints);
            break;
        case GameState::EndScreen:
            //
            break;
        default:
            throw "Invalid game state";
    }
}
